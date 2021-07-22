#ifndef WSSH_H
#define WSSH_H

#include <QObject>
#include "track_control.h"

class wssh : public QObject
{
    Q_OBJECT
public:
    wssh(wssh const&) = delete;
    void operator=(wssh const&) = delete;
    static wssh& Get() {
        static wssh instance;
        return instance;
    }

private:
    explicit wssh() {}

public slots:
    //from CTC
    void SetSugAuthority(std::vector<bool> authority, bool l);
    void SetSugSpeed(std::vector<int> suggested_speed, bool l);
    void SetBlockMaintenance(int block_num, bool maintenance_mode);
    //from Track Model
    void SetTrainPresence(int curr_block_num, int prev_block_num);
    void SetBrokenRail(int block_num, bool failure);

signals:
    //to CTC
    void ShareSwitchPosition(int pointing_to, bool line);
    void ShareTrainPresence(std::vector<bool> occupied, bool line);
    //to Track Model
    void ShareCommSpeed(std::vector<int> commanded_speed);
    void ShareAuthority(std::vector<bool> authority);
    void ShareSwitchPosTM(int sw_base, int pointing_to, bool line);
        //light state?
};

#endif // WSSH_H
