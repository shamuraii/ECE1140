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
    void SetTrainPresence(int block_num, bool presence, string l);

signals:
    //to CTC
    void ShareSwitchPosition(int pointing_to, bool line);
    void ShareTrainPresence(std::vector<bool> occupied, bool line);
    //to Track Model
        //commanded_speed
        //authority
        //light state?
};

#endif // WSSH_H
