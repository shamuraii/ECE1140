#include "controllerinterface.h"
#include "trainmodeldatabase.h"
#include "trainmodeldata.h"

#include <QDebug>

void ControllerInterface::setCommandedPower(int id, double power)
{
    qDebug() << "Train Model received power: " << power;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setCommandedPower(power);
}

void ControllerInterface::setLeftDoor(int id, bool d)
{
    qDebug() << "Train Model received left door: " << d;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setLeftDoors(d);
}

void ControllerInterface::setRightDoor(int id, bool d)
{
    qDebug() << "Train Model received right door: " << d;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setRightDoors(d);
}

void ControllerInterface::setCabinLights(int id, bool l)
{
    qDebug() << "Train Model received cabin lights: " << l;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setCabinLights(l);
}

void ControllerInterface::setHeadlights(int id, bool l)
{
    qDebug() << "Train Model received headlights: " << l;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setHeadlights(l);
}

void ControllerInterface::setAnnouncement(int id, QString a)
{
    qDebug() << "Train Model received announcement: " << a;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setAnnouncement(a);
}

void ControllerInterface::setServiceBrake(int id, bool b)
{
    qDebug() << "Train Model received service brake: " << b;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr)
    {
        data->setBrakesOn(b);
        emit serviceBrakeChanged(id, data->getBrakesOn());
    }
}

void ControllerInterface::setEBrake(int id, bool b)
{
    qDebug() << "Train Model received e brake: " << b;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr)
    {
        data->setEbrakesOn(b);
        emit eBrakeChanged(id, data->getEbrakesOn());
    }
}

void ControllerInterface::setCabinTemp(int id, int temp)
{
    qDebug() << "Train Model received cabin temp: " << temp;
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    if (data != nullptr) data->setCabinTemp(temp);
}

ControllerInterface& ControllerInterface::getInstance()
{
    static ControllerInterface c;
    return c;
}
