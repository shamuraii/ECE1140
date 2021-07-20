#include "switch.h"

Switch::Switch(int lower, int upper)
    : QObject(nullptr),
      lower_(lower),
      upper_(upper)
{
    pointing_to_ = lower_;
}

bool Switch::HasBlock(int block_num) const {
    return (lower_ == block_num || upper_ == block_num);
}

int Switch::PointingTo() const {
    return pointing_to_;
}

int Switch::LowerBlock() const {
    return lower_;
}

int Switch::UpperBlock() const {
    return upper_;
}

void Switch::UpdateState(int new_target) {
    pointing_to_ = new_target;
}
