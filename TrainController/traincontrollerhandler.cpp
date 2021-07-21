#include "traincontrollerhandler.h"

TrainControllerHandler::TrainControllerHandler(QObject *parent) : QObject(parent)
{
    current_gui_index = -1;
    SetUpSignals();
}

void TrainControllerHandler::SetUpSignals()
{
    // Test gui and handler signal connection
    //Signals from train model
    QObject::connect(&TrainControllerSignalHandler::Get(), SIGNAL(TrainController(int)), this, SLOT(NewTrainController(int)));
    QObject::connect(&TrainControllerSignalHandler::Get(), SIGNAL(CommandedSpeed(int,double)), this, SLOT(NewCommandedSpeed(int,double)));
    QObject::connect(&TrainControllerSignalHandler::Get(), SIGNAL(ActualSpeed(int,double)), this, SLOT(NewActualSpeed(int,double)));
    //QObject::connect(&TrainControllerSignalHandler::Get(), SIGNAL(TCEmergencyBrake(int, bool)), this, SLOT(ToggleEmergencyBrake(int, bool))); Emergency brake pull from user
    QObject::connect(&TrainControllerSignalHandler::Get(), SIGNAL(Authority(int,int)), this, SLOT(NewAuthority(int,int)));
    QObject::connect(&TrainControllerSignalHandler::Get(), SIGNAL(BeaconInfo(int,string)), this, SLOT(NewBeaconInfo(int,string)));
//    QObject::connect(&TrainControllerSignalHandler::Get(), SIGNAL(FailureMode(int,string)), this, SLOT(FailureMode(int,string)));
    // Future might have service brake to check for failure mode

    // Signals to train model
    QObject::connect(this, SIGNAL(ServiceBrake(int,bool)), &TrainControllerSignalHandler::Get(), SLOT(ServiceBrake(int,bool)));
    QObject::connect(this, SIGNAL(EmergencyBrake(int,bool)), &TrainControllerSignalHandler::Get(), SLOT(EmergencyBrake(int,bool)));
    QObject::connect(this, SIGNAL(SendPower(int,double)), &TrainControllerSignalHandler::Get(), SLOT(SendPower(int,double)));
    QObject::connect(this, SIGNAL(Headlights(int,bool)), &TrainControllerSignalHandler::Get(), SLOT(Headlights(int,bool)));
    QObject::connect(this, SIGNAL(CabinLights(int,bool)), &TrainControllerSignalHandler::Get(), SLOT(CabinLights(int,bool)));
    QObject::connect(this, SIGNAL(CabinTemp(int,double)), &TrainControllerSignalHandler::Get(), SLOT(CabinTemp(int,double)));
    QObject::connect(this, SIGNAL(LeftDoor(int,bool)), &TrainControllerSignalHandler::Get(), SLOT(LeftDoor(int,bool)));
    QObject::connect(this, SIGNAL(RightDoor(int,bool)), &TrainControllerSignalHandler::Get(), SLOT(RightDoor(int,bool)));\
    QObject::connect(this, SIGNAL(Announcement(int,string)), &TrainControllerSignalHandler::Get(), SLOT(Announcement(int,string)));
}

void TrainControllerHandler::NewTrainController(int id)
{
    TrainController newTrain;
    trains.push_back(newTrain);
    cout << "\nNew Train. Id = " << id << "\n";

    emit GuiNewTrain(id);

    if (id ==1)
    {
        current_gui_index = 0;
        current_test_gui_index = 0;
        emit GuiUpdate(newTrain);
        emit GuiTestUpdate(newTrain);
    }
}

void TrainControllerHandler::NewCommandedSpeed(int index, double speed)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    trains[index].commanded_speed = speed;

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);

}

void TrainControllerHandler::ToggleServiceBrake(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    trains[index].service_brake = !trains[index].service_brake;
    trains[index].power = 0;

    emit ServiceBrake(index, trains[index].service_brake);
    emit SendPower(index, 0);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);

}

