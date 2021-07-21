#include "trainmodeldatabase.h"

int TrainModelDatabase::id_count = 0;
std::vector<TrainModelData*> TrainModelDatabase::trains;

TrainModelData* TrainModelDatabase::getTrainByID(int id)
{
    for (unsigned int i = 0; i < trains.size(); i++)
    {
        if (trains[i]->getID() == id) return trains[i];
    }
    return nullptr;
}

int TrainModelDatabase::createTrain()
{
    id_count++;
    TrainModelData* d = new TrainModelData;
    d->setID(id_count);
    trains.push_back(d);
    return id_count;
}
