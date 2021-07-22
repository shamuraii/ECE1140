#include "trackmodelsh.h"
#include "ui_trackmodelsignalhandler.h"

void TrackModelSH::getActualSpeed(int){}
void TrackModelSH::getDistanceTraveled(int){}
void TrackModelSH::getAuthority(int){}
void TrackModelSH::getCommandedSpeed(int){}

void TrackModelSH::getTimerTicked() {
    emit sendTimerTicked();
}

void TrackModelSH::getPTimerTicked() {
    emit sendPtimerTicked();
}
