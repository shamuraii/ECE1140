#ifndef TRACKMODELINTERFACE_H
#define TRACKMODELINTERFACE_H

#include <QObject>
#include <string>

//Singleton interface class containing slots for the Track Model and others

//Track Model should be able to send a train the following data:
//commanded authority, beacon info, commanded speed

//CTC should be able to send the module the following data:
//train creation events (TODO)

//Track Model should receive the following data:
//distance traveled

//CTC should receive the following data:
//train stop events, stopping distance

//All slots and signals take the ID of the recipient train along with the data

class TrackModelInterface : public QObject
{
    Q_OBJECT
private:
    //Private constructor so it can't be instantiated
    TrackModelInterface() {}
public slots:
    //Slots for incoming data
	//Track Model
    void setAuthority(int, bool);
    void setBeaconInfo(int, QString);
    void setCommandedSpeed(int, int);
	
	//CTC
	void createTrain(int);
	
	//Timers
    void timerTicked();
    void ptimerTicked();

signals:
    //Signals for outgoing data
    void distanceTraveled(int train_num, double distance_m);
	void newTrain(int);
    //For CTC
    void trainStopped(int train_num);
	void stoppingDistance(int, long);
public:
    //Singleton functions
    static TrackModelInterface& getInstance()
    {
        static TrackModelInterface instance;
        return instance;
    }

    TrackModelInterface(const TrackModelInterface&) = delete;
    void operator=(const TrackModelInterface&) = delete;

};

#endif // TRACKMODELINTERFACE_H
