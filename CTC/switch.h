#ifndef SWITCH_H
#define SWITCH_H

#include <QObject>

class Switch : public QObject
{
    Q_OBJECT
private:
    int lower_;
    int upper_;
    int pointing_to_;
public:
    explicit Switch(int lower, int upper);


    bool HasBlock(int block_num) const;
    int LowerBlock() const;
    int UpperBlock() const;
    int PointingTo() const;

public slots:
    void UpdateState(int new_target);

signals:

};

#endif // SWITCH_H
