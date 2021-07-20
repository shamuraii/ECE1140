#include <set>

#include "block.h"

const int Block::kInfiniteWeight = -1;
const int Block::kYardNum = 0;

Block::Block(int num) : QObject(nullptr), num_(num)
{
    occupied_ = false;
    closed_ = false;
    speed_limit_ = 1;
    length_ = 1;
    sug_auth_ = 0;
    sug_speed_ = 0;
}

bool Block::IsYard() const {
    return num_ == kYardNum;
}

bool Block::IsClosed() const {
    return closed_;
}

bool Block::IsOccupied() const {
    return occupied_;
}

int Block::GetNum() const {
    return num_;
}

int Block::GetWeight() const {
    if (IsYard())
        return 1;
    else if (closed_)
        return kInfiniteWeight;
    else
        return 1;
}

int Block::GetAuth() const {
    return sug_auth_;
}

int Block::GetSpeed() const {
    return sug_speed_;
}

int Block::GetSpeedLimit() const {
    return speed_limit_;
}

int Block::GetLength() const {
    return length_;
}

std::set<int> Block::GetConnections() const {
    return connections_;
}

void Block::SetClosed(bool closed) {
    closed_ = closed;
}

void Block::SetOccupied(bool occupied) {
    occupied_ = occupied;
}

void Block::AddConnection(int conn_block_num) {
    connections_.insert(conn_block_num);
}
