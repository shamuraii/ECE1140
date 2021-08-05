#include "trackmodelsh.h"
#include <QDebug>


void TrackModelSH::getDistanceTraveled(int trainNum, double distance){
    qDebug() << "TrackModel: Train Number: " << trainNum << " Distance:" << distance;
    emit sendDistanceTraveled(trainNum, distance);
}

void TrackModelSH::getAuthority(std::vector<bool> auth){
    qDebug() << "TrackModel: get auth vector: " << auth.size();
    emit sendAuthVector(auth);
}

void TrackModelSH::getCommandedSpeed(std::vector<int> comSpeed){
    qDebug() << "TrackModel:  get speed vector: " << comSpeed.size();
    emit sendSpeedVector(comSpeed);
}

void TrackModelSH::getTimerTicked() {
    sim_time_ = sim_time_.addSecs(1);
    emit sendTimerTicked(sim_time_);
}

void TrackModelSH::getPTimerTicked() {
    emit sendPtimerTicked();
}
void TrackModelSH::updateBlockInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line){
    qDebug() << "TrackModel:  " << speed_limits.size() << " " << lengths.size() << " " << line;
    emit sendTrackInfo(speed_limits, lengths, line);
}

void TrackModelSH::getCurrentBlockNum(int curr, int prev){
    qDebug() << "TrackModel:  Current Block: " << curr << " Prev Block: " << prev;
    emit sendCurrentBlockNum(curr, prev);
}

void TrackModelSH::getTrainAuthority(bool auth){
    qDebug() << "TrackModel:  Authority: " << auth;
    emit sendAuthority(1, auth);
}

void TrackModelSH::getTrainSpeed(int speed){
    qDebug() << "TrackModel:  Speed: " << speed;
    emit sendCommandedSpeed(1, speed);
}


void TrackModelSH::updateBeaconInfo(int trainNum, QString station){
    emit sendBeaconInfo(trainNum, station);
}
