#ifndef TRACKMODELSH_H
#define TRACKMODELSH_H

#include <QObject>

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
    void sendBeaconInfo(QString);
    void sendAuthority(int);
    void sendTrainNum(int);
    void sendCommandedSpeed(int, int);

    void sendBoarding(int);

    void sendTrackInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void sendLineSales(int sales, bool line);

    void sendTimerTicked();
    void sendPtimerTicked();

public slots:
    void getActualSpeed(int);
    void getDistanceTraveled(int);
    void getAuthority(int);
    void getCommandedSpeed(int);

    void getTimerTicked();
    void getPTimerTicked();

};

#endif // TRACKMODELSH_H
