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
