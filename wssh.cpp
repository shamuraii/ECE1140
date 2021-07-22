#include "wssh.h"
#include <iostream>
#include <vector>


//slots from CTC
void wssh::SetSugAuthority(std::vector<bool> sug_authority, bool l) {
    int size = sug_authority.size();
    for(int i=0; i<size; i++) {
        if(l == 0) {
            //red line
            for(int j=1; j<76; j++) {
                track_control::setBlockAuthority(i, sug_authority[j], "red");
            }
        } else {
            //green line
            for(int k=1; k<150; k++) {
                track_control::setBlockAuthority(i, sug_authority[k], "green");
            }
        }
    }
}

void wssh::SetSugSpeed(std::vector<int> suggested_speed, bool l) {
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

void wssh::SetTrainPresence(int block_num, bool presence, string l) {
    track_control::setBlockOccupancy(block_num, presence, l);
    if((l == "red" && block_num == 46)||(l == "green" && block_num == 18))
        track_control::setCrossing(true, l);
    if((l == "red" && block_num == 48)|(l == "green" && block_num == 20))
        track_control::setCrossing(false, l);
}
