#ifndef TRAINMODELDATABASE_H
#define TRAINMODELDATABASE_H

#include <vector>
#include "trainmodeldata.h"

class TrainModelDatabase
{
private:
    static std::vector<TrainModelData*> trains;

    TrainModelDatabase() {}
public:
    static TrainModelData* getTrainByID(int);
    static std::vector<TrainModelData*> getAllTrains();
    static void createTrain(int);
};

#endif // TRAINMODELDATABASE_H
