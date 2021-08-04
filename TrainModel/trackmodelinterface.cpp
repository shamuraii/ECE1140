#include "trackmodelinterface.h"
#include "controllerinterface.h"
#include "trainmodeldatabase.h"
#include <QDebug>

void TrackModelInterface::setAuthority(int id, bool comm_auth)
{
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    data->setAuthority(comm_auth);
    qDebug() << "Train Model received authority: " << comm_auth;
    emit ControllerInterface::getInstance().authorityChanged(id, comm_auth);
}

void TrackModelInterface::setBeaconInfo(int id, QString info)
{
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    data->setCurrentStation(info);
    qDebug() << "Train Model received beacon info: " << info;
    emit ControllerInterface::getInstance().beaconInfoChanged(id, info);
}

void TrackModelInterface::setCommandedSpeed(int id, int comm_speed)
{
    TrainModelData* data = TrainModelDatabase::getTrainByID(id);
    data->setCommandedSpeed(comm_speed);
    qDebug() << "Train Model received commanded speed: " << comm_speed;
    emit ControllerInterface::getInstance().commandedSpeedChanged(id, comm_speed);
}

//long timer tick
//send distance traveled and stopping distance here
void TrackModelInterface::timerTicked()
{
    std::vector<TrainModelData*> trains = TrainModelDatabase::getAllTrains();
    for (auto train : trains)
    {
        qDebug() << "Train #" << train->getID() << " sending distance: " << train->getDistance();
        emit distanceTraveled(train->getID(), train->getDistance());
		emit stoppingDistance(train->getID(), train->getActualSpeed()*train->getActualSpeed()*0.5*(1/1.2));
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

void TrackModelInterface::createTrain(int id)
{
	//Who creates train id???
	int newID = TrainModelDatabase::createTrain(id);
	emit newTrain(id);
}
