#ifndef TRACKMODELINTERFACE_H
#define TRACKMODELINTERFACE_H

#include <QObject>
#include <string>

//Singleton interface class containing slots for the Track Model
//Track Model should be able to send a train the following data:
//commanded authority, current station, door side, commanded speed
//Track Model should receive the following data:
//speed

//All slots and signals take the ID of the recipient train along with the data

class TrackModelInterface : public QObject
{
    Q_OBJECT
private:
    //Private constructor so it can't be instantiated
    TrackModelInterface() {}
public slots:
    //Slots for incoming data
    void setAuthority(int, bool);
    void setBeaconInfo(QString);
    void setCommandedSpeed(int, int);

signals:
    //Signals for outgoing data
    void distanceTraveled(int train_num, double distance_m);
    //For CTC
    void trainStopped(int train_num);
public:
    //Singleton functions
    static TrackModelInterface& getInstance() {
        static TrackModelInterface instance;
        return instance;
    };
    TrackModelInterface(const TrackModelInterface&) = delete;
    void operator=(const TrackModelInterface&) = delete;

};

#endif // TRACKMODELINTERFACE_H
