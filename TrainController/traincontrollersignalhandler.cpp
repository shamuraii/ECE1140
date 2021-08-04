#include "traincontrollersignalhandler.h"

// External signals from train model, sending signals to train controller
void TrainControllerSignalHandler::NewTrainController(int index)
{
    emit TrainController(index-1);
}

void TrainControllerSignalHandler::NewCommandedSpeed(int index, double speed)
{
    emit CommandedSpeed(index-1,speed);
    qDebug() << "TC new commanded speed " << speed;
}

void TrainControllerSignalHandler::NewActualSpeed(int index, double speed)
{
    emit ActualSpeed(index-1,speed);
    qDebug() << "TC new actual speed " << speed;
}

void TrainControllerSignalHandler::ToggleEmergencyBrake(int index, bool state)
{
    emit TCEmergencyBrake(index-1, state);
    qDebug() << "Passenger pulled ebrake " << state;
}

// checking failure mode
//void TrainControllerSignalHandler::ToggleServiceBrake(int index, bool state)
//{
//    emit ServiceBrake(index, state);
//}

// Failure mode
void TrainControllerSignalHandler::FailureMode(int index, int failure)
{
    qDebug() << "TC Failure mode received " << failure;
    emit TCFailureMode(index, failure);
}

void TrainControllerSignalHandler::NewAuthority(int index, int auth)
{
    emit Authority(index-1, auth);
    qDebug() << "TC new authority" << auth;
}

void TrainControllerSignalHandler::NewBeaconInfo(int index, QString info)
{
    emit BeaconInfo(index-1, info);
    qDebug() << "TC new beacon info";
}

// Internal Signals from train controller, sending signals to train model
void TrainControllerSignalHandler::ServiceBrake(int index,bool state)
{
    emit NewServiceBrake(index+1, state);
    qDebug() << "TC telling train to brake " << state;
}

void TrainControllerSignalHandler::SendPower(int index, double power)
{
    emit NewSendPower(index+1, power);
    qDebug() << "TC sending power" << power;
}

void TrainControllerSignalHandler::Headlights(int index, bool state)
{
    emit NewHeadlights(index+1, state);
    qDebug() << "TC toggle headlights " << state;
}

void TrainControllerSignalHandler::CabinLights(int index, bool state)
{
    emit NewCabinLights(index+1, state);
    qDebug() << "TC toggle cabin lights " << state;
}

void TrainControllerSignalHandler::CabinTemp(int index, double temp)
{
    emit NewCabinTemp(index+1, temp);
}

void TrainControllerSignalHandler::Announcement(int index, QString info)
{
    emit NewAnnouncement(index, info);
    qDebug() << "TC make announcement";
}

void TrainControllerSignalHandler::LeftDoor(int index, bool status)
{
    emit NewLeftDoor(index+1, status);
    qDebug() << "TC toggle left door " << status;
}

void TrainControllerSignalHandler::RightDoor(int index, bool status)
{
    emit NewRightDoor(index+1, status);
    qDebug() << "TC toggle right door " << status;
}

void TrainControllerSignalHandler::EmergencyBrake(int index, bool status)
{
    qDebug() << "TC tell train to toggle ebrake " << status;
    emit NewEmergencyBrake(index+1, status);
}

void TrainControllerSignalHandler::TimerTicked()
{
    emit Timer();
}
