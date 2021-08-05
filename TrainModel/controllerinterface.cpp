#include "controllerinterface.h"
#include "trainmodeldatabase.h"
#include "trainmodeldata.h"

#include <QDebug>

void ControllerInterface::setCommandedPower(int id, double power)
{
    qDebug() << "Train #" << id << " received power: " << power;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setCommandedPower(power);
}

void ControllerInterface::setLeftDoor(int id, bool d)
{
    qDebug() << "Train #" << id << " received left door: " << d;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setLeftDoors(d);
}

void ControllerInterface::setRightDoor(int id, bool d)
{
    qDebug() << "Train #" << id << " received right door: " << d;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setRightDoors(d);
}

void ControllerInterface::setCabinLights(int id, bool l)
{
    qDebug() << "Train #" << id << " received cabin lights: " << l;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setCabinLights(l);
}

void ControllerInterface::setHeadlights(int id, bool l)
{
    qDebug() << "Train #" << id << " received headlights: " << l;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setHeadlights(l);
}

void ControllerInterface::setAnnouncement(int id, QString a)
{
    qDebug() << "Train #" << id << " received announcement: " << a;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setAnnouncement(a);
}

void ControllerInterface::setServiceBrake(int id, bool b)
{
    qDebug() << "Train #" << id << " received service brake: " << b;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr)
    {
        data->setBrakesOn(b);
        emit serviceBrakeChanged(id, data->getBrakesOn());
    }
}

void ControllerInterface::setEBrake(int id, bool b)
{
    qDebug() << "Train #" << id << " received e brake: " << b;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setEbrakesOn(b);
}

void ControllerInterface::setCabinTemp(int id, int temp)
{
    qDebug() << "Train #" << id << " received cabin temp: " << temp;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setCabinTemp(temp);
}
