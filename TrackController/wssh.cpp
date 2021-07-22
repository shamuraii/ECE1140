#include "wssh.h"
#include <iostream>
#include <vector>
#include <QDebug>


//slots from CTC
void wssh::SetSugAuthority(std::vector<bool> sug_authority, bool l) {
    qDebug() << "WC entered SetSugAuth";

    emit ShareAuthority(sug_authority);
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
    qDebug() << "WC entered SetSugSpeed";

    emit ShareCommSpeed(suggested_speed);
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

    //TODO emit ShareTrainPresence to CTC
    if(curr_block_num == 46)
        track_control::setCrossing(true, "red");
    if(curr_block_num == 48)
        track_control::setCrossing(false, "red");

}

void wssh::SetBrokenRail(int block_num, bool failure) {
    track_control::setBlockFailure(block_num, failure);
}

void wssh::TimerTicked() {
    //TODO something has to happen here idk :Os
}
