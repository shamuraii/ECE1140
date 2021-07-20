#ifndef TRAINNETWORK_H
#define TRAINNETWORK_H

#include <QObject>
#include <vector>

#include "train.h"
#include "trackline.h"

class TrainNetwork : public QObject
{
    Q_OBJECT
private:
    std::vector<Train*> trains_;
    std::vector<TrackLine*> lines_;
    bool automatic_mode_;

    int NextTrainNum() const;
public:
    explicit TrainNetwork();

    std::vector<Train*> GetTrains();
    Train *GetTrain(int train_num);
    TrackLine *GetTrackLine(QString line_name);
    bool IsAutomatic() const;

    void AddLine(TrackLine *new_line);
    void AddTrain(Train *new_train);
    void DisableAutomatic();


public slots:
    void TrainMoved(Block *old_loc, Block *new_loc);
    void UpdateWaysideOutputs();

signals:
    //void WaysideOutputsUpdated(std::vector<QPair<int, int>> out_auth, std::vector<QPair<int, int>> out_speed);
    void NetworkUpdated();
    void TrainAdded(int num);
};

#endif // TRAINNETWORK_H
