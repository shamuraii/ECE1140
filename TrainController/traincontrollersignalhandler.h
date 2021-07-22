#ifndef TRAINCONTROLLERSIGNALHANDLER_H
#define TRAINCONTROLLERSIGNALHANDLER_H

#include <QObject>
#include <string>
#include <iostream>

using namespace std;

class TrainControllerSignalHandler : public QObject
{
    Q_OBJECT
public:
    virtual ~ TrainControllerSignalHandler() {}

    // Static getter
    static TrainControllerSignalHandler & Get()
    {
        static TrainControllerSignalHandler instance;
        return instance;
    }

private:
    explicit TrainControllerSignalHandler(QObject * parent = nullptr){}

public slots:
    // External signals from train model
    void NewTrainController(int);
    void NewCommandedSpeed(int,double);
    void NewActualSpeed(int,double);
    void ToggleEmergencyBrake(int,bool);
    //void ToggleServiceBrake(int,bool); // Might use for failure
    void NewAuthority(int,int);
    //void FailureMode(int,string);
    void NewBeaconInfo(int,QString); // Talk with group

    // Internal signals from train controller
    void ServiceBrake(int,bool);
    void SendPower(int,double);
    void Headlights(int,bool);
    void CabinLights(int,bool);
    void CabinTemp(int,double);
    void Announcement(int,QString);
    void LeftDoor(int,bool);
    void RightDoor(int,bool);
    void EmergencyBrake(int,bool);

signals:
    // External signals to train model
    void NewServiceBrake(int,bool);
    void NewSendPower(int,double);
    void NewHeadlights(int,bool);
    void NewCabinLights(int,bool);
    void NewCabinTemp(int,double);
    void NewAnnouncement(int,QString);
    void NewLeftDoor(int,bool); // True open false close
    void NewRightDoor(int,bool);
    void NewEmergencyBrake(int,bool);

    // Internal signals to train controller
    void TrainController(int);
    void CommandedSpeed(int,double);
    void ActualSpeed(int,double);
    void TCEmergencyBrake(int,bool);
    // void ServiceBrake(int,bool); for failure mode
    void Authority(int,int);
    void BeaconInfo(int,QString);

};

#endif // TRAINCONTROLLERSIGNALHANDLER_H
