#include "failalert.h"
#include "ui_failalert.h"

QString alert;

FailAlert::FailAlert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FailAlert)
{
    ui->setupUi(this);
}

FailAlert::~FailAlert()
{
    delete ui;
}

void FailAlert::setAlert(QString s){
    alert = s;

    QLabel *msg = ui->fail_msg;
    msg->setText(alert);
}
