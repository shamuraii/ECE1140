#include "trainmodeldata.h"
#include "controllerinterface.h"
#include "trackmodelinterface.h"
#include <math.h>
#include <QDebug>

//TODO setter should send update signal to GUIs

TrainModelData::TrainModelData()
{
    power = 0;
    commanded_speed = 0;
    actual_speed = 0;
    authority = 0;
    accel_limit = 5;
    decel_limit = 5;
    length = 100;
    height = 12;
    mass = 100000;
    passengers = 200;
    crew = 8;
    speed_limit = 20;
    id = 1;
    distance = 0;
    cabin_temp = 70;

    brakes_on = ebrakes_on = engine_failure = signal_failure = brake_failure = false;
    left_doors = right_doors = door_side = false;
    headlights = cabin_lights = false;

    current_station = "Oakland Station";
    last_station = "Lawn St";
}

void TrainModelData::tick(int time)
{
    //Update speed based on power and brakes
    //From Kinetic Energy = 1/2 * m * v^2
    //v = sqrt(2*E/m)

    /*
     *  Service Brake deceleration: 1.2m/s^2 -> 2.68mph/s
     *  E Brake deceleration: 2.73m/s^2 -> 6.11mph/s
     *  Medium acceleration: 0.5m/s^2 -> 1.12mph/s
     *  Mass is in pounds (1 lb = .454 kg)
     *  Speed is in m/s (1 m/s = 2.237 mph)
     *  Time is in ms
    */

    //Update times and distance
    distance += actual_speed*0.001*timer.restart();

    bool wasMoving = actual_speed > 0;
    double current_energy = .5 * .454 * mass * actual_speed * actual_speed;
    current_energy += 0.001 * time * power;
    actual_speed = sqrt(2 * current_energy / (.454 * mass));
    if (ebrakes_on) actual_speed -= 0.001*2.73*time;
    else if (brakes_on) actual_speed -= 0.001*1.2*time;
    if (actual_speed < 0) actual_speed = 0;

    qDebug() << "Train Model speed changed to: " << 3.6*actual_speed << "kmh";

    //Update GUI
    emit dataChanged();

    //Tell controller our speed changed in kmh
    emit ControllerInterface::getInstance().speedChanged(getID(), 3.6*actual_speed);

    //Tell track model our speed changed (TODO) (Moved to long tick)

    //If speed dropped to 0, tell CTC we've arrived at a station (TODO)
    if (wasMoving && actual_speed == 0)
    {
        qDebug() << "Train Model stopped...telling CTC";
        emit TrackModelInterface::getInstance().trainStopped(getID());
    }
}

unsigned int TrainModelData::getCommandedPower()
{
    return power;
}

unsigned int TrainModelData::getActualPower()
{
    return power;
}

unsigned int TrainModelData::getCommandedSpeed()
{
    return commanded_speed;
}

float TrainModelData::getActualSpeed()
{
    return actual_speed;
}

unsigned int TrainModelData::getAuthority()
{
    return authority;
}

unsigned int TrainModelData::getAccelLimit()
{
    return accel_limit;
}

unsigned int TrainModelData::getDecelLimit()
{
    return decel_limit;
}

bool TrainModelData::getCabinLights()
{
    return cabin_lights;
}

bool TrainModelData::getHeadlights()
{
    return headlights;
}

bool TrainModelData::getBrakesOn()
{
    return brakes_on;
}

bool TrainModelData::getEbrakesOn()
{
    return ebrakes_on;
}

bool TrainModelData::getEngineFail()
{
    return engine_failure;
}

bool TrainModelData::getSignalFail()
{
    return signal_failure;
}

bool TrainModelData::getBrakeFail()
{
    return brake_failure;
}

bool TrainModelData::getLeftDoors()
{
    return left_doors;
}

bool TrainModelData::getRightDoors()
{
    return right_doors;
}

unsigned int TrainModelData::getCabinTemp()
{
    return cabin_temp;
}

QString TrainModelData::getAnnouncement()
{
    return current_announcement;
}

