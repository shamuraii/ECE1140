#include "traincontrollerhandler.h"

TrainControllerHandler::TrainControllerHandler(QObject *parent) : QObject(parent)
{
    current_gui_index = -1;
    SetUpSignals();
    NewTrainController(0);
}

void TrainControllerHandler::SetUpSignals()
{
    TrainControllerSignalHandler *tcsh = &TrainControllerSignalHandler::Get();

    // Test gui and handler signal connection
    //Signals from train model
    QObject::connect(tcsh, &TrainControllerSignalHandler::TrainController, this, &TrainControllerHandler::NewTrainController);
    QObject::connect(tcsh, &TrainControllerSignalHandler::CommandedSpeed, this, &TrainControllerHandler::NewCommandedSpeed);
    QObject::connect(tcsh, &TrainControllerSignalHandler::ActualSpeed, this, &TrainControllerHandler::NewActualSpeed);
    //QObject::connect(tcsh, &TrainControllerSignalHandler::TCEmergencyBrake, this, &TrainControllerHandler::PassengerEmergencyBrake);
    QObject::connect(tcsh, &TrainControllerSignalHandler::Authority, this, &TrainControllerHandler::NewAuthority);
    QObject::connect(tcsh, &TrainControllerSignalHandler::BeaconInfo, this, &TrainControllerHandler::NewBeaconInfo);
    QObject::connect(tcsh, &TrainControllerSignalHandler::TCFailureMode, this, &TrainControllerHandler::FailureMode);
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

    // Signal for timer
    QObject::connect(tcsh, &TrainControllerSignalHandler::Timer, this, &TrainControllerHandler::TimerTicked);
}

void TrainControllerHandler::NewTrainController(int index)
{
    TrainController newTrain;
    trains.push_back(newTrain);

    qDebug() << "Emitted Gui new: " << index;
    emit GuiNewTrain(index);
    emit GuiTestNewTrain(index);

    if (index == 0)
    {
        current_gui_index = 0;
        current_test_gui_index = 0;
        emit GuiUpdate(newTrain);
        emit GuiTestUpdate(newTrain);
    }
}

void TrainControllerHandler::NewCommandedSpeed(int index, double speed)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    trains[index].commanded_speed = ConvertKMPHToMS(speed);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);

}

// Toggle service brake
void TrainControllerHandler::ToggleServiceBrake(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Toggles service brake
    trains[index].service_brake = !trains[index].service_brake;

    // If braking set commanded power to 0
    if (!trains[index].service_brake)
    {
         trains[index].power = 0;
         emit SendPower(index, trains[index].power);
    }

    // Send signal to train model
    emit ServiceBrake(index, trains[index].service_brake);

    // Update gui if needed
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);

}

// New actual speed received, calculate power
void TrainControllerHandler::NewActualSpeed(int index, double speed)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Converts the speed to m/s
    trains[index].actual_speed = ConvertKMPHToMS(speed);
    //Calculates power
    double power = trains[index].CalculatePower();

    // Handle train arriving at station
    //TODO: check if made_announcement is false
    if (trains[index].at_station)
        ArrivedAtStation(index);


    // Release brakes and close doors to leave station
    if (trains[index].leave_station)
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

    // Send new commanded power to train model
    emit SendPower(index, power);

    // Update Guis if needed
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
    if (current_test_gui_index == index)
        emit GuiTestUpdate(trains[index]);
}

void TrainControllerHandler::ToggleHeadlights(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;
    qDebug() << "Current index in headlights " << index;
    qDebug() << "Current gui index " << current_gui_index;
    // Toggles the headlights
    trains[index].headlights = !trains[index].headlights;

    // Sends headlight status to train
    emit Headlights(index, trains[index].headlights);

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Toggle cabin lights
void TrainControllerHandler::ToggleCabinLights(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Toggles the cabin lights
    trains[index].cabin_lights = !trains[index].cabin_lights;

    // Sends cabin light status to train
    emit CabinLights(index, trains[index].cabin_lights);

    // Update gui
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Set the cabin temperature
void TrainControllerHandler::SetCabinTemp(int index, double temp)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Sets the cabin temp
    trains[index].cabin_temp = temp;

    // Sends cabin temp to train
    emit CabinTemp(index, temp);

    // Update gui
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Send the announcements to train
void TrainControllerHandler::StartAnnouncement(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Train should be stopped before announcements start
//    if (trains[index].actual_speed != 0)
//        return;

    trains[index].made_announcement = true;
    emit Announcement(index, trains[index].announcement);
}

// Driver sets new setpoint speed
void TrainControllerHandler::NewSetpointSpeed(int index, double speed)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;
    speed = ConvertMPHToMS(speed);
    // Checks that the speed is valid
    if (speed < 0 || speed > 100 || speed > trains[index].commanded_speed)
        return;

    // Sets the new setpoint speed
    trains[index].setpoint_speed = speed;
    // Updates gui
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);

}

