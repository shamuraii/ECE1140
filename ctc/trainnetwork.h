#ifndef TRAINNETWORK_H
#define TRAINNETWORK_H

#include <QObject>
#include <vector>

#include "ctrain.h"
#include "trackline.h"

namespace ctc {

class TrainNetwork : public QObject
{
    Q_OBJECT
private:
    std::vector<CTrain*> trains_;
    std::vector<TrackLine*> lines_;
    bool automatic_mode_;

    int NextTrainNum() const;
public:
    explicit TrainNetwork();

    std::vector<CTrain*> GetTrains();
    CTrain *GetTrain(int train_num);
    TrackLine *GetTrackLine(QString line_name);
    bool IsAutomatic() const;

    void AddLine(TrackLine *new_line);
    void AddTrain(CTrain *new_train);
    void DisableAutomatic();


public slots:
    // From debugger
    void TrainMoved(Block *old_loc, Block *new_loc);

    // From CtcSH
    void UpdateOutputs();
    void SwitchMoved(int pointing_to, bool line);
    void UpdateOccupancy(std::vector<bool> occupancy, bool line);
    void TrainStopped(int train_num);
    void SetTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);

signals:
    void OutputsUpdated(std::vector<bool> out_auth, std::vector<int> out_speed, bool line);
    void NetworkUpdated();
    void TrainAdded(int num, bool line);
};
}

#endif // TRAINNETWORK_H
