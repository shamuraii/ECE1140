#include "track_control.h"
#include "wssh.h"

vector<track_control::Block> track_control::green_block_vector;
vector<track_control::Block> track_control::red_block_vector;

track_control::track_control()
{
    int red_blocks[13] = {1,8,14,20,25,31,37,43,47,52,57,63,69};
    int green_blocks[19] = {1,7,14,20,27,34,42,50,59,66,74,82,90,99,107,116,124,133,142};
    int red_switches[7][4] = {{9, 0, 10, 10}, {16, 15, 1, 1}, {27, 28, 76, 76}, {32, 33, 72, 72}, {38, 39, 71, 71}, {43, 44, 67, 67}, {52, 53, 66, 66}};
    int green_switches[6][4] = {{13, 12, 1, 1}, {28, 30, 150, 150}, {57, 0, 58, 58}, {63, 0, 62, 62}, {77, 76, 101, 101}, {85, 86, 100, 100}};

    int index = 0;

    //green line
    for(int i=1; i<150; i++) {
        Block b1;
        //setting id
        b1.id = i;
        //setting line
        b1.line = "green";
        //setting wayside section
        if(b1.id<green_blocks[index+1]){
            b1.section = 'A'+index;
        } else {
            b1.section = 'A'+index+1;
            index++;
        }
        //setting authority
        b1.authority = 0;
        //setting speed
        b1.speed = 0;
        //setting maintenance mode
        b1.maintenance_mode = 0;
        //setting occupancy
        b1.occupancy = 0;
        //setting fail
        b1.fail = 0;
        //setting switch
        b1.sw.presence = 0;
        b1.sw.base = 0;
        b1.sw.upper = 0;
        b1.sw.lower = 0;
        b1.sw.connected_to = 0;
        for (int j=0; j<6; j++) {
            if(b1.id == j) {
                b1.sw.presence = 1;
                b1.sw.base = j;
                b1.sw.upper = green_switches[j][1];
                b1.sw.lower = green_switches[j][2];
                b1.sw.connected_to = green_switches[j][2];
            }
        }
        //setting crossing
        b1.rx.presence = 0;
        b1.rx.lights_state = 0;
        b1.rx.bar_state = 0;
        if(b1.id == 19) {
            b1.rx.presence = 1;
            b1.rx.lights_state= 0;
            b1.rx.bar_state= 0;
        }
        green_block_vector.push_back(b1);
    }

    //red line
    for(int i=1; i<76; i++) {
        Block b1;
        //setting id
        b1.id = i;
        //setting line
        b1.line = "red";
        //setting wayside section
        if(b1.id<red_blocks[index+1]){
            b1.section = 'A'+index;
        } else {
            b1.section = 'A'+index+1;
            index++;
        }
        //setting authority
        b1.authority = 0;
        //setting speed
        b1.speed = 0;
        //setting maintenance mode
        b1.maintenance_mode = 0;
        //setting occupancy
        b1.occupancy = 0;
        //setting fail
        b1.fail = 0;
        //setting switch
        b1.sw.presence = 0;
        b1.sw.base = 0;
        b1.sw.upper = 0;
        b1.sw.lower = 0;
        b1.sw.connected_to = 0;
        for (int j=0; j<7; j++) {
            if(b1.id == j) {
                b1.sw.presence = 1;
                b1.sw.base = j;
                b1.sw.upper = red_switches[j][1];
                b1.sw.lower = red_switches[j][2];
                b1.sw.connected_to = red_switches[j][2];
            }
        }
        //setting crossing
        b1.rx.presence = 0;
        b1.rx.lights_state = 0;
        b1.rx.bar_state = 0;
        if(b1.id == 47) {
            b1.rx.presence = 1;
            b1.rx.lights_state= 0;
            b1.rx.bar_state= 0;
        }
        red_block_vector.push_back(b1);
    }
}

