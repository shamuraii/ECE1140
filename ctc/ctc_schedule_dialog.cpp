#include <vector>
#include <QMessageBox>
#include <QString>

#include "ctc_schedule_dialog.h"
#include "ui_ctc_schedule_dialog.h"
#include "ctc_home.h"
#include "block.h"
#include "station.h"
#include "trackline.h"
#include "train.h"
#include "trainnetwork.h"

CtcScheduleDialog::CtcScheduleDialog(TrackLine *line, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcScheduleDialog),
    line_(line)
{
    ui->setupUi(this);
    RefreshDisplay();
}

CtcScheduleDialog::~CtcScheduleDialog()
{
    delete ui;
}

void CtcScheduleDialog::on_cancel_button_clicked()
{
    this->close();
}


void CtcScheduleDialog::on_schedule_button_clicked()
{
    TrainNetwork *network = qobject_cast<CtcGUI*>(this->parent()->parent())->Network();
    QTime departure_time = ui->depart_box->time();

    if (ui->dest_cbox->currentText().isEmpty()) {
        QMessageBox::warning(this, "Error", "No destination stop selected.");
        return;
    }

    Station *destination = line_->GetStation(ui->dest_cbox->currentText());

    Train *new_train = new Train(destination,
                                 departure_time,
                                 line_);
    network->AddTrain(new_train);
    QMessageBox::information(this, "Success", "Train " + QString::number(new_train->GetNum()) + " scheduled successfully.");
    this->close();
}

void CtcScheduleDialog::RefreshDisplay() {
    if (line_) {
        ui->dest_cbox->clear();
        for (Station *s : line_->GetStations()) {
            ui->dest_cbox->addItem(s->GetName());
        }
    }
}
