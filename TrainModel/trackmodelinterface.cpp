#include "trackmodelinterface.h"
#include "controllerinterface.h"
#include "trainmodeldatabase.h"
#include <QDebug>

//These don't update my own GUI but it's debateable
//whether or not I'm going to display this anyway

void TrackModelInterface::setAuthority(int id, bool comm_auth)
{
    emit ControllerInterface::getInstance().authorityChanged(id, comm_auth);
}

void TrackModelInterface::setBeaconInfo(int id, QString info)
{
    emit ControllerInterface::getInstance().beaconInfoChanged(id, info);
}

void TrackModelInterface::setCommandedSpeed(int id, int comm_speed)
{
    emit ControllerInterface::getInstance().commandedSpeedChanged(id, comm_speed);
}

//long timer tick
//send distance traveled here
void TrackModelInterface::timerTicked()
{
    std::vector<TrainModelData*> trains = TrainModelDatabase::getAllTrains();
    for (auto train : trains)
    {
        //qDebug() << "Distance: " << train->getDistance();
        emit distanceTraveled(train->getID(), train->getDistance());
        train->setDistance(0);
    }
}

//short timer tick
//calculate power here
void TrackModelInterface::ptimerTicked()
{
    std::vector<TrainModelData*> trains = TrainModelDatabase::getAllTrains();
    for (auto train : trains)
    {
        //Assuming short timer ticks every 200ms
        train->tick(200);
    }
}