track_control::Block track_control::getBlock(int block_num, string l) {
    if(l == "red") {
        return red_block_vector[block_num-1];
    } else {
        return green_block_vector[block_num-1];
    }
}

void track_control::setBlockAuthority(int block_num, int auth, string l)
{
    if(l == "red") {
        red_block_vector[block_num-1].authority = auth;
    } else if(l == "green") {
        green_block_vector[block_num-1].authority = auth;
    }
}

bool track_control::getBlockMaintenanceMode(int block_num, string l) {
    if(l == "red")
        return red_block_vector[block_num].maintenance_mode;
    else
        return green_block_vector[block_num].maintenance_mode;
}

void track_control::setBlockOccupancy(int block_num, bool occ, string l) {
    if(l == "red") {
        red_block_vector[block_num-1].occupancy = occ;
    } else if(l == "green") {
        green_block_vector[block_num-1].occupancy = occ;
    }
}

void track_control::setBlockFailure(int block_num, int fail_code, string l) {
    if(l == "red") {
        red_block_vector[block_num-1].fail = fail_code;
    } else if(l == "green") {
        green_block_vector[block_num-1].fail = fail_code;
    }
}

void track_control::setBlockSpeed(int block_num, int sp, string l) {
    if(l == "red") {
        red_block_vector[block_num-1].speed = sp;
    } else if(l == "green") {
        green_block_vector[block_num-1].speed = sp;
    }
}

void track_control::setBlockMaintenanceMode(int block_num, bool maint, string l) {
    if(l == "red") {
        red_block_vector[block_num-1].maintenance_mode = maint;
    } else if(l == "green") {
        green_block_vector[block_num-1].maintenance_mode = maint;
    }
}

bool track_control::getSwitchPresence(int block_num, string l) {
    if(l == "red") {
        return red_block_vector[block_num-1].sw.presence;
    } else {
        return green_block_vector[block_num-1].sw.presence;
    }
}

int track_control::getSwitchPositon(int block_num, string l) {
    if(l == "red") {
        return red_block_vector[block_num-1].sw.connected_to;
    } else {
        return green_block_vector[block_num-1].sw.connected_to;
    }
}

void track_control::setSwitches() {
    //green line
    for(int i=0; i>150; i++) {
        if(green_block_vector[i].authority == 1) {
            if(green_block_vector[i].sw.presence == 1) {
                int upper_block = green_block_vector[i].sw.upper;
                int lower_block = green_block_vector[i].sw.lower;
                if(green_block_vector[upper_block].authority == 1) {
                    green_block_vector[i].sw.connected_to = upper_block;
                    emit wssh::Get().ShareSwitchPosition(upper_block, true);
                } else {
                    green_block_vector[i].sw.connected_to = lower_block;
                    emit wssh::Get().ShareSwitchPosition(lower_block, true);
                }
            }
        }
    }

    //red line
    for(int i=0; i>76; i++) {
        if(red_block_vector[i].authority == 1) {
            if(red_block_vector[i].sw.presence == 1) {
                int upper_block = red_block_vector[i].sw.upper;
                int lower_block = red_block_vector[i].sw.lower;
                if(red_block_vector[upper_block].authority == 1) {
                    red_block_vector[i].sw.connected_to = upper_block;
                    emit wssh::Get().ShareSwitchPosition(upper_block, false);
                } else {
                    red_block_vector[i].sw.connected_to = lower_block;
                    emit wssh::Get().ShareSwitchPosition(lower_block, false);
                }
            }
        }
    }
}

vector<track_control::Block> track_control::getBlockVector(string l) {
    if(l == "red")
        return red_block_vector;
    else
        return green_block_vector;
}

void track_control::setCrossing(bool state, string l) {
    if(l == "red") {
        red_block_vector[47].rx.bar_state = state;
        red_block_vector[47].rx.lights_state = state;
    } else {
        green_block_vector[19].rx.bar_state = state;
        green_block_vector[19].rx.lights_state = state;
    }
}
