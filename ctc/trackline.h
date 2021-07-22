#ifndef TRACKLINE_H
#define TRACKLINE_H

#include <QObject>
#include <vector>

#include "block.h"
#include "station.h"
#include "switch.h"

namespace ctc {

struct BlockPair {
    int priority;
    int blockNum;
};

struct BlockComp {
    constexpr bool operator()(BlockPair const& a, BlockPair const& b) const noexcept {
        return a.priority < b.priority;
    }
};

class TrackLine : public QObject
{
    Q_OBJECT
private:
    std::vector<Block*> blocks_;
    std::vector<Station*> stations_;
    std::vector<Switch*> switches_;
    QString name_;

    std::vector<Block*> ReconstructPath(int start_num, int end_num, std::unordered_map<int, int> came_from) const;

public:
    explicit TrackLine(QString block_file,
                       QString station_file,
                       QString switch_file,
                       QString name);

    QString GetName() const;
    Block *GetYardBlock() const;
    Block *GetBlock(int block_num) const;
    Station *GetStation(int block_num) const;
    Station *GetStation(QString station_name) const;
    Switch *GetSwitch(int block_num) const;
    int GetBlockCount() const;
    std::vector<Block*> GetBlocks() const;
    std::vector<Station*> GetStations() const;
    std::vector<Switch*> GetSwitches() const;

    std::vector<Station*> GetStopListFromDestination(Station *destination) const;

    std::vector<Block*> GetFullRoute(std::vector<int> stop_blocks) const;
    std::vector<Block*> GetRoute(int start_num, int end_num) const;

public slots:
    void UpdateThroughput();

signals:
    void ThroughputUpdated(int persons);

};
}

#endif // TRACKLINE_H
