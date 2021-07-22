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


signals:
    void new_block(QString g, QString e, QString l, QString s, QString d);
    void new_station(QString s, QString t, QString tr, QString b, QString d);
    void sendBlockInfo(std::vector<int> speed_limits, std::vector<int> lengths, bool line);
    void sendCurrentBlockNum(int curr, int prev);

public slots:
    void on_failSelectButton_clicked();

    void on_tempEdit_textEdited(const QString &arg1);

    void calculateBlock(int trainNum, double distance);



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

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SIMULATION_H
