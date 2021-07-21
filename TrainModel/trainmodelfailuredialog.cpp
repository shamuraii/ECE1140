#include "trainmodelfailuredialog.h"
#include "ui_trainmodelfailuredialog.h"
#include "controllerinterface.h"

#include <iostream>
#include <QObject>

TrainModelFailureDialog::TrainModelFailureDialog(QWidget *parent, TrainModelData* d) :
    QDialog(parent),
    ui(new Ui::TrainModelFailureDialog),
    data(d)
{
    ui->setupUi(this);
    brakes = ebrakes = engine_fail = signal_fail = brake_fail = false;

    //Connect buttons to interface slots
    QObject::connect(this, &TrainModelFailureDialog::brakeToggled, &ControllerInterface::getInstance(), &ControllerInterface::setServiceBrake);
    QObject::connect(this, &TrainModelFailureDialog::eBrakeToggled, &ControllerInterface::getInstance(), &ControllerInterface::setEBrake);
}

TrainModelFailureDialog::~TrainModelFailureDialog()
{
    delete ui;
}

void TrainModelFailureDialog::setTrain(TrainModelData* d)
{
    data = d;
    update();
}

//Brake toggle button
void TrainModelFailureDialog::on_pushButton_clicked()
{
    //data->setBrakesOn(!data->getBrakesOn());
    emit brakeToggled(data->getID(), !data->getBrakesOn());
    update();
}

//Ebrake toggle button
void TrainModelFailureDialog::on_pushButton_2_clicked()
{
    //data->setEbrakesOn(!data->getEbrakesOn());
    emit eBrakeToggled(data->getID(), !data->getEbrakesOn());
    update();
}

//Engine failure toggle button
void TrainModelFailureDialog::on_pushButton_3_clicked()
{
    data->setEngineFail(!data->getEngineFail());
    update();
}

//Signal failure toggle button
void TrainModelFailureDialog::on_pushButton_4_clicked()
{
    data->setSignalFail(!data->getSignalFail());
    update();
}

//Brake failure toggle button
void TrainModelFailureDialog::on_pushButton_5_clicked()
{
    data->setBrakeFail(!data->getBrakeFail());
    update();
}

void TrainModelFailureDialog::update()
{
    if (data->getBrakesOn()) ui->label_3->setText("Service Brakes: On");
    else ui->label_3->setText("Service Brakes: Off");
    if (data->getEbrakesOn()) ui->label_2->setText("Emergency Brakes: On");
    else ui->label_2->setText("Emergency Brakes: Off");
    if (data->getEngineFail()) ui->label_7->setText("Failure!!");
    else ui->label_7->setText("Operational");
    if (data->getSignalFail()) ui->label_8->setText("Failure!!");
    else ui->label_8->setText("Operational");
    if (data->getBrakeFail()) ui->label_9->setText("Failure!!");
    else ui->label_9->setText("Operational");
}


