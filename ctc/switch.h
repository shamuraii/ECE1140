#ifndef SWITCH_H
#define SWITCH_H

#include <QObject>

namespace ctc {

class Switch : public QObject
{
    Q_OBJECT
private:
    int lower_;
    int upper_;
    int pointing_to_;

    bool maint_mode_;
public:
    explicit Switch(int lower, int upper);


    bool HasBlock(int block_num) const;
    int LowerBlock() const;
    int UpperBlock() const;
    int PointingTo() const;
    bool InMaintenance() const;

public slots:
    void UpdateState(int new_target, bool line);
    void SetMaintenance(bool mode, bool line);

signals:
    void StateChanged(int pointing_to, bool line);
    void MaintChanged(int switch_num, bool mode, bool line);
};
}

#endif // SWITCH_H
