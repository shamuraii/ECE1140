#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

#include "trackline.h"
#include "block.h"
#include "station.h"
#include "switch.h"

using namespace ctc;

TrackLine::TrackLine(QString block_file,
                     QString station_file,
                     QString switch_file,
                     QString name) : QObject(nullptr), name_(name)
{
    std::ifstream fin;
    std::string line;
    std::string val;
    std::stringstream ss;

    // Open the Block File
    fin.open(block_file.toStdString());
    while (std::getline(fin, line)) {
        ss = std::stringstream(line);
        std::getline(ss, val, ',');
        // Make new block
        Block *b = new Block(stoi(val));
        while (std::getline(ss, val, ',')) {
            if (!val.empty())
                b->AddConnection(std::stoi(val));
        }
        blocks_.push_back(b);
    }
    fin.close();
    fin.clear();

    // Open the Station File
    fin.open(station_file.toStdString());
    while (std::getline(fin, line)) {
        ss = std::stringstream(line);
        std::vector<std::string> results;
        while (std::getline(ss, val, ',')) {
            results.push_back(val);
        }
        int block_num = std::stoi(results[0]);
        QString s_name = QString::fromStdString(results[1]);

        // Check if station already added to another block
        Station *s = GetStation(s_name);
        if (s == nullptr) {
            // Make new station
            s = new Station(block_num, s_name);
            connect(s, &Station::ThroughputUpdated, this, &TrackLine::UpdateThroughput);
            stations_.push_back(s);
        } else {
            // Add block2 to station
            s->SetBlockNum2(block_num);
        }
        // Add to the station stop order
        stop_order_.push_back(s);
    }
    fin.close();
    fin.clear();

    // Open the Switch File
    fin.open(switch_file.toStdString());
    while (std::getline(fin, line)) {
        ss = std::stringstream(line);
        std::vector<std::string> results;
        while (std::getline(ss, val, ',')) {
            results.push_back(val);
        }
        // Make new switch
        Switch *sw = new Switch(std::stoi(results[0]),
                                std::stoi(results[1]),
                                std::stoi(results[2]));
        switches_.push_back(sw);
    }
    fin.close();
}

Block *TrackLine::GetYardBlock() const {
    return blocks_[Block::kYardNum];
}

QString TrackLine::GetName() const {
    return name_;
}

Block *TrackLine::GetBlock(int block_num) const {
    if (static_cast<int>(blocks_.size()) < block_num || block_num < 0)
        return nullptr;
    else
        return blocks_[block_num];
}

Station *TrackLine::GetStation(int block_num) const {
    for (Station *s : stations_)
        if (s->GetBlockNum() == block_num || s->GetBlockNum2() == block_num)
            return s;
    return nullptr;
}

Station *TrackLine::GetStation(QString station_name) const {
    for (Station *s : stations_)
        if (s->GetName() == station_name)
            return s;
    return nullptr;
}

Switch *TrackLine::GetSwitch(int block_num) const {
    for (Switch *sw : switches_)
        if (sw->GetBlock() == block_num)
            return sw;
    return nullptr;
}

int TrackLine::GetBlockCount() const {
    return blocks_.size();
}

std::vector<Block*> TrackLine::GetBlocks() const {
    return blocks_;
}

std::vector<Station*> TrackLine::GetStations() const {
    return stations_;
}

std::vector<Switch*> TrackLine::GetSwitches() const {
    return switches_;
}

std::vector<Station*> TrackLine::GetStopListFromDestination(Station *destination) const {
    std::vector<Station*> stops;

    for (auto* s : stop_order_) {
        stops.push_back(s);
        if (s == destination)
            break;
    }

    return stops;
}

std::vector<Block*> TrackLine::GetFullRoute(std::vector<int> stop_blocks) const {
    std::vector<Block*> path;
    if (stop_blocks.empty()) {
        return path;
    }

    bool solvable = true;
    int prev_stop = stop_blocks.front();
    for (int next_stop : stop_blocks) {
        std::vector<Block*> next_path = GetRoute(prev_stop, next_stop);
        if (next_path.empty()) {
            solvable = false;
            break;
        } else {
            path.insert(path.end(), next_path.begin(), next_path.end());
            path.pop_back();
            prev_stop = next_stop;
        }
    }
    path.push_back(GetBlock(stop_blocks.back()));
    if (!solvable) path.clear();
    return path;
}

std::vector<Block*> TrackLine::GetRoute(int start_num, int end_num) const {
    std::unordered_map<int, int> came_from; //<block, parent>
    std::unordered_map<int, int> cost_so_far; //<block, cost>
    std::priority_queue<BlockPair, std::vector<BlockPair>, BlockComp> frontier;

    frontier.push({ 0, start_num });
    came_from[start_num] = start_num;
    cost_so_far[start_num] = 0;
    bool solved = false;

    while (!frontier.empty()) {
        BlockPair current = frontier.top();
        frontier.pop();

        //Check if meaningless entry
        if (cost_so_far[current.blockNum] < current.priority) {
            continue;
        }

        //Check if finished
        if (current.blockNum == end_num) {
            solved = true;
            break;
        }

        for (int next_num : blocks_[current.blockNum]->GetConnections()) {
            Block *next = GetBlock(next_num);
            int next_weight = next->GetWeight();
            if (next_weight != Block::kInfiniteWeight) {
                int new_cost = cost_so_far[current.blockNum] + next_weight;
                if (cost_so_far.find(next_num) == cost_so_far.end()
                    || new_cost < cost_so_far[next_num]) {
                    cost_so_far[next_num] = new_cost;
                    frontier.push({ new_cost, next_num });
                    came_from[next_num] = current.blockNum;
                }
            }
        }
    }
    if (solved) {
        return ReconstructPath(start_num, end_num, came_from);
    }
    else {
        std::vector<Block*> out_v;
        out_v.clear();
        return out_v;
    }
}

std::vector<Block*> TrackLine::ReconstructPath(int start_num, int end_num, std::unordered_map<int, int> came_from) const {
    std::vector<Block*> path;
    int current = end_num;
    while (current != start_num) {
        path.push_back(GetBlock(current));
        current = came_from[current];
    }
    path.push_back(GetBlock(start_num));
    std::reverse(path.begin(), path.end());
    return path;
}

void TrackLine::UpdateThroughput() {
    int throughput = 0;
    for (Station *s : stations_)
        throughput += s->GetSales();
    emit ThroughputUpdated(throughput);
}
