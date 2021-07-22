#include "trainmodeldebugdialog.h"
#include "ui_trainmodeldebugdialog.h"

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
        data->setCommandedPower(d);
        update();
    }
}

//Send Announcement
void TrainModelDebugDialog::on_pushButton_7_clicked()
{
    data->setAnnouncement(ui->lineEdit_3->text());
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
        data->setCabinTemp(d);
        update();
    }
}

//Toggle service brakes
void TrainModelDebugDialog::on_pushButton_8_clicked()
{
    data->setBrakesOn(!data->getBrakesOn());
    update();
}

//Toggle headlights
void TrainModelDebugDialog::on_pushButton_4_clicked()
{
    data->setHeadlights(!data->getHeadlights());
    update();
}

//Toggle cabin lights
void TrainModelDebugDialog::on_pushButton_3_clicked()
{
    data->setCabinLights(!data->getCabinLights());
    update();
}

//Toggle right door
void TrainModelDebugDialog::on_pushButton_2_clicked()
{
    data->setRightDoors(!data->getRightDoors());
    update();
}

//Toggle left door
void TrainModelDebugDialog::on_pushButton_clicked()
{
    data->setLeftDoors(!data->getLeftDoors());
    update();
}

/***Track Model***/

//Toggle Authority
void TrainModelDebugDialog::on_pushButton_9_clicked()
{
    if (data->getAuthority()) data->setAuthority(0);
    else data->setAuthority(1);
    update();
}

//Toggle door side
void TrainModelDebugDialog::on_pushButton_14_clicked()
{
    data->setDoorSide(!data->getDoorSide());
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
        data->setCommandedSpeed(d);
        update();
    }
}

//Set speed limit
void TrainModelDebugDialog::on_pushButton_11_clicked()
{
    QString s = ui->lineEdit_5->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setSpeedLimit(d);
        update();
    }
}

//Set current station name
void TrainModelDebugDialog::on_pushButton_12_clicked()
{
    data->setCurrentStation(ui->lineEdit_6->text().toStdString());
    update();
}

//Set last station name
void TrainModelDebugDialog::on_pushButton_13_clicked()
{
    data->setLastStation(ui->lineEdit_7->text().toStdString());
    update();
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

//Set accel limit
void TrainModelDebugDialog::on_pushButton_20_clicked()
{
    QString s = ui->lineEdit_13->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setAccelLimit(d);
        update();
    }
}

//Set decel limit
void TrainModelDebugDialog::on_pushButton_21_clicked()
{
    QString s = ui->lineEdit_14->text();
    bool worked;
    int d = s.toInt(&worked);
    if(worked)
    {
        data->setDecelLimit(d);
        update();
    }
}