// Toggle left door
void TrainControllerHandler::ToggleLeftDoor(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Toggle door on train
    trains[index].left_door = !trains[index].left_door;
    emit LeftDoor(index, trains[index].left_door);

    // Update gui
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Toggle right door
void TrainControllerHandler::ToggleRightDoor(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Toggle door on train
    trains[index].right_door = !trains[index].right_door;
    emit RightDoor(index, trains[index].right_door);

    // Update gui
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Set Kp value
void TrainControllerHandler::SetKp(int index, double kp)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
        return;

    // Sets Kp value
    trains[index].kp = kp;

    // Update gui
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Set Ki value
void TrainControllerHandler::SetKi(int index, double ki)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Sets Ki value
    trains[index].ki = ki;

    // Update gui
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Emits signal to update gui to currently viewed train
void TrainControllerHandler::UpdateGui(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index || index < 0)
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

// Passenger pulls the emergency brake
void TrainControllerHandler::PassengerEmergencyBrake(int index)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

    // Turn ebrake on
    trains[index].emergency_brake = true;

    // Tell train model to turn ebrake on
    emit EmergencyBrake(index, trains[index].emergency_brake);

    // Update gui if necessary
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
    if (a == 0)
    {
        trains[index].service_brake = true;
        emit ServiceBrake(index, true);
    }

    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
    if (current_test_gui_index == index)
        emit GuiTestUpdate(trains[index]);
}

void TrainControllerHandler::FailureMode(int index, int failure)
{
    if (trains.size() == 0 || trains.size() <= (unsigned long long)index)
        return;

//    if (trains[index].emergency_brake)
//        ToggleEmergencyBrake(index);

//    NewAuthority(index,0);

    //trains[index].ResolveFailure(failure);

    switch(failure) {
        case 0: // brake failure
            // Activate ebrakes just for safety
            // Also results in power command of 0 being sent
            trains[index].emergency_brake = true;
            emit EmergencyBrake(index, true);
            break;
        case 1: //engine failure
            // Activate ebrakes
            // Also results in power command of 0 being sent
            trains[index].emergency_brake = true;
            emit EmergencyBrake(index, true);
            break;
        case 2: //Signal pickup failure
            NewAuthority(index, 0);
            break;
    }

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
        // Open doors
        if (trains[index].open_door == 1)
        {
            trains[index].left_door = true;
            emit LeftDoor(index, true);
        }
        else if (trains[index].open_door == 0)
        {
            trains[index].right_door = true;
            emit RightDoor(index, true);
        }
        else
        {
            trains[index].left_door = true;
            emit LeftDoor(index, true);
            trains[index].right_door = true;
            emit RightDoor(index, true);

        }
        // Make announcement
        StartAnnouncement(index);
    }
}

void TrainControllerHandler::ManualMode(int index)
{
    //cout << index << password;
    trains[index].manual_mode = !trains[index].manual_mode;
    if (current_gui_index == index)
        emit GuiUpdate(trains[index]);
}

// Utility function to convert kmph to m/s
double TrainControllerHandler::ConvertKMPHToMS(double speed)
{
    return speed * (5.0/18.0);
}

// Utility function to convert mph to m/s
double TrainControllerHandler::ConvertMPHToMS(double speed)
{
    return speed * 0.44704;
}

// Simulation timer for 1 second
void TrainControllerHandler::TimerTicked()
{
    for (int i = 0; i < trains.size(); i++)
    {
        trains[i].Timer();
    }

}
