#include "traincontrollersignalhandler.h"

// External signals from train model, sending signals to train controller
void TrainControllerSignalHandler::NewTrainController(int index)
{
    emit TrainController(index);
}

void TrainControllerSignalHandler::NewCommandedSpeed(int index, double speed)
{
    emit CommandedSpeed(index,speed);
}

void TrainControllerSignalHandler::NewActualSpeed(int index, double speed)
{
    emit ActualSpeed(index,speed);
}

void TrainControllerSignalHandler::ToggleEmergencyBrake(int index, bool state)
{
    emit TCEmergencyBrake(index, state);
}

// checking failure mode
//void TrainControllerSignalHandler::ToggleServiceBrake(int index, bool state)
//{
//    emit ServiceBrake(index, state);
//}

void TrainControllerSignalHandler::NewAuthority(int index, int auth)
{
    emit Authority(index, auth);
}

void TrainControllerSignalHandler::NewBeaconInfo(int index, QString info)
{
    emit BeaconInfo(index, info);
}

// Internal Signals from train controller, sending signals to train model
void TrainControllerSignalHandler::ServiceBrake(int index,bool state)
{
    emit NewServiceBrake(index, state);
}

void TrainControllerSignalHandler::SendPower(int index, double power)
{
    emit NewSendPower(index, power);
}

void TrainControllerSignalHandler::Headlights(int index, bool state)
{
    emit NewHeadlights(index, state);
}

void TrainControllerSignalHandler::CabinLights(int index, bool state)
{
    emit NewCabinLights(index, state);
}

void TrainControllerSignalHandler::CabinTemp(int index, double temp)
{
    emit NewCabinTemp(index, temp);
}

void TrainControllerSignalHandler::Announcement(int index, QString info)
{
    emit NewAnnouncement(index, info);
}

void TrainControllerSignalHandler::LeftDoor(int index, bool status)
{
    emit NewLeftDoor(index, status);
}

void TrainControllerSignalHandler::RightDoor(int index, bool status)
{
    emit NewRightDoor(index, status);
}

void TrainControllerSignalHandler::EmergencyBrake(int index, bool status)
{
    emit NewEmergencyBrake(index, status);
}
