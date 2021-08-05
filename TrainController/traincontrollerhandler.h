#ifndef TRAINCONTROLLERHANDLER_H
#define TRAINCONTROLLERHANDLER_H

#include <QObject>
#include <vector>
#include "traincontroller.h"
#include "traincontrollersignalhandler.h"

class TrainControllerHandler : public QObject
{
    Q_OBJECT
public:
    explicit TrainControllerHandler(QObject *parent = nullptr);
    vector<TrainController> trains;

public slots:
    void NewTrainController(int);
    void NewCommandedSpeed(int,double);
    void ToggleServiceBrake(int);
    void NewActualSpeed(int,double);
    void ToggleHeadlights(int);
    void ToggleCabinLights(int);
    void SetCabinTemp(int,double);
    void StartAnnouncement(int);
    void NewSetpointSpeed(int,double);
    void ToggleLeftDoor(int);
    void ToggleRightDoor(int);
    void SetKp(int,double);
    void SetKi(int,double);
    void UpdateGui(int);
    void ToggleEmergencyBrake(int);
    void PassengerEmergencyBrake(int);
    void UpdateTestGui(int);
    void NewAuthority(int,int);
    void FailureMode(int, int);
    void EndFailure(int);
    void NewBeaconInfo(int,QString);
    void ArrivedAtStation(int);
    void ManualMode(int);
    void TimerTicked();

private:
    int current_gui_index;
    int current_test_gui_index;

    void SetUpSignals();
    double ConvertKMPHToMS(double);
    double ConvertMPHToMS(double);
    vector<TrainController> redundancy_trains;

signals:
    void GuiUpdate(TrainController);
    void GuiNewTrain(int);
    void GuiTestNewTrain(int);
    void ServiceBrake(int,bool);
    void SendPower(int,double);
    void Headlights(int,bool);
    void CabinLights(int,bool);
    void CabinTemp(int,double);
    void Announcement(int,QString);
    void LeftDoor(int,bool);
    void RightDoor(int,bool);
    void GuiTestUpdate(TrainController);
    void EmergencyBrake(int,bool);
};

#endif // TRAINCONTROLLERHANDLER_H
