#include "trainmodeldebugdialog.h"
#include "ui_trainmodeldebugdialog.h"
#include "controllerinterface.h"
#include "trackmodelinterface.h"

TrainModelDebugDialog::TrainModelDebugDialog(QWidget *parent, TrainModelData* d) :
    QDialog(parent),
    ui(new Ui::TrainModelDebugDialog),
    data(d)
{
    ui->setupUi(this);
}

TrainModelDebugDialog::~TrainModelDebugDialog()
{
    delete ui;
}

void TrainModelDebugDialog::setTrain(TrainModelData* d)
{
    data = d;
}

void TrainModelDebugDialog::update()
{
    //emit dataChanged();
}

/***Train Controller Tab***/

//Set Commanded Power
void TrainModelDebugDialog::on_pushButton_6_clicked()
{
    QString s = ui->lineEdit_2->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        ControllerInterface::getInstance().setCommandedPower(data->getID(), d);
        update();
    }
}

//Send Announcement
void TrainModelDebugDialog::on_pushButton_7_clicked()
{
    ControllerInterface::getInstance().setAnnouncement(data->getID(), ui->lineEdit_3->text());
    update();
}

//Set Cabin Temp
void TrainModelDebugDialog::on_pushButton_5_clicked()
{
    QString s = ui->lineEdit->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        ControllerInterface::getInstance().setCabinTemp(data->getID(), d);
        update();
    }
}

//Toggle service brakes
void TrainModelDebugDialog::on_pushButton_8_clicked()
{
    ControllerInterface::getInstance().setServiceBrake(data->getID(), !data->getBrakesOn());
    update();
}

//Toggle headlights
void TrainModelDebugDialog::on_pushButton_4_clicked()
{
    ControllerInterface::getInstance().setHeadlights(data->getID(), !data->getHeadlights());
    update();
}

//Toggle cabin lights
void TrainModelDebugDialog::on_pushButton_3_clicked()
{
    ControllerInterface::getInstance().setCabinLights(data->getID(), !data->getCabinLights());
    update();
}

//Toggle right door
void TrainModelDebugDialog::on_pushButton_2_clicked()
{
    ControllerInterface::getInstance().setRightDoor(data->getID(), !data->getRightDoors());
    update();
}

//Toggle left door
void TrainModelDebugDialog::on_pushButton_clicked()
{
    ControllerInterface::getInstance().setLeftDoor(data->getID(), !data->getLeftDoors());
    update();
}

/***Track Model***/

//Toggle Authority
void TrainModelDebugDialog::on_pushButton_9_clicked()
{
    if (data->getAuthority()) TrackModelInterface::getInstance().setAuthority(data->getID(), 0);
    else TrackModelInterface::getInstance().setAuthority(data->getID(), 1);
    update();
}

//Set commanded speed
void TrainModelDebugDialog::on_pushButton_10_clicked()
{
    QString s = ui->lineEdit_4->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        TrackModelInterface::getInstance().setCommandedSpeed(data->getID(), d);
        update();
    }
}

//Set beacon info
void TrainModelDebugDialog::on_pushButton_11_clicked()
{
    TrackModelInterface::getInstance().setBeaconInfo(data->getID(), ui->lineEdit_5->text());
}

/***Misc***/

//Set length
void TrainModelDebugDialog::on_pushButton_15_clicked()
{
    QString s = ui->lineEdit_8->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setLength(d);
        update();
    }
}

//Set height
void TrainModelDebugDialog::on_pushButton_16_clicked()
{
    QString s = ui->lineEdit_9->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setHeight(d);
        update();
    }
}

//Set Mass
void TrainModelDebugDialog::on_pushButton_17_clicked()
{
    QString s = ui->lineEdit_10->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setMass(d);
        update();
    }
}

//Set passengers
void TrainModelDebugDialog::on_pushButton_18_clicked()
{
    QString s = ui->lineEdit_11->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setPassengers(d);
        update();
    }
}

//Set crew
void TrainModelDebugDialog::on_pushButton_19_clicked()
{
    QString s = ui->lineEdit_12->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setCrew(d);
        update();
    }
}

