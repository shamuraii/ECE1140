#ifndef SIMULATION_H
#define SIMULATION_H

#include <QMainWindow>
#include <QTimerEvent>
#include <QTimer>
#include <QObject>
#include <memory>
#include <vector>

#include "failuremodeselector.h"
#include "trackdetails.h"
#include "stationdetails.h"
#include "beacon.h"
#include "uploadtrack.h"

namespace Ui {
class Simulation;
}

class Simulation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Simulation(QWidget *parent = nullptr);
    ~Simulation();
    FailureModeSelector *fail_mode_selec;
    TrackDetails *track_details;
    StationDetails *station_details;
    Beacon *beacon;
    std::shared_ptr<QTimer> timer;
    std::shared_ptr<QTimer> ptimer;

    void setLength(int);
    std::vector<int> getLength();
    void setSpeed(int);
    std::vector<int> getSpeed();
    void setLine(bool line);
    bool getLine();
    void setGrade(double);
    std::vector<double> getGrades();
    void setElevation(double);
    std::vector<double> getElevation();
    int getCurrentBlockNum();
    void setCurrentBlockNum(int);
    int getPrevBlockNum();
    void setPrevBlockNum(int);
    double getTotalDistance();
    void setTotalDistance(double);
    void setOccupied();


    void station_clicked();
    void beacon_clicked();
    void block_clicked();
    void switch_clicked();
    void emitTrackInfo();

    std::vector<QString> getStationName();
    //void setStation
    std::vector<int> getTicketSales();
    std::vector<int> getBoarding();
    std::vector<int> getDisembarking;

    std::vector<QString> getBeaconStation();
    void setBeaconStation(QString);
    std::vector<QString> getBeaconSide();
    void setBeaconSide(QString);

signals:
    void new_block(QString g, QString e, QString l, QString s, QString d);
    void new_station(QString s, QString t, QString tr, QString b, QString d);
    void new_beacon(QString station, QString side);
    void sendBlockInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void sendBeaconInfo(std::vector<QString> beaconStation, std::vector<QString> side);
    void sendCurrentBlockNum(int curr, int prev);
    void sendTrainAuthority(bool);
    void sendTrainSpeed(int);


public slots:
    void on_failSelectButton_clicked();

    void on_tempEdit_textEdited(const QString &arg1);

    void calculateBlock(int trainNum, double distance);
    void getAuthVector(std::vector<bool>);
    void getSpeedVector(std::vector<int>);



private:
    Ui::Simulation *ui;
    std::vector<int> speed_limits;
    std::vector<int> lengths;
    bool line;
    std::vector<double> grade;
    std::vector<double> elevation;
    double totalDistance;
    int currentBlockNum;
    int prevBlockNum;
    std::vector<QString> stationName;
    std::vector<int> ticketSales;
    std::vector<int> boarding;
    std::vector<int> disembarking;
    std::vector<QString> beaconStation;
    std::vector<QString> beaconSide;

protected:
    void timerEvent(QTimerEvent *event);
private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
};

#endif // SIMULATION_H
