#include "stationdetails.h"
#include "ui_stationdetails.h"

StationDetails::StationDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StationDetails)
{
    ui->setupUi(this);


}

StationDetails::~StationDetails()
{
    delete ui;
}

void StationDetails::update_station(QString s, QString t, QString tr, QString b, QString d){
    ui->stationLabel->setText(s);
    ui->ticket_label->setText(t);
    ui->train_label->setText(tr);
    ui->board_label->setText(b);
    ui->leave_label->setText(d);
}
