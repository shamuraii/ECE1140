#include "trackmodelsh.h"

#include <QDebug>


void TrackModelSH::getDistanceTraveled(int trainNum, double distance){
    emit sendDistanceTraveled(trainNum, distance);
}

void TrackModelSH::getAuthority(std::vector<bool> auth){
    qDebug() << "TrackM entered getAuthority";
    //get the authority at block
    //emit sendAuthority(1, auth);
}

void TrackModelSH::getCommandedSpeed(std::vector<int> comSpeed){
    qDebug() << "TrackM entered getCommandedSpeed";
    //get where train is
   // emit sendCommandedSpeed();
}

void TrackModelSH::getTimerTicked() {
    emit sendTimerTicked();
}

void TrackModelSH::getPTimerTicked() {
    emit sendPtimerTicked();
}
void TrackModelSH::updateBlockInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line){
    emit sendTrackInfo(speed_limits, lengths, line);
}

void TrackModelSH::getCurrentBlockNum(int curr, int prev){
    emit sendCurrentBlockNum(curr, prev);
}