void TrainControllerHandler::NewActualSpeed(int index, double speed)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    trains[index].actual_speed = speed;
    double power = trains[index].CalculatePower();

    // Handle train arriving at station
    if (trains[index].at_station)
        ArrivedAtStation(index);


    // Release brakes and close doors to leave station
    if (trains[index].leave_station && trains[index].actual_speed == 0)
    {
        // Close doors to train
        trains[index].left_door = false;
        trains[index].right_door = false;
        emit LeftDoor(index, false);
        emit RightDoor(index, false);

        // Release brake
        trains[index].service_brake = false;
        emit ServiceBrake(index, false);

        trains[index].leave_station = false;
    }

    emit SendPower(index, power);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
    if (current_test_gui_index == index)
        emit GuiTestUpdate(trains[index]);
}

void TrainControllerHandler::ToggleHeadlights(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Toggles the headlights
    trains[index].headlights = !trains[index].headlights;

    // Sends headlight status to train
    emit Headlights(index, trains[index].headlights);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

void TrainControllerHandler::ToggleCabinLights(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Toggles the cabin lights
    trains[index].cabin_lights = !trains[index].cabin_lights;

    // Sends cabin light status to train
    emit CabinLights(index, trains[index].cabin_lights);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

void TrainControllerHandler::SetCabinTemp(int index, double temp)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Sets the cabin temp
    trains[index].cabin_temp = temp;

    // Sends cabin temp to train
    emit CabinTemp(index, temp);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

void TrainControllerHandler::StartAnnouncement(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Train should be stopped before announcements start
    if (trains[index].actual_speed != 0)
        return;

    emit Announcement(index, trains[index].announcement);
}

void TrainControllerHandler::NewSetpointSpeed(int index, double speed)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Checks that the speed is valid
    if (speed < 0 || speed > 100 || speed > trains[index].commanded_speed)
        return;

    // Sets the new setpoint speed
    trains[index].setpoint_speed = speed;
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);

}

void TrainControllerHandler::ToggleLeftDoor(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    trains[index].left_door = !trains[index].left_door;

    // Toggle door on train
    emit LeftDoor(index, trains[index].left_door);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

void TrainControllerHandler::ToggleRightDoor(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    trains[index].right_door = !trains[index].right_door;

    // Toggle door on train
    emit RightDoor(index, trains[index].right_door);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

void TrainControllerHandler::SetKp(int index, double kp)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Sets Kp value
    trains[index].kp = kp;

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

void TrainControllerHandler::SetKi(int index, double ki)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Sets Ki value
    trains[index].ki = ki;

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Emits signal to update gui to currently viewed train
void TrainControllerHandler::UpdateGui(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    emit GuiUpdate(trains[index]);

    current_gui_index = index;
}

// Toggles the emergency brake and updates gui if neccessary
void TrainControllerHandler::ToggleEmergencyBrake(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    trains[index].emergency_brake = !trains[index].emergency_brake;

    emit EmergencyBrake(index, trains[index].emergency_brake);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Emits signal to update gui to currently viewed train
void TrainControllerHandler::UpdateTestGui(int index)
{

    emit GuiTestUpdate(trains[index]);

    current_test_gui_index = index;
}

void TrainControllerHandler::NewAuthority(int index, int a)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    trains[index].authority = a;
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
    if (current_test_gui_index == index)
        emit GuiTestUpdate(trains[index]);
}

void TrainControllerHandler::FailureMode(int index, string failure)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

//    if (trains[index].emergency_brake)
//        ToggleEmergencyBrake(index);

//    NewAuthority(index,0);

    trains[index].ResolveFailure(failure);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
    if (current_test_gui_index == index)
        emit GuiTestUpdate(trains[index]);
}

void TrainControllerHandler::NewBeaconInfo(int index, string info)
{
    cout << index << info;
}

void TrainControllerHandler::ArrivedAtStation(int index)
{
    if (!trains[index].made_announcement)
    {
        if (trains[index].open_door)
        {
            trains[index].left_door = true;
            emit LeftDoor(index, true);
        }
        else
        {
            trains[index].right_door = true;
            emit RightDoor(index, false);
        }
        StartAnnouncement(index);
    }
}

void TrainControllerHandler::ManualMode(int index, string password)
{
    cout << index << password;
}

