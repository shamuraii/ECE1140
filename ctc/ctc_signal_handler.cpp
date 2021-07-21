#include "ctc_signal_handler.h"

void CtcSH::TimedEvents() {
    emit UpdateOutputs();
}


void CtcSH::GetSwitchPosition(int pointing_to, bool line) {
    emit NewSwitchPos(pointing_to, line);
}

void CtcSH::GetTrainLocation(std::vector<bool> occupancy, bool line) {
    emit NewOccupancies(occupancy, line);
}

void CtcSH::OutputsUpdated(std::vector<bool> out_auth, std::vector<int> out_speed, bool line) {
    emit ShareSugAuthority(out_auth, line);
    emit ShareSugSpeed(out_speed, line);
}

void CtcSH::BlockMaint(int block_num, bool maint_mode, bool line) {
    emit SetBlockMaintenance(block_num, maint_mode, line);
}

void CtcSH::SwitchMaint(int switch_num, bool maint_mode, bool line) {
    emit SetSwitchMaintenance(switch_num, maint_mode, line);
}

void CtcSH::SwitchPos(int pointing_to, bool line) {
    emit SetSwitchPosition(pointing_to, line);
}
