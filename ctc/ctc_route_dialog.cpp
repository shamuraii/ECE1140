#include <QMessageBox>

#include "ctc_route_dialog.h"
#include "ui_ctc_route_dialog.h"
#include "station.h"
#include "train.h"
#include "trackline.h"

CtcRouteDialog::CtcRouteDialog(Train *train, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcRouteDialog)
{
    ui->setupUi(this);
    train_ = train;
    line_ = train_->GetLine();
    setWindowTitle("Edit Route: Train " + QString::number(train_->GetNum()));

    ui->train_text->setText(QString::number(train_->GetNum()));

    ui->dest_cbox->clear();
    for (Station *s : line_->GetStations()) {
        ui->dest_cbox->addItem(s->GetName());
    }
    ui->dest_cbox->setCurrentText(train_->GetDestination()->GetName());
}

CtcRouteDialog::~CtcRouteDialog()
{
    delete ui;
}

void CtcRouteDialog::on_cancel_button_clicked()
{
    this->close();
}


void CtcRouteDialog::on_route_text_editingFinished()
{
    bool is_numeric = false;
    int block_num = ui->route_text->text().toInt(&is_numeric);
    if (!is_numeric) {
        QMessageBox::warning(this, "Invalid Route Info", "Route-text must be a valid block number.");
        ui->route_text->clear();
    } else if (!line_->GetBlock(block_num)) {
        QMessageBox::warning(this, "Invalid Route Info", "Route-text provided block does not exist on track.");
        ui->route_text->clear();
    }
}


void CtcRouteDialog::on_save_button_clicked()
{
    QMessageBox::information(this, "Sorry", "This has not yet been implemented.");
    this->close();
}

