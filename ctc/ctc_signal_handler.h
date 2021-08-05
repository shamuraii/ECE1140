#ifndef CTCSIGNALHANDLER_H
#define CTCSIGNALHANDLER_H

#include <QObject>
#include <QTime>

class CtcSH : public QObject
{
    Q_OBJECT
public:
    CtcSH(CtcSH const&) = delete;
    void operator=(CtcSH const&) = delete;
    static CtcSH& Get() {
        static CtcSH instance;
        return instance;
    }

private:
    explicit CtcSH() {}

public slots:
    // External
    void GetSwitchPosition(int pointing_to, bool line);
    void GetTrainLocation(std::vector<bool> occupancy, bool line);

    void GetTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void GetLineSales(int sales, bool line);
    void GetTrainStopped(int train_num);

    void TimedEvents(QTime sim_time);

    // Internal
    void OutputsUpdated(std::vector<bool> out_auth, std::vector<int> out_speed, bool line);
    void BlockMaint(int block_num, bool maint_mode, bool line);
    void SwitchMaint(int switch_num, bool maint_mode, bool line);
    void SwitchPos(int pointing_to, bool line);
    void TrainScheduled(int trainNum, bool line);
    void TrainDispatched(int trainNum, bool line);

signals:
    // External
    void ShareSugAuthority(std::vector<bool> out_auth, bool line);
    void ShareSugSpeed(std::vector<int> out_speed, bool line);
    void ShareBlockMaintenance(int block_num, bool maint_mode, bool line);
    void ShareSwitchMaintenance(int switch_num, bool maint_mode, bool line);
    void ShareSwitchPosition(int pointing_to, bool line);

    void NewTrain(int trainNum, bool line);
    void TrainDeparting(int trainNum, bool line);

    // Internal
    void UpdateOutputs();
    void RecalculateRoutes();
    void CheckTrainDepartures(QTime *sim_time);
    void RecalculateThroughput(QTime *sim_time);
    void NewSwitchPos(int pointing_to, bool line);
    void NewOccupancies(std::vector<bool> occupancy, bool line);
    void NewTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void NewLineSales(int sales, bool line);
    void TrainStopped(int train_num);
};

#endif // CTCSIGNALHANDLER_H
