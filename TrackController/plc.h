#ifndef PLC_H
#define PLC_H
#include <string>
#include <iostream>
using namespace std;

class PLC
{
public:
    PLC();
    bool runPLC(); //returns whether it is running successfully
    bool verifyPLC(); //returns whether the PLC is valid or not

private:
    string plc_file;
    string filename;
    bool valid;
};

#endif // PLC_H
