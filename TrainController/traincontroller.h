#ifndef TRAINCONTROLLER_H
#define TRAINCONTROLLER_H

#include <string>
#include <iostream>
#include <QString>
#include <QStringList>

using namespace std;

class TrainController
{
public:
    TrainController();

    void ResolveFailure(QString);
    double CalculatePower();
    void GrabBeaconInfo(QString);
    void AtStation();

    bool service_brake;
    bool emergency_brake;
    bool manual_mode;
    bool failure_mode;
    double setpoint_speed;
    QString announcement;
    bool headlights;
    bool cabin_lights;
    bool left_door;
    bool right_door;
    double cabin_temp;
    double actual_speed;
    double kp;
    double ki;
    double commanded_speed;
    int authority;
    int open_door;
    double power;
    bool leave_station;
    bool made_announcement;
    bool at_station;

private:
    double prev_u;
    double prev_error;
    double T;
    double max_power;
    bool station_here;

    double CheckPowerCalculation(double,double);


};

#endif // TRAINCONTROLLER_H
