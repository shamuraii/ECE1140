#ifndef TRAINMODELDATA_H
#define TRAINMODELDATA_H

#include <string>
#include <QObject>
#include <QElapsedTimer>

class TrainModelData : public QObject
{
    Q_OBJECT
public:
    TrainModelData();

    //Tick for speed calculation
    void tick(int);

    //A ridiculous amount of getters and setters
    unsigned int getCommandedPower();
    unsigned int getActualPower();
    unsigned int getCommandedSpeed();
    float getActualSpeed();
    unsigned int getAuthority();
    unsigned int getAccelLimit();
    unsigned int getDecelLimit();
    bool getCabinLights();
    bool getHeadlights();
    bool getBrakesOn();
    bool getEbrakesOn();
    bool getEngineFail();
    bool getSignalFail();
    bool getBrakeFail();
    bool getLeftDoors();
    bool getRightDoors();
    unsigned int getCabinTemp();
    QString getAnnouncement();
    unsigned int getLength();
    unsigned int getHeight();
    unsigned int getMass();
    unsigned int getPassengers();
    unsigned int getCrew();
    std::string getCurrentStation();
    std::string getLastStation();
    bool getDoorSide();
    int getID();
    unsigned int getSpeedLimit();
    double getDistance();

    void setBrakesOn(const bool&);
    void setEbrakesOn(const bool&);
    void setEngineFail(const bool&);
    void setSignalFail(const bool&);
    void setBrakeFail(const bool&);
    void setCommandedPower(const unsigned int&);
    void setCabinLights(const bool&);
    void setHeadlights(const bool&);
    void setLeftDoors(const bool&);
    void setRightDoors(const bool&);
    void setCabinTemp(const unsigned int&);
    void setAnnouncement(const QString&);
    void setLength(const unsigned int&);
    void setHeight(const unsigned int&);
    void setMass(const unsigned int&);
    void setPassengers(const unsigned int&);
    void setCrew(const unsigned int&);
    void setCurrentStation(const std::string&);
    void setLastStation(const std::string&);
    void setDoorSide(const bool&);
    void setAuthority(const unsigned int&);
    void setCommandedSpeed(const unsigned int&);
    void setSpeedLimit(const unsigned int&);
    void setAccelLimit(const unsigned int&);
    void setDecelLimit(const unsigned int&);
    void setActualSpeed(const float&);
    void setID(const int&);
    void setDistance(const double&);

signals:
    void dataChanged();

private:
    //Brakes and fail states
    bool brakes_on, ebrakes_on, engine_failure, signal_failure, brake_failure;

    //Movement info
    unsigned int power, commanded_speed, authority, accel_limit, decel_limit;
    unsigned int speed_limit;
    float actual_speed;
    double distance;
    QElapsedTimer timer;

    //Beacon info
    std::string current_station, last_station;
    bool door_side;

    //Physical properties
    unsigned int length, height, mass, passengers, crew, id, cabin_temp;  //TODO: find relevant physical info
    bool left_doors, right_doors, lights, headlights, cabin_lights;

    //Misc
    QString current_announcement;
};

#endif // TRAINMODELDATA_H
