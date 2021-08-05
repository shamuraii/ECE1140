#ifndef TRACK_CONTROL_H
#define TRACK_CONTROL_H
#include <iostream>
#include <vector>
using namespace std;

//#include "wayside.h"
//#include "block.h"
//#include "switch.h"
//#include "crossing.h"
#include "plc.h"


class track_control
{
public:
    track_control();

    struct Switch {
        bool presence;
        int base;
        int upper;
        int lower;
        int connected_to;
    };
    struct Crossing {
        bool presence;
        bool lights_state;
        bool bar_state;
    };
    struct Block {
      int id;
      char section;
      string line;
      bool authority;
      bool occupancy;
      int speed;
      bool fail;
      bool maintenance_mode;
      Switch sw;
      Crossing rx;
    };

    static void initialize();
    static string getPLCFile();
    static void setPLCFile(string);
    static Block getBlock(int block_num, string l);
    static void setBlockAuthority(int block_num, int auth, string l);
    static void checkAuthority(int block_num, bool l);
    static void setBlockOccupancy(int block_num, bool occ, string l);
    static void setBlockFailure(int block_num, int fail_code, string l);
    static void setBlockSpeed(int block_num, int sp, string l);
    static void checkSpeed(int block_num, bool l);
    static void setBlockMaintenanceMode(int block_num, bool maint, string l);
    static bool getBlockMaintenanceMode(int, string);
    static bool getSwitchPresence(int block_num, string l);
    static int getSwitchPositon(int block_num, string l);
    static void setSwitches();
    static void setSwitchPositionManual(int base, int connection, string l);
    static vector<Block> getBlockVector(string);
    static void setCrossing(bool state, string l);
    static void setBlockFailure(int block_num, bool f);
    static int getBlockID(int);
    static bool getBlockAuthority(int);
    static int getBlockSpeed(int);
    static bool getBlockOccupancy(int, bool);

private:
    static vector<Block> green_block_vector;
    static vector<Block> red_block_vector;
    static vector<bool> red_line_occupancy;
    static vector<bool> green_line_occupancy;
    static string plc_file;
};

#endif // TRACK_CONTROL_H
