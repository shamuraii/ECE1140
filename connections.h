#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <QObject>
#include <QTimer>

#include "ctc/ctc_signal_handler.h"
#include "TrackController/wssh.h"
#include "TrackModel/trackmodelsh.h"
#include "TrainModel/controllerinterface.h"
#include "TrainModel/trackmodelinterface.h"
#include "TrainController/traincontrollersignalhandler.h"

void ConnectSystem() {
    CtcSH *ctc = &CtcSH::Get();
    wssh *ws = &wssh::Get();
    TrackModelSH *tmsh = &TrackModelSH::Get();
    TrackModelInterface *tmi = &TrackModelInterface::getInstance();
    ControllerInterface *ci = &ControllerInterface::getInstance();
    TrainControllerSignalHandler *tcsh = &TrainControllerSignalHandler::Get();

    // Timer Events
    QObject::connect(tmsh, &TrackModelSH::sendTimerTicked, ctc, &CtcSH::TimedEvents);
    QObject::connect(tmsh, &TrackModelSH::sendTimerTicked, ws, &wssh::TimerTicked);
    QObject::connect(tmsh, &TrackModelSH::sendTimerTicked, tmi, &TrackModelInterface::timerTicked);
    QObject::connect(tmsh, &TrackModelSH::sendPtimerTicked, tmi, &TrackModelInterface::ptimerTicked);
    QObject::connect(tmsh, &TrackModelSH::sendTimerTicked, tcsh, &TrainControllerSignalHandler::TimerTicked);

    // CTC - Wayside
    QObject::connect(ctc, &CtcSH::ShareSugAuthority, ws, &wssh::SetSugAuthority);
    QObject::connect(ctc, &CtcSH::ShareSugSpeed, ws, &wssh::SetSugSpeed);
    QObject::connect(ctc, &CtcSH::ShareBlockMaintenance, ws, &wssh::SetBlockMaintenance);
    //QObject::connect(ctc, &CtcSH::ShareSwitchMaintenance, ws, &wssh::SetSwitchMaintenance);
    //QObject::connect(ctc, &CtcSH::ShareSwitchPosition, ws, &wssh::SetSwitchPosition);

    QObject::connect(ws, &wssh::ShareSwitchPosition, ctc, &CtcSH::GetSwitchPosition);
    QObject::connect(ws, &wssh::ShareTrainPresence, ctc, &CtcSH::GetTrainLocation);

    // CTC - Track Model
    QObject::connect(tmsh, &TrackModelSH::sendTrackInfo, ctc, &CtcSH::GetTrackInfo);
    QObject::connect(tmsh, &TrackModelSH::sendLineSales, ctc, &CtcSH::GetLineSales);

    // CTC - Train Model
    QObject::connect(tmi, &TrackModelInterface::trainStopped, ctc, &CtcSH::GetTrainStopped);

    // Wayside - Track Model
    QObject::connect(ws, &wssh::ShareAuthority, tmsh, &TrackModelSH::getAuthority);
    QObject::connect(ws, &wssh::ShareCommSpeed, tmsh, &TrackModelSH::getCommandedSpeed);
    //QObject::connect(ws, &wssh::ShareSwitchPosTM, tmsh, &TrackModelSH::getSwitchPosition);

    QObject::connect(tmsh, &TrackModelSH::sendCurrentBlockNum, ws, &wssh::SetTrainPresence);
    //QObject::connect(tmsh, &TrackModelSH::sendBrokenRail, ws, &wssh::SetBrokenRail);

    // Track Model - Train Model
    QObject::connect(tmsh, &TrackModelSH::sendAuthority, tmi, &TrackModelInterface::setAuthority);
    QObject::connect(tmsh, &TrackModelSH::sendBeaconInfo, tmi, &TrackModelInterface::setBeaconInfo);
    QObject::connect(tmsh, &TrackModelSH::sendCommandedSpeed, tmi, &TrackModelInterface::setCommandedSpeed);

    QObject::connect(tmi, &TrackModelInterface::distanceTraveled, tmsh, &TrackModelSH::getDistanceTraveled);

    // Train Model - Train Controller
    QObject::connect(ci, &ControllerInterface::newTrain, tcsh, &TrainControllerSignalHandler::NewTrainController);
    QObject::connect(ci, &ControllerInterface::speedChanged, tcsh, &TrainControllerSignalHandler::NewActualSpeed);
    //QObject::connect(ci, &ControllerInterface::serviceBrakeChanged, tcsh, &TrainControllerSignalHandler::);
    QObject::connect(ci, &ControllerInterface::eBrakeChanged, tcsh, &TrainControllerSignalHandler::ToggleEmergencyBrake);
    QObject::connect(ci, &ControllerInterface::authorityChanged, tcsh, &TrainControllerSignalHandler::NewAuthority);
    QObject::connect(ci, &ControllerInterface::commandedSpeedChanged, tcsh, &TrainControllerSignalHandler::NewCommandedSpeed);
    QObject::connect(ci, &ControllerInterface::beaconInfoChanged, tcsh, &TrainControllerSignalHandler::NewBeaconInfo);

    QObject::connect(tcsh, &TrainControllerSignalHandler::NewServiceBrake, ci, &ControllerInterface::setServiceBrake);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewSendPower, ci, &ControllerInterface::setCommandedPower);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewHeadlights, ci, &ControllerInterface::setHeadlights);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewCabinLights, ci, &ControllerInterface::setCabinLights);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewCabinTemp, ci, &ControllerInterface::setCabinTemp);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewAnnouncement, ci, &ControllerInterface::setAnnouncement);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewLeftDoor, ci, &ControllerInterface::setLeftDoor);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewRightDoor, ci, &ControllerInterface::setRightDoor);
    QObject::connect(tcsh, &TrainControllerSignalHandler::NewEmergencyBrake, ci, &ControllerInterface::setEBrake);
}

#endif // CONNECTIONS_H
