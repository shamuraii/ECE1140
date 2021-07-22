#include "train.h"
#include "trackline.h"
#include "station.h"
#include "ctc_constants.h"

using namespace ctc;

Train::Train(Station *destination, QTime departure_time, TrackLine *line)
    : QObject(nullptr),
      destination_(destination),
      departure_time_(departure_time),
      line_(line)
{
    stops_ = line_->GetStopListFromDestination(destination_);

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

void Train::CalculateEstimatedArrival() {
    estimated_arrival_ = departure_time_.addSecs(60*60);// Add 1 hour... todo
}

int Train::GetNum() const {
    return num_;
}

std::vector<Station*> Train::GetStops() const {
    return stops_;
}

std::vector<Block*> Train::GetRoute() const {
    return route_;
}

TrackLine *Train::GetLine() const {
    return line_;
}

Station *Train::GetDestination() const {
    return destination_;
}

Block *Train::GetLocation() const {
    return location_;
}

Block *Train::GetNextBlock() const {
    return route_[route_index_ + 1];
}

QTime Train::GetDepartTime() const {
    return departure_time_;
}

QTime Train::GetArrivalTime() const {
    return estimated_arrival_;
}

QString Train::GetRouteString() const {
    QString out = "";
    for (Block *b : route_) {
        out.append(QString::number(b->GetNum()));
        out.append(" - ");
    }
    out.chop(3);
    return out;
}

QString Train::GetStopsString() const {
    QString out = "";
    for (Station *s : stops_) {
        out.append(s->GetName());
        out.append(" -> ");
    }
    out.chop(4);
    return out;
}

int Train::GetSugSpeed(bool mph) const {
    int sug_speed = location_->GetSpeed();
    if (mph)
        return sug_speed * kMPHperKMH;
    else
        return sug_speed;
}

int Train::GetSugAuth() const {
    return location_->GetAuth();
}

void Train::UpdateOutputs() {
    GetLocation()->SetAuth(1);
    GetNextBlock()->SetAuth(1);

    GetLocation()->SetSpeed(GetLocation()->GetSpeedLimit());
    GetNextBlock()->SetSpeed(GetNextBlock()->GetSpeedLimit());
}

void Train::SetLocation(Block *new_location) {
    location_ = new_location;
}

void Train::SetNum(int num) {
    num_ = num;
}

void Train::RecalculateRoute(int num) {
    if (num == -1) {
        // Regular route recalculation
    } else {
        // Forced to route to a specific block
    }
}

void Train::DebugAdvanceTrain() {
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
