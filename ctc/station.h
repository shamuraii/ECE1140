#ifndef STATION_H
#define STATION_H

#include <QObject>

namespace ctc {

class Station : public QObject
{
    Q_OBJECT
private:
    int block_num_;
    int block_num2_;
    QString name_;
    int sales_;
public:
    explicit Station(int block_num, QString name);

    int GetBlockNum() const;
    int GetBlockNum2() const;
    QString GetName() const;
    int GetSales() const;

    void SetBlockNum2(int num);
public slots:
    void SetThroughput(int persons);
signals:
    void ThroughputUpdated();
};
}

#endif // STATION_H
