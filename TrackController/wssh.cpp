#include "wssh.h"
#include <iostream>
#include <vector>



//slots from CTC
void wssh::SetSugAuthority(std::vector<bool> sug_authority, bool l) {
    emit Get().ShareAuthority(sug_authority);

    int size = sug_authority.size();
    for(int i=0; i<size; i++) {
        if(l == 0) {
            //red line
            for(int j=1; j<76; j++) {
                track_control::setBlockAuthority(i, sug_authority[j], "red");
                //set PLC file
                track_control::setPLCFile("R-9");
                for (int x=0; x<7; x++) {
                    if(sug_authority[j] == red_switch_blocks[x]) {
                        track_control::setPLCFile("R-"+to_string(red_switch_blocks[x]));
                    }
                }
            }
        } else {
            //green line
            for(int k=1; k<150; k++) {
                track_control::setBlockAuthority(i, sug_authority[k], "green");
                //set PLC file
                track_control::setPLCFile("G-0");
                for (int x=0; x<5; x++) {
                    if(sug_authority[k] == green_switch_blocks[x]) {
                        track_control::setPLCFile("G-"+to_string(green_switch_blocks[x]));
                    }
                }
            }
        }
    }
}

void wssh::SetSugSpeed(std::vector<int> suggested_speed, bool l) {
    emit Get().ShareCommSpeed(suggested_speed);
    int size = suggested_speed.size();
    for(int i=0; i<size; i++) {
        if(l == 0) {
            //red line
            for(int j=1; j<76; j++) {
                track_control::setBlockSpeed(i, suggested_speed[j], "red");
            }
        } else {
            //green line
            for(int k=1; k<150; k++) {
                track_control::setBlockSpeed(i, suggested_speed[k], "green");
            }
        }
    }
}

void wssh::SetBlockMaintenance(int block_num, bool maintenance_mode) {
    //assume red line
    track_control::setBlockMaintenanceMode(block_num, maintenance_mode, "red");
}

void wssh::SetTrainPresence(int curr_block_num, int prev_block_num) {
    track_control::setBlockOccupancy(curr_block_num, true, "red");
    track_control::setBlockOccupancy(prev_block_num, false, "red");
    emit Get().UpdateGUI();
    if(curr_block_num == 46)
        track_control::setCrossing(true, "red");
    if(curr_block_num == 48)
        track_control::setCrossing(false, "red");
    track_control::checkAuthority(curr_block_num, false);
    track_control::checkSpeed(curr_block_num, false);

}

void wssh::SetBrokenRail(int block_num, bool failure) {
    track_control::setBlockFailure(block_num, failure);
}
