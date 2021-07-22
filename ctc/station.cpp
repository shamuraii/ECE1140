#include "station.h"

using namespace ctc;

Station::Station(int block_num, QString name)
    : QObject(nullptr),
      block_num_(block_num),
      name_(name)
{
    sales_ = 0;
}

int Station::GetBlockNum() const {
    return block_num_;
}

QString Station::GetName() const {
    return name_;
}

int Station::GetSales() const {
    return sales_;
}

void Station::SetThroughput(int persons) {
    sales_ = persons;
    emit ThroughputUpdated();
}
