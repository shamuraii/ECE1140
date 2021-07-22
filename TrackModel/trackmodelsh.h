#ifndef TRACKMODELSH_H
#define TRACKMODELSH_H

#include <QObject>
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
    void sendTimerTicked();
    void sendPtimerTicked();

    //internal
    void sendDistanceTraveled(int, double);

public slots:
    //From Train Model
    void getDistanceTraveled(int trainNum, double distance);//meters

    //From Track Controller
    void getAuthority(std::vector<bool>);
    void getCommandedSpeed(std::vector<int>);
    //void getSwitchPosition(int switchBlock, int pointingTo);
    //void getLightStatus();

    //internal
    //void getTrainNum(int);
    void updateBlockInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void getCurrentBlockNum(int curr, int prev);

    void getTimerTicked();
    void getPTimerTicked();

};

#endif // TRACKMODELSH_H
