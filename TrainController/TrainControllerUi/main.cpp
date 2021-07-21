#include "traincontrollerui.h"
#include "qcontroller.h"
#include "traincontrollerhandler.h"
#include "testui.h"
#include <iostream>


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrainControllerUi w;
    TestUi testui;

    TrainControllerHandler trainHandler;

    // Train gui and handler singal connection
    QObject::connect(&trainHandler, SIGNAL(GuiUpdate(TrainController)), &w, SLOT(Update(TrainController)));
    QObject::connect(&trainHandler, SIGNAL(GuiNewTrain(int)), &w, SLOT(NewTrain(int)));
    QObject::connect(&w, SIGNAL(ToggleServiceBrake(int)), &trainHandler, SLOT(ToggleServiceBrake(int)));
    QObject::connect(&w, SIGNAL(ToggleEmergencyBrake(int)), &trainHandler, SLOT(ToggleEmergencyBrake(int)));
    QObject::connect(&w, SIGNAL(ToggleHeadlights(int)), &trainHandler, SLOT(ToggleHeadlights(int)));
    QObject::connect(&w, SIGNAL(ToggleCabinLights(int)), &trainHandler, SLOT(ToggleCabinLights(int)));
    QObject::connect(&w, SIGNAL(SetCabinTemp(int,double)), &trainHandler, SLOT(SetCabinTemp(int,double)));
    QObject::connect(&w, SIGNAL(ToggleLeftDoor(int)), &trainHandler, SLOT(ToggleLeftDoor(int)));
    QObject::connect(&w, SIGNAL(ToggleRightDoor(int)), &trainHandler, SLOT(ToggleRightDoor(int)));
    QObject::connect(&w, SIGNAL(SetKp(int,double)), &trainHandler, SLOT(SetKp(int,double)));
    QObject::connect(&w, SIGNAL(SetKi(int,double)), &trainHandler, SLOT(SetKi(int,double)));
    QObject::connect(&w, SIGNAL(UpdateGui(int)), &trainHandler, SLOT(UpdateGui(int)));
    QObject::connect(&w, SIGNAL(StartAnnouncement(int)), &trainHandler, SLOT(StartAnnouncement(int)));
    QObject::connect(&w, SIGNAL(NewSetpointSpeed(int,double)), &trainHandler, SLOT(NewSetpointSpeed(int,double)));


    // Test gui and handler signal connection
    QObject::connect(&testui, SIGNAL(NewTrain(int)), &trainHandler, SLOT(NewTrainController(int)));
    QObject::connect(&testui, SIGNAL(NewCommandedSpeed(int,double)), &trainHandler, SLOT(NewCommandedSpeed(int,double)));
    QObject::connect(&trainHandler, SIGNAL(ServiceBrake(int,bool)), &testui, SLOT(ServiceBrake(int,bool)));
    QObject::connect(&trainHandler, SIGNAL(EmergencyBrake(int,bool)), &testui, SLOT(EmergencyBrake(int,bool)));
    QObject::connect(&trainHandler, SIGNAL(SendPower(int,double)), &testui, SLOT(NewPower(int,double)));
    QObject::connect(&testui, SIGNAL(NewActualSpeed(int,double)), &trainHandler, SLOT(NewActualSpeed(int,double)));
    QObject::connect(&trainHandler, SIGNAL(Headlights(int,bool)), &testui, SLOT(Headlights(int,bool)));
    QObject::connect(&trainHandler, SIGNAL(CabinLights(int,bool)), &testui, SLOT(CabinLights(int,bool)));
    QObject::connect(&trainHandler, SIGNAL(CabinTemp(int,double)), &testui, SLOT(CabinTemp(int,double)));
    QObject::connect(&trainHandler, SIGNAL(LeftDoor(int,bool)), &testui, SLOT(LeftDoor(int,bool)));
    QObject::connect(&trainHandler, SIGNAL(RightDoor(int,bool)), &testui, SLOT(RightDoor(int,bool)));\
    QObject::connect(&testui, SIGNAL(ToggleEmergencyBrake(int)), &trainHandler, SLOT(ToggleEmergencyBrake(int)));
    QObject::connect(&trainHandler, SIGNAL(Announcement(int,string)), &testui, SLOT(Announcement(int,string)));
    QObject::connect(&trainHandler, SIGNAL(GuiTestUpdate(TrainController)), &testui, SLOT(UpdateTest(TrainController)));
    QObject::connect(&testui, SIGNAL(UpdateTestGui(int)), &trainHandler, SLOT(UpdateTestGui(int)));
    QObject::connect(&testui, SIGNAL(NewAuthority(int,int)), &trainHandler, SLOT(NewAuthority(int,int)));
    QObject::connect(&testui, SIGNAL(FailureMode(int,string)), &trainHandler, SLOT(FailureMode(int,string)));

    // trainHandler.NewTrainController(1);

    w.show();
    testui.show();

    return a.exec();
}
