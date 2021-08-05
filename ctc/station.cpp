#include "station.h"

using namespace ctc;

Station::Station(int block_num, QString name)
    : QObject(nullptr),
      block_num_(block_num),
      name_(name)
{
    sales_ = 0;
    block_num2_  = -1;
}

int Station::GetBlockNum() const {
    return block_num_;
}

int Station::GetBlockNum2() const {
    return block_num2_;
}

QString Station::GetName() const {
    return name_;
}

int Station::GetSales() const {
    return sales_;
}

void Station::SetBlockNum2(int num) {
    block_num2_ = num;
}

void Station::SetThroughput(int persons) {
    sales_ = persons;
    emit ThroughputUpdated();
}
