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

    int sug_auth_;
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
    int GetAuth() const;
    int GetSpeed() const;
    int GetSpeedLimit() const;
    int GetLength() const;
    std::set<int> GetConnections() const;

    void SetClosed(bool closed);
    void SetOccupied(bool occupied);
    void AddConnection(int conn_block_num);

signals:

};

#endif // BLOCK_H
