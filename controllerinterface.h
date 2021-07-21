#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <QObject>
#include <string>

//Static singleton class containing slots for the Train Controller

//Train Controller should be able to send a train the following data:
//commanded power, left door, right door, cabin lights, headlights
//announcement, service brake, ebrake, cabin temp

//Train Controller should receive the following data:
//speed, service brake, ebrake, commanded authority
//commanded speed, beacon info

//All data receiving slots take the ID of the recipient train along with the data

class ControllerInterface : public QObject
{
    Q_OBJECT
private:
    ControllerInterface() {}
public slots:
    //Incoming data slots
    void setCommandedPower(int, double);
    void setLeftDoor(int, bool);
    void setRightDoor(int, bool);
    void setCabinLights(int, bool);
    void setHeadlights(int, bool);
    void setAnnouncement(int, std::string);
    void setServiceBrake(int, bool);
    void setEBrake(int, bool);
    void setCabinTemp(int, int);
signals:
    //Outgoing data signals
    void newTrain(int);
    void speedChanged(int, double);
    void serviceBrakeChanged(int, bool);
    void eBrakeChanged(int, bool);
    void authorityChanged(int, int);
    void commandedSpeedChanged(int, double);
    void beaconInfoChanged(int, std::string);
public:
    static ControllerInterface& getInstance();
    ControllerInterface(const ControllerInterface&) = delete;
    void operator=(const ControllerInterface&) = delete;
};

#endif // CONTROLLERINTERFACE_H
