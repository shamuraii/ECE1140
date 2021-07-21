#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <vector>
#include <set>

class Block : public QObject
{
    Q_OBJECT
private:
    int num_;
    bool occupied_;
    bool closed_;

    bool sug_auth_;
    int sug_speed_;

    int speed_limit_;
    int length_;
    std::set<int> connections_;

public:
    static const int kInfiniteWeight;
    static const int kYardNum;

    explicit Block(int num);

    bool IsYard() const;
    bool IsClosed() const;
    bool IsOccupied() const;

    int GetNum() const;
    int GetWeight() const;
    bool GetAuth() const;
    int GetSpeed() const;
    int GetSpeedLimit() const;
    int GetLength() const;
    std::set<int> GetConnections() const;

    void SetClosed(bool closed, bool line);
    void SetOccupied(bool occupied);
    void SetAuth(bool auth);
    void SetSpeed(int speed);
    void AddConnection(int conn_block_num);

signals:
    void MaintChanged(int block_num, bool maint_mode, bool line);

};

#endif // BLOCK_H
