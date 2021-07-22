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
