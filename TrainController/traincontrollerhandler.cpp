#include "traincontrollerhandler.h"

TrainControllerHandler::TrainControllerHandler(QObject *parent) : QObject(parent)
{
    current_gui_index = -1;
    SetUpSignals();
    NewTrainController(1);
}

void TrainControllerHandler::SetUpSignals()
{
    TrainControllerSignalHandler *tcsh = &TrainControllerSignalHandler::Get();

    // Test gui and handler signal connection
    //Signals from train model
    QObject::connect(tcsh, &TrainControllerSignalHandler::TrainController, this, &TrainControllerHandler::NewTrainController);
    QObject::connect(tcsh, &TrainControllerSignalHandler::CommandedSpeed, this, &TrainControllerHandler::NewCommandedSpeed);
    QObject::connect(tcsh, &TrainControllerSignalHandler::ActualSpeed, this, &TrainControllerHandler::NewActualSpeed);
    //QObject::connect(tcsh, &TrainControllerSignalHandler::TCEmergencyBrake, this, &TrainControllerHandler::ToggleEmergencyBrake); Emergency brake pull from user
    QObject::connect(tcsh, &TrainControllerSignalHandler::Authority, this, &TrainControllerHandler::NewAuthority);
    QObject::connect(tcsh, &TrainControllerSignalHandler::BeaconInfo, this, &TrainControllerHandler::NewBeaconInfo);
//    QObject::connect(tcsh, &TrainControllerSignalHandler::FailureMode, this, &TrainControllerHandler::FailureMode);
    // Future might have service brake to check for failure mode

    // Signals to train model
    QObject::connect(this, &TrainControllerHandler::ServiceBrake, tcsh, &TrainControllerSignalHandler::ServiceBrake);
    QObject::connect(this, &TrainControllerHandler::EmergencyBrake, tcsh, &TrainControllerSignalHandler::EmergencyBrake);
    QObject::connect(this, &TrainControllerHandler::SendPower, tcsh, &TrainControllerSignalHandler::SendPower);
    QObject::connect(this, &TrainControllerHandler::Headlights, tcsh, &TrainControllerSignalHandler::Headlights);
    QObject::connect(this, &TrainControllerHandler::CabinLights, tcsh, &TrainControllerSignalHandler::CabinLights);
    QObject::connect(this, &TrainControllerHandler::CabinTemp, tcsh, &TrainControllerSignalHandler::CabinTemp);
    QObject::connect(this, &TrainControllerHandler::LeftDoor, tcsh, &TrainControllerSignalHandler::LeftDoor);
    QObject::connect(this, &TrainControllerHandler::RightDoor, tcsh, &TrainControllerSignalHandler::RightDoor);
    QObject::connect(this, &TrainControllerHandler::Announcement, tcsh, &TrainControllerSignalHandler::Announcement);
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

void TrainControllerHandler::FailureMode(int index, QString failure)
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

void TrainControllerHandler::NewBeaconInfo(int index, QString info)
{
    //cout << index << info;
    trains[index].GrabBeaconInfo(info);
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

void TrainControllerHandler::ManualMode(int index, QString password)
{
    //cout << index << password;
    trains[index].manual_mode = !trains[index].manual_mode;
}

