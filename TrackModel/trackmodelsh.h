#ifndef TRACKMODELSH_H
#define TRACKMODELSH_H

#include <QObject>
#include <QTime>
#include <vector>


class TrackModelSH : public QObject
{
    Q_OBJECT

public:
    TrackModelSH(TrackModelSH const&) = delete;
    void operator=(TrackModelSH const&) = delete;
    static TrackModelSH& Get() {
        static TrackModelSH instance;
        return instance;
    }
    QTime sim_time_ = QTime::fromMSecsSinceStartOfDay(0);

private:
    explicit TrackModelSH() {}


signals:
    //To Train Model
    void sendBeaconInfo(int trainNum, QString beacon);
    void sendAuthority(int trainNum, bool auth);
    void sendCommandedSpeed(int trainNum, int speed);//km/h


    //To track controller
    //void sendBrokenRail(int blockNum, bool isFailed); //eventually
    void sendCurrentBlockNum(int curr, int prev);

    //To CTC
    void sendTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void sendLineSales(int sales, bool line); //eventually

    //Time
    void sendTimerTicked(QTime sim_time);
    void sendPtimerTicked();

    //internal
    void sendDistanceTraveled(int, double);
    void sendAuthVector(std::vector<bool>);
    void sendSpeedVector(std::vector<int>);

 public slots:
    //From Train Model
    void getDistanceTraveled(int trainNum, double distance);//meters

    //From Track Controller
    void getAuthority(std::vector<bool>);
    void getCommandedSpeed(std::vector<int>);
    //void getSwitchPosition(int switchBlock, int pointingTo, bool line);
    //void getLightStatus();

    //internal
    //void getTrainNum(int);
    void updateBlockInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void getCurrentBlockNum(int curr, int prev);

    void getTimerTicked();
    void getPTimerTicked();
    void getTrainAuthority(bool auth);
    void getTrainSpeed(int speed);
    void updateBeaconInfo(int trainNum, QString station);

};

#endif // TRACKMODELSH_H
