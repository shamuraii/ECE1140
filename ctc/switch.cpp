#include "switch.h"
#include "ctc_signal_handler.h"

Switch::Switch(int lower, int upper)
    : QObject(nullptr),
      lower_(lower),
      upper_(upper)
{
    pointing_to_ = lower_;
    maint_mode_ = false;

    connect(this, &Switch::StateChanged, &CtcSH::Get(), &CtcSH::SwitchPos);
    connect(this, &Switch::MaintChanged, &CtcSH::Get(), &CtcSH::SwitchMaint);
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

bool Switch::InMaintenance() const {
    return maint_mode_;
}

void Switch::SetMaintenance(bool mode, bool line) {
    if (maint_mode_ != mode) {
        maint_mode_ = mode;
        emit MaintChanged(lower_, mode, line);
    }
}

void Switch::UpdateState(int new_target, bool line) {
    if (pointing_to_ != new_target) {
        pointing_to_ = new_target;
        if (maint_mode_) {
            emit StateChanged(pointing_to_, line);
        }
    }
}
