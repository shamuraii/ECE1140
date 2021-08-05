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
    connect(this, &TrainNetwork::TrainAdded, &CtcSH::Get(), &CtcSH::TrainScheduled);
    connect(this, &TrainNetwork::TrainDispatched, &CtcSH::Get(), &CtcSH::TrainDispatched);
    connect(&CtcSH::Get(), &CtcSH::UpdateOutputs, this, &TrainNetwork::UpdateOutputs);
    connect(&CtcSH::Get(), &CtcSH::RecalculateRoutes, this, &TrainNetwork::RecalculateRoutes);
    connect(&CtcSH::Get(), &CtcSH::RecalculateThroughput, this, &TrainNetwork::CalculateThroughputs);
    connect(&CtcSH::Get(), &CtcSH::CheckTrainDepartures, this, &TrainNetwork::CheckDepartures);
    connect(&CtcSH::Get(), &CtcSH::TrainStopped, this, &TrainNetwork::TrainStopped);

    connect(&CtcSH::Get(), &CtcSH::NewLineSales, this, &TrainNetwork::AddLineSales);
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
    connect(new_train, &CTrain::DebugMovedTrain, this, &TrainNetwork::TrainMoved);

    bool l_bool = (new_train->GetLine()->GetName() == kRedlineName ? kRedBool : kGreenBool);
    emit TrainAdded(new_train->GetNum(), l_bool);
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
    TrackLine *rline = GetTrackLine(kRedlineName);
    std::vector<bool> r_out_auth;
    std::vector<int> r_out_speed;

    for (Block *b : rline->GetBlocks()) {
        r_out_auth.push_back(b->GetAuth());
        r_out_speed.push_back(b->GetSpeed());
    }
    emit OutputsUpdated(r_out_auth, r_out_speed, kRedBool);

    TrackLine *gline = GetTrackLine(kGreenlineName);
    std::vector<bool> g_out_auth;
    std::vector<int> g_out_speed;

    for (Block *b : gline->GetBlocks()) {
        g_out_auth.push_back(b->GetAuth());
        g_out_speed.push_back(b->GetSpeed());
    }
    emit OutputsUpdated(g_out_auth, g_out_speed, kGreenBool);
}

void TrainNetwork::RecalculateRoutes() {
    for (CTrain *t : trains_)
        t->RecalculateRoute();
}

void TrainNetwork::SwitchMoved(int pointing_to, bool line) {
    if (line == kRedBool) {
        TrackLine *l = GetTrackLine(kRedlineName);
        for (Switch *s : l->GetSwitches()) {
            if (s->HasBlock(pointing_to))
                s->UpdateState(pointing_to, line);
        }
    }
    if (line == kGreenBool) {
        TrackLine *l = GetTrackLine(kGreenlineName);
        for (Switch *s : l->GetSwitches()) {
            if (s->HasBlock(pointing_to))
                s->UpdateState(pointing_to, line);
        }
    }
}

void TrainNetwork::UpdateOccupancy(std::vector<bool> occupancy, bool line) {
    if (line == kRedBool) {
        TrackLine *l = GetTrackLine(kRedlineName);
        std::vector<Block*> blocks = l->GetBlocks();


        for (size_t i = 0; i < 11; i++) {
            qDebug() << occupancy[i];
        }


        for (size_t i = 0; i < occupancy.size(); i++) {

            bool prev = blocks[i]->IsOccupied();
            bool now = occupancy[i];

            blocks[i]->SetOccupied(now);
            if (now) {
                qDebug() << "CTC: Redline Block " << i << " occupied";
            }

            if (prev && !now) {
                qDebug() << "CTC: Redline Block " << i << " lost a train";
                for (CTrain *t : trains_) {
                    if (t->GetLine()->GetName() == kRedlineName && t->GetLocation()->GetNum() == blocks[i]->GetNum()) {
                        qDebug() << "CTC: Redline train from " << i << " to " << t->GetNextBlock()->GetNum();
                        t->SetLocation(t->GetNextBlock());
                        t->IncrementRouteIndex();
                    }
                }
            }
        }
    } else {
        TrackLine *l = GetTrackLine(kGreenlineName);
        std::vector<Block*> blocks = l->GetBlocks();

        /*
        for (size_t i = 0; i < 11; i++) {
            qDebug() << occupancy[i];
        }
        */

        for (size_t i = 0; i < occupancy.size(); i++) {

            bool prev = blocks[i]->IsOccupied();
            bool now = occupancy[i];

            blocks[i]->SetOccupied(now);
            if (now) {
                qDebug() << "CTC: Greenline Block " << i << " occupied";
            }

            if (prev && !now) {
                qDebug() << "CTC: Greenline Block " << i << " lost a train";
                for (CTrain *t : trains_) {
                    if (t->GetLine()->GetName() == kGreenlineName && t->GetLocation()->GetNum() == blocks[i]->GetNum()) {
                        qDebug() << "CTC: Greenline train from " << i << " to " << t->GetNextBlock()->GetNum();
                        t->SetLocation(t->GetNextBlock());
                        t->IncrementRouteIndex();
                    }
                }
            }
        }
    }
    emit NetworkUpdated();
}

void TrainNetwork::TrainStopped(int train_num) {
    CTrain *t = GetTrain(train_num);
    t->TrainStopped();
}

void TrainNetwork::SetTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line) {
    if (line == kRedBool) {
        qDebug() << "CTC: Setting RedLine Info";
        TrackLine *l = GetTrackLine(kRedlineName);
        std::vector<Block*> blocks = l->GetBlocks();
        for (size_t i=0; i < speed_limits.size(); i++) {
            blocks[i+1]->SetInfo(speed_limits[i], lengths[i]);
            qDebug() << blocks[i+1]->GetNum() << " " << blocks[i+1]->GetSpeedLimit();
        }
    } else {
        qDebug() << "CTC: Setting GreenLine Info";
        TrackLine *l = GetTrackLine(kGreenlineName);
        std::vector<Block*> blocks = l->GetBlocks();
        for (size_t i=0; i < speed_limits.size(); i++) {
            blocks[i+1]->SetInfo(speed_limits[i], lengths[i]);
            qDebug() << blocks[i+1]->GetNum() << " " << blocks[i+1]->GetSpeedLimit();
        }
    }
}

void TrainNetwork::CheckDepartures(QTime sim_time) {
    for(CTrain *t : trains_) {
        qDebug() << "Depart time: " << t->GetDepartTime().toString("HH:mm") << " SimTime: " << sim_time.toString("HH:mm");
        if (t->GetDepartTime() <= sim_time) {
            if (t->DispatchTrain()) {
                bool line_bool = (t->GetLine()->GetName() == kRedlineName) ? kRedBool : kGreenBool;
                emit TrainDispatched(t->GetNum(), line_bool);
            }
        }
    }
}

void TrainNetwork::DebugDispatchTrain(CTrain *t) {
    t->DispatchTrain();
    bool line_bool = (t->GetLine()->GetName() == kRedlineName) ? kRedBool : kGreenBool;
    emit TrainDispatched(t->GetNum(), line_bool);
}

void TrainNetwork::AddLineSales(int sales, bool line) {
    if (line == kRedBool) {
        TrackLine *l = GetTrackLine(kRedlineName);
        l->UpdateSales(sales);
    } else {
        TrackLine *l = GetTrackLine(kGreenlineName);
        l->UpdateSales(sales);
    }
}

void TrainNetwork::CalculateThroughputs(QTime sim_time) {
    for (TrackLine *l : lines_) {
        l->CalculateThroughputs(sim_time);
    }
}
