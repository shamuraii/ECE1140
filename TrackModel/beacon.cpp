#include "beacon.h"
#include "ui_beacon.h"

Beacon::Beacon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Beacon)
{
    ui->setupUi(this);
}

Beacon::~Beacon()
{
    delete ui;
}

void Beacon::update_beacon(QString s, QString t){
    ui->stationName->setText(s);
    ui->stationSide->setText(t);
}