unsigned int TrainModelData::getLength()
{
    return length;
}

unsigned int TrainModelData::getHeight()
{
    return height;
}

unsigned int TrainModelData::getMass()
{
    return mass;
}

unsigned int TrainModelData::getPassengers()
{
    return passengers;
}

unsigned int TrainModelData::getCrew()
{
    return crew;
}

QString TrainModelData::getCurrentStation()
{
    return current_station;
}

std::string TrainModelData::getLastStation()
{
    return last_station;
}

bool TrainModelData::getDoorSide()
{
    return door_side;
}

int TrainModelData::getID()
{
    return id;
}

unsigned int TrainModelData::getSpeedLimit()
{
    return speed_limit;
}

double TrainModelData::getDistance()
{
    //Add distance up to now as well
    distance += actual_speed*0.001*timer.restart();
    return distance;
}

void TrainModelData::setBrakesOn(const bool& b)
{
    brakes_on = b;
    emit dataChanged();
}

void TrainModelData::setEbrakesOn(const bool& b)
{
    ebrakes_on = b;
    emit dataChanged();
}

void TrainModelData::setEngineFail(const bool& b)
{
    engine_failure = b;
    emit dataChanged();
}

void TrainModelData::setSignalFail(const bool& b)
{
    signal_failure = b;
    emit dataChanged();
}

void TrainModelData::setBrakeFail(const bool& b)
{
    brake_failure = b;
    emit dataChanged();
}

void TrainModelData::setCommandedPower(const unsigned int& i)
{
    power = i;
    emit dataChanged();
}

void TrainModelData::setCabinLights(const bool& b)
{
    cabin_lights = b;
    emit dataChanged();
}

void TrainModelData::setHeadlights(const bool& b)
{
    headlights = b;
    emit dataChanged();
}

void TrainModelData::setLeftDoors(const bool & b)
{
    left_doors = b;
    emit dataChanged();
}

void TrainModelData::setRightDoors(const bool & b)
{
    right_doors = b;
    emit dataChanged();
}

void TrainModelData::setCabinTemp(const unsigned int & i)
{
    cabin_temp = i;
    emit dataChanged();
}

void TrainModelData::setAnnouncement(const QString& s)
{
    current_announcement = s;
    emit dataChanged();
}

void TrainModelData::setLength(const unsigned int & i)
{
    length = i;
    emit dataChanged();
}

void TrainModelData::setHeight(const unsigned int & i)
{
    height = i;
    emit dataChanged();
}

void TrainModelData::setMass(const unsigned int & i)
{
    mass = i;
    emit dataChanged();
}

void TrainModelData::setPassengers(const unsigned int & i)
{
    passengers = i;
    emit dataChanged();
}

void TrainModelData::setCrew(const unsigned int & i)
{
    crew = i;
    emit dataChanged();
}

void TrainModelData::setCurrentStation(const QString& s)
{
    current_station = s;
    emit dataChanged();
}

void TrainModelData::setLastStation(const std::string& s)
{
    last_station = s;
    emit dataChanged();
}

void TrainModelData::setDoorSide(const bool& b)
{
    door_side = b;
    emit dataChanged();
}

void TrainModelData::setAuthority(const unsigned int& i)
{
    authority = i;
    emit dataChanged();
}

void TrainModelData::setCommandedSpeed(const unsigned int& i)
{
    commanded_speed = i;
    emit dataChanged();
}

void TrainModelData::setSpeedLimit(const unsigned int& i)
{
    speed_limit = i;
    emit dataChanged();
}

void TrainModelData::setAccelLimit(const unsigned int& i)
{
    accel_limit = i;
    emit dataChanged();
}

void TrainModelData::setDecelLimit(const unsigned int& i)
{
    decel_limit = i;
    emit dataChanged();
}

void TrainModelData::setActualSpeed(const float& i)
{
    actual_speed = i;
    emit dataChanged();
}

void TrainModelData::setID(const int& i)
{  
    id = i;
    emit dataChanged();
}

void TrainModelData::setDistance(const double& d)
{
    distance = d;
}
