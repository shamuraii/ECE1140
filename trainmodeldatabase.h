#ifndef TRAINMODELDATABASE_H
#define TRAINMODELDATABASE_H

#include <vector>
#include <trainmodeldata.h>

class TrainModelDatabase
{
private:
    static std::vector<TrainModelData*> trains;
    static int id_count;

    TrainModelDatabase() {}
public:
    static TrainModelData* getTrainByID(int);
    static int createTrain();
};

#endif // TRAINMODELDATABASE_H
