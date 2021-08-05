#include "traincontroller.h"

TrainController::TrainController()
{
    service_brake = false;
    emergency_brake = false;
    manual_mode = false;
    failure_mode = false;
    setpoint_speed = 0;
    announcement = "";
    headlights = false;
    cabin_lights = false;
    left_door = false;
    right_door = false;
    cabin_temp = 70;
    actual_speed = 0;
    kp = 35000;
    ki = 1000;
    commanded_speed = 0;
    authority = 0;
    open_door = -1;
    power = 0;
    leave_station = false;
    made_announcement = false;
    station_here = false;

    // Variables for Power Loop
    prev_error = 0;
    prev_u = 0;
    T = 0.4;
    max_power = 120000;
    previous_power = 0;

    // Variable for stopping at station
    wait_counter = 0;
    leave_station = false;

}


double TrainController::CalculatePower()
{
    // No power calculation occurs if a brake is on, a failure mode is occuring, or authority is 0
    if (service_brake || emergency_brake || failure_mode || !authority)
    {
        power = 0;
        //return power;
    }
    else
    {
        double error;

        if (manual_mode)
            error = setpoint_speed - actual_speed;
        else
            error = commanded_speed - actual_speed;

        double u;
        if (previous_power < max_power)
            u = prev_u + (T/2.0)*(error + prev_error);
        else
            u = prev_u;

        power = kp*error + ki*u;
        previous_power = power;

        if(power > max_power)
            power = max_power;

        prev_error = error;
    }
    AtStation();
    return power;
}


void TrainController::AtStation()
{
    // Checks if train has just stopped
    if (station_here && actual_speed == 0 && !at_station)
    {
        at_station = true;
        made_announcement = false;
        wait_counter = 0;
        // Start time to wait for 60 seconds
    }
    //Checks if train has waited enough at station
    else if (station_here && at_station && actual_speed == 0 && !leaving_station)
    {
        //Check if 60 seconds went by
        if (wait_counter > 10)
        {
            // flag to close doors and start power command again
            leave_station = true;
            // flag saying leaving is in progress
            leaving_station = true;
        }
    }
    // Train left the station
    else if (station_here && at_station && actual_speed != 0)
    {
        at_station = false;
        leaving_station = false;
    }

}

void TrainController::GrabBeaconInfo(QString info)
{
    QStringList splitted = info.split(",");
    announcement = "Arriving at " + splitted[0];
    if (splitted[1] == "Right")
        open_door = 0;
    else if (splitted[1] == "Left")
        open_door = 1;
    else
        open_door = 2;
    station_here = !station_here;
}

void TrainController::Timer()
{
    if (at_station)
        wait_counter += 1;
}
