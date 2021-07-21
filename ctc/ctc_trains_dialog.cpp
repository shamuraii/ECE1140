#include <QMessageBox>

#include "ctc_trains_dialog.h"
#include "ui_ctc_trains_dialog.h"
#include "ctc_home.h"
#include "ctc_route_dialog.h"

#include "trainnetwork.h"
#include "trackline.h"
#include "train.h"

CtcTrainsDialog::CtcTrainsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcTrainsDialog)
{
    ui->setupUi(this);
    FillTable();
}

CtcTrainsDialog::~CtcTrainsDialog()
{
    delete ui;
}

void CtcTrainsDialog::FillTable() {
    TrainNetwork *network = qobject_cast<CtcGUI*>(this->parent())->Network();
    QTableWidget *table = ui->trains_table;
    QStringList headers = {"TrainID", "Location", "Destination", "Departure Time", "ETA"};

    table->setRowCount(0);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSortingEnabled(true);

    for (Train *t : network->GetTrains()) {
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(t->GetNum())));
        table->setItem(table->rowCount() - 1, 1, new QTableWidgetItem(QString::number(t->GetLocation()->GetNum())));
        table->setItem(table->rowCount() - 1, 2, new QTableWidgetItem(t->GetDestination()->GetName()));
        table->setItem(table->rowCount() - 1, 3, new QTableWidgetItem(t->GetDepartTime().toString("hh:mm")));
        table->setItem(table->rowCount() - 1, 4, new QTableWidgetItem(t->GetArrivalTime().toString("hh:mm")));
    }
}

void CtcTrainsDialog::on_refresh_button_clicked()
{
    FillTable();
}


void CtcTrainsDialog::on_back_button_clicked()
{
    this->close();
}


void CtcTrainsDialog::on_route_button_clicked()
{
    TrainNetwork *network = qobject_cast<CtcGUI*>(this->parent())->Network();
    QTableWidget *table = ui->trains_table;
    int row = table->currentRow();

    if (row == -1) {
        QMessageBox::information(this, "Warning", "A train must be selected.");
        return;
    }

    qDebug() << row;

    if (network->IsAutomatic()) {
        int result = QMessageBox::warning(this, "Leaving Automatic Mode", "About to turn off Automatic Mode. Once disabled, this mode cannot be re-enabled. Are you sure you want to continue?",
                             QMessageBox::Cancel | QMessageBox::Ok);
        if (result == QMessageBox::Ok)
            network->DisableAutomatic();
        else if (result != QMessageBox::Ok)
            return;
    }

    QTableWidgetItem *item = table->item(row, 0);
    QString train_id = item->text();
    Train *train = network->GetTrain(train_id.toInt());

    if (route_popup_ && route_popup_->isVisible())
        route_popup_->close();
    route_popup_ = new CtcRouteDialog(train, this);
    route_popup_->show();
}

