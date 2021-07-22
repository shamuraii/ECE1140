#include "trainmodeldata.h"
#include "controllerinterface.h"

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
    mass = 3000;
    passengers = 200;
    crew = 8;
    speed_limit = 20;
    id = 1;

    brakes_on = ebrakes_on = engine_failure = signal_failure = brake_failure = false;
    left_doors = right_doors = door_side = false;
    headlights = cabin_lights = false;

    current_station = "Oakland Station";
    last_station = "Lawn St";
}

void TrainModelData::tick(int time)
{
    //Update speed based on power and brakes (TODO)
    actual_speed++;
    //Tell controller our speed changed
    emit ControllerInterface::getInstance().speedChanged(getID(), actual_speed);
    //Tell track model our speed changed (TODO)
    //If speed dropped to 0, tell CTC we've arrived at a station (TODO)
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

std::string TrainModelData::getAnnouncement()
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

std::string TrainModelData::getCurrentStation()
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

void TrainModelData::setBrakesOn(const bool& b)
{
    brakes_on = b;
}

void TrainModelData::setEbrakesOn(const bool& b)
{
    ebrakes_on = b;
}

void TrainModelData::setEngineFail(const bool& b)
{
    engine_failure = b;
}

void TrainModelData::setSignalFail(const bool& b)
{
    signal_failure = b;
}

void TrainModelData::setBrakeFail(const bool& b)
{
    brake_failure = b;
}

void TrainModelData::setCommandedPower(const unsigned int& i)
{
    power = i;
}

void TrainModelData::setCabinLights(const bool& b)
{
    cabin_lights = b;
}

void TrainModelData::setHeadlights(const bool& b)
{
    headlights = b;
}

void TrainModelData::setLeftDoors(const bool & b)
{
    left_doors = b;
}

void TrainModelData::setRightDoors(const bool & b)
{
    right_doors = b;
}

void TrainModelData::setCabinTemp(const unsigned int & i)
{
    cabin_temp = i;
}

void TrainModelData::setAnnouncement(const std::string & s)
{
    current_announcement = s;
}

void TrainModelData::setLength(const unsigned int & i)
{
    length = i;
}

void TrainModelData::setHeight(const unsigned int & i)
{
    height = i;
}

void TrainModelData::setMass(const unsigned int & i)
{
    mass = i;
}

void TrainModelData::setPassengers(const unsigned int & i)
{
    passengers = i;
}

void TrainModelData::setCrew(const unsigned int & i)
{
    crew = i;
}

void TrainModelData::setCurrentStation(const std::string& s)
{
    current_station = s;
}

void TrainModelData::setLastStation(const std::string& s)
{
    last_station = s;
}

void TrainModelData::setDoorSide(const bool& b)
{
    door_side = b;
}

void TrainModelData::setAuthority(const unsigned int& i)
{
    authority = i;
}

void TrainModelData::setCommandedSpeed(const unsigned int& i)
{
    commanded_speed = i;
}

void TrainModelData::setSpeedLimit(const unsigned int& i)
{
    speed_limit = i;
}

void TrainModelData::setAccelLimit(const unsigned int& i)
{
    accel_limit = i;
}

void TrainModelData::setDecelLimit(const unsigned int& i)
{
    decel_limit = i;
}

void TrainModelData::setActualSpeed(const float& i)
{
    actual_speed = i;
}

void TrainModelData::setID(const int& i)
{
    id = i;
}
