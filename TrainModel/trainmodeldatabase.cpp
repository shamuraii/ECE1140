#include "trainmodeldatabase.h"

std::vector<TrainModelData*> TrainModelDatabase::trains;

TrainModelData* TrainModelDatabase::getTrainByID(int id)
{
    for (unsigned int i = 0; i < trains.size(); i++)
    {
        if (trains[i]->getID() == id) return trains[i];
    }
    return nullptr;
}

std::vector<TrainModelData*> TrainModelDatabase::getAllTrains()
{
    return trains;
}

void TrainModelDatabase::createTrain(int id)
{
    TrainModelData* d = new TrainModelData;
    d->setID(id);
    trains.push_back(d);
}
