#include <vector>

#include "trainnetwork.h"
#include "ctc_constants.h"
#include "block.h"
#include "ctrain.h"
#include "trackline.h"
#include "ctc_signal_handler.h"

using namespace ctc;

TrainNetwork::TrainNetwork() : QObject(nullptr)
{
    automatic_mode_ = true;

    connect(this, &TrainNetwork::OutputsUpdated, &CtcSH::Get(), &CtcSH::OutputsUpdated);
    connect(&CtcSH::Get(), &CtcSH::UpdateOutputs, this, &TrainNetwork::UpdateOutputs);
    connect(&CtcSH::Get(), &CtcSH::NewSwitchPos, this, &TrainNetwork::SwitchMoved);
    connect(&CtcSH::Get(), &CtcSH::NewOccupancies, this, &TrainNetwork::UpdateOccupancy);
    connect(&CtcSH::Get(), &CtcSH::NewTrackInfo, this, &TrainNetwork::SetTrackInfo);
}

std::vector<CTrain*> TrainNetwork::GetTrains() {
    return trains_;
}

CTrain *TrainNetwork::GetTrain(int train_num) {
    for (CTrain *t : trains_) {
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

void TrainNetwork::AddTrain(CTrain *new_train) {
    new_train->SetNum(NextTrainNum());
    trains_.push_back(new_train);
    connect(new_train, &CTrain::UpdatedLocation, this, &TrainNetwork::TrainMoved);
    emit TrainAdded(new_train->GetNum());
}

int TrainNetwork::NextTrainNum() const {
    int next = 1;
    for (CTrain *t : trains_) {
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

void TrainNetwork::UpdateOutputs() {
    for (CTrain *t : trains_) {
        t->UpdateOutputs();
    }
    TrackLine *line = GetTrackLine(kRedlineName);
    std::vector<bool> out_auth;
    std::vector<int> out_speed;

    for (Block *b : line->GetBlocks()) {
        out_auth.push_back(b->GetAuth());
        out_speed.push_back(b->GetSpeed());
    }
    emit OutputsUpdated(out_auth, out_speed, kRedBool);

    // TODO: green line
}

void TrainNetwork::SwitchMoved(int pointing_to, bool line) {
    if (line == kRedBool) {
        TrackLine *l = GetTrackLine(kRedlineName);
        for (Switch *s : l->GetSwitches()) {
            if (s->HasBlock(pointing_to))
                s->UpdateState(pointing_to, line);
        }
    }
    // TODO: green line
}

void TrainNetwork::UpdateOccupancy(std::vector<bool> occupancy, bool line) {
    //TODO: this is BROKEN for 2 lines
    if (line == kRedBool) {
        TrackLine *l = GetTrackLine(kRedlineName);
        std::vector<Block*> blocks = l->GetBlocks();
        for (size_t i = 0; i < occupancy.size(); i++) {
            bool prev = blocks[i+1]->IsOccupied();
            bool now = occupancy[i];

            blocks[i+1]->SetOccupied(now);

            if (prev && !now) {
                for (CTrain *t : trains_) {
                    if (t->GetLocation()->GetNum() == blocks[i+1]->GetNum()) {
                        t->SetLocation(t->GetNextBlock());
                    }
                }
            }
        }
    }
}

void TrainNetwork::TrainStopped(int train_num) {
    CTrain *t = GetTrain(train_num);
    t->TrainStopped();
}

void TrainNetwork::SetTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line) {
    if (line == kRedBool) {
        qDebug() << "CTC: Setting Track Info";
        TrackLine *l = GetTrackLine(kRedlineName);
        std::vector<Block*> blocks = l->GetBlocks();
        for (size_t i=0; i < speed_limits.size(); i++) {
            blocks[i+1]->SetInfo(speed_limits[i], lengths[i]);
            qDebug() << blocks[i+1]->GetNum() << " " << blocks[i+1]->GetSpeedLimit();
        }
    }
    // TODO: green line
}
