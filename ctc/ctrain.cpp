#include "ctrain.h"
#include "trackline.h"
#include "station.h"
#include "ctc_constants.h"

namespace ctc {

CTrain::CTrain(Station *destination, QTime departure_time, TrackLine *line)
    : QObject(nullptr),
      destination_(destination),
      departure_time_(departure_time),
      line_(line)
{
    stops_ = line_->GetStopListFromDestination(destination_);
    stopped_ = false;

    std::vector<int> stop_blocks;
    stop_blocks.push_back(Block::kYardNum);
    for (Station *s : stops_) {
        stop_blocks.push_back(s->GetBlockNum());
    }
    stop_blocks.push_back(Block::kYardNum);
    route_ = line_->GetFullRoute(stop_blocks);

    location_ = line->GetYardBlock();
    CalculateEstimatedArrival();
    route_index_ = 0;
    num_ = 0;
}

void CTrain::CalculateEstimatedArrival() {
    estimated_arrival_ = departure_time_.addSecs(60*60);// Add 1 hour... todo
}

int CTrain::GetNum() const {
    return num_;
}

std::vector<Station*> CTrain::GetStops() const {
    return stops_;
}

std::vector<Block*> CTrain::GetRoute() const {
    return route_;
}

TrackLine *CTrain::GetLine() const {
    return line_;
}

Station *CTrain::GetDestination() const {
    return destination_;
}

Block *CTrain::GetLocation() const {
    return location_;
}

Block *CTrain::GetNextBlock() const {
    return route_[route_index_ + 1];
}

QTime CTrain::GetDepartTime() const {
    return departure_time_;
}

QTime CTrain::GetArrivalTime() const {
    return estimated_arrival_;
}

QString CTrain::GetRouteString() const {
    QString out = "";
    for (Block *b : route_) {
        out.append(QString::number(b->GetNum()));
        out.append(" - ");
    }
    out.chop(3);
    return out;
}

QString CTrain::GetStopsString() const {
    QString out = "";
    for (Station *s : stops_) {
        out.append(s->GetName());
        out.append(" -> ");
    }
    out.chop(4);
    return out;
}

int CTrain::GetSugSpeed(bool mph) const {
    int sug_speed = location_->GetSpeed();
    if (mph)
        return sug_speed * kMPHperKMH;
    else
        return sug_speed;
}

int CTrain::GetSugAuth() const {
    return location_->GetAuth();
}

void CTrain::UpdateOutputs() {
    if (stopped_) {
        GetLocation()->SetAuth(1);
    } else {
        for (Station *s : line_->GetStations()) {
            if (s->GetBlockNum() == GetLocation()->GetNum()) {
                GetLocation()->SetAuth(0);
            }
        }
    }
    GetLocation()->SetSpeed(GetLocation()->GetSpeedLimit());
    GetNextBlock()->SetSpeed(GetNextBlock()->GetSpeedLimit());

    GetNextBlock()->SetAuth(1);
    for (Station *s : line_->GetStations()) {
        if (s->GetBlockNum() == GetNextBlock()->GetNum()) {
            GetNextBlock()->SetAuth(0);
        }
    }
}

void CTrain::SetLocation(Block *new_location) {
    location_ = new_location;
    stopped_ = false;
}

void CTrain::SetNum(int num) {
    num_ = num;
}

void CTrain::TrainStopped() {
    stopped_ = true;
}

void CTrain::RecalculateRoute(int num) {
    if (num == -1) {
        // Regular route recalculation
    } else {
        // Forced to route to a specific block
    }
}

void CTrain::DebugAdvanceTrain() {
    if (route_index_ == static_cast<int>(route_.size()) - 1) {
        return;
    }
    Block *old = location_;
    Block *next = route_[++route_index_];
    if (next->GetNum() == location_->GetNum()) {
        return;
    }

    location_ = next;

    emit UpdatedLocation(old, location_);    
}

}
