#ifndef CTRAIN_H
#define CTRAIN_H

#include <QObject>
#include <QDateTime>
#include <vector>

#include "block.h"
#include "station.h"
#include "trackline.h"

namespace ctc {

class CTrain : public QObject
{
    Q_OBJECT
private:
    int num_;
    Station *destination_;
    QTime departure_time_;
    QTime estimated_arrival_;
    TrackLine *line_;
    Block *location_;
    std::vector<Station*> stops_;
    std::vector<Block*> route_;
    int route_index_;
    bool stopped_;
    bool dispatched_;
    bool manually_routed_;

    void CalculateEstimatedArrival();

public:
    explicit CTrain(Station *destination, QTime departure_time, TrackLine *line);
    int GetNum() const;
    std::vector<Block*> GetRoute() const;
    TrackLine *GetLine() const;
    Station *GetDestination() const;
    Block *GetLocation() const;
    Block *GetNextBlock() const;
    QTime GetDepartTime() const;
    QTime GetArrivalTime() const;

    QString GetStopsString() const;
    QString GetRouteString() const;

    int GetSugSpeed(bool mph) const;
    int GetSugAuth() const;

    void SetNum(int num);
    void TrainStopped();
    void DispatchTrain();

    void IncrementRouteIndex();

    int LengthToNextStop();

public slots:
    void SetLocation(Block *new_location);
    void UpdateOutputs();
    void RecalculateRoute(int force_num = -1, Station *new_destination = nullptr);
    void DebugAdvanceTrain();

signals:
    void DebugMovedTrain(Block *old_loc, Block *new_loc);
};

}

#endif // CTRAIN_H
