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

    // Variable for stopping at station
    wait_counter = 0;
    leave_station = false;

}

void TrainController::ResolveFailure(QString failure)
{
    std::cout << "Resolving failure";
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

        double u = prev_u + (T/2.0)*(error + prev_error);

        power = kp*error + ki*u;

        double check_power = CheckPowerCalculation(prev_error, prev_u);

        if(power > max_power)
            power = max_power;
        else
            prev_u = u;

        prev_error = error;

        if (power != check_power)
        {
            cout << "Power loop miscalculation";
            power = 0;
        }

    }
    AtStation();
    return power;
}

double TrainController::CheckPowerCalculation(double p_e, double p_u)
{
    double e;

    if (manual_mode)
        e = setpoint_speed - actual_speed;
    else
        e = commanded_speed - actual_speed;

    double u = p_u + (T/2.0)*(e + p_e);

    double new_power = kp*e + ki*u;

    if (new_power > max_power)
        new_power = max_power;
    return new_power;


}

void TrainController::AtStation()
{
    // Checks if train has just stopped
    if (station_here && actual_speed == 0 && !at_station)
    {
        at_station = true;
        made_announcement = false;
        // Start time to wait for 60 seconds
    }

    //Checks if train has waited enough at station
    else if (station_here && at_station && actual_speed == 0 && !leaving_station)
    {
        //Check if 60 seconds went by
        if (wait_counter > 60)
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
