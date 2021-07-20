#include <vector>

#include "trainnetwork.h"
#include "ctc_constants.h"
#include "block.h"
#include "train.h"
#include "trackline.h"

TrainNetwork::TrainNetwork() : QObject(nullptr)
{
    automatic_mode_ = true;
}

std::vector<Train*> TrainNetwork::GetTrains() {
    return trains_;
}

Train *TrainNetwork::GetTrain(int train_num) {
    for (Train *t : trains_) {
        if (t->GetNum() == train_num)
            return t;
    }
    return nullptr;
}

TrackLine *TrainNetwork::GetTrackLine(QString line_name) {
    for (TrackLine *tl : lines_) {
        if (tl->GetName() == line_name)
            return tl;
    }
    return nullptr;
}

bool TrainNetwork::IsAutomatic() const {
    return automatic_mode_;
}

void TrainNetwork::DisableAutomatic() {
    automatic_mode_ = false;
}

void TrainNetwork::AddLine(TrackLine *new_line) {
    lines_.push_back(new_line);
}

void TrainNetwork::AddTrain(Train *new_train) {
    new_train->SetNum(NextTrainNum());
    trains_.push_back(new_train);
    connect(new_train, &Train::UpdatedLocation, this, &TrainNetwork::TrainMoved);
    emit TrainAdded(new_train->GetNum());
}

int TrainNetwork::NextTrainNum() const {
    int next = 1;
    for (Train *t : trains_) {
        int temp = t->GetNum();
        if (temp >= next)
            next = temp + 1;
    }
    return next;
}

void TrainNetwork::TrainMoved(Block *old_loc, Block *new_loc) {
    if (!old_loc->IsYard()) old_loc->SetOccupied(false);
    if (!new_loc->IsYard()) new_loc->SetOccupied(true);
    emit NetworkUpdated();
}

void TrainNetwork::UpdateWaysideOutputs() {
    std::vector<int> out_auth;
    std::vector<int> out_speed;

    for (int i = 0; i < GetTrackLine(kRedlineName)->GetBlockCount(); i++) {
        out_auth.push_back(0);
        out_speed.push_back(0);
    }

    for (Train *t : trains_) {
        out_auth[t->GetLocation()->GetNum()] = 1;
        out_auth[t->GetNextBlock()->GetNum()] = 1;

        out_speed[t->GetLocation()->GetNum()] = t->GetLocation()->GetSpeedLimit();
        out_speed[t->GetNextBlock()->GetNum()] = t->GetNextBlock()->GetSpeedLimit();
    }


}
