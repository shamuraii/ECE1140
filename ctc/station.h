#ifndef STATION_H
#define STATION_H

#include <QObject>

namespace ctc {

class Station : public QObject
{
    Q_OBJECT
private:
    int block_num_;
    QString name_;
    int sales_;
public:
    explicit Station(int block_num, QString name);

    int GetBlockNum() const;
    QString GetName() const;
    int GetSales() const;
public slots:
    void SetThroughput(int persons);
signals:
    void ThroughputUpdated();
};
}

#endif // STATION_H
