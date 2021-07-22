#include <QDebug>

#include "ctc_signal_handler.h"

void CtcSH::TimedEvents() {
    qDebug() << "UpdateOutputs";
    emit UpdateOutputs();
}

void CtcSH::GetTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line) {
    qDebug() << "NewTrackInfo " << speed_limits.size() << " " << lengths.size() << " " << line;
    emit NewTrackInfo(speed_limits, lengths, line);
}

void CtcSH::GetSwitchPosition(int pointing_to, bool line) {
    qDebug() << "NewSwitchPos " << pointing_to << " " << line;
    emit NewSwitchPos(pointing_to, line);
}

void CtcSH::GetTrainLocation(std::vector<bool> occupancy, bool line) {
    qDebug() << "NewOccupancies " << occupancy.size() << " " << line;
    emit NewOccupancies(occupancy, line);
}

void CtcSH::OutputsUpdated(std::vector<bool> out_auth, std::vector<int> out_speed, bool line) {
    qDebug() << "ShareSugAuth " << out_auth.size() << " " << line;
    emit ShareSugAuthority(out_auth, line);
    qDebug() << "ShareSugSpeed " << out_speed.size() << " " << line;
    emit ShareSugSpeed(out_speed, line);
}

void CtcSH::BlockMaint(int block_num, bool maint_mode, bool line) {
    qDebug() << "ShareBlockMaintenance " << block_num << " " << maint_mode << " " << line;
    emit ShareBlockMaintenance(block_num, maint_mode, line);
}

void CtcSH::SwitchMaint(int switch_num, bool maint_mode, bool line) {
    qDebug() << "ShareSwitchMaintenance " << switch_num << " " << maint_mode << " " << line;
    emit ShareSwitchMaintenance(switch_num, maint_mode, line);
}

void CtcSH::SwitchPos(int pointing_to, bool line) {
    qDebug() << "ShareSwitchPosition " << pointing_to << " " << line;
    emit ShareSwitchPosition(pointing_to, line);
}
