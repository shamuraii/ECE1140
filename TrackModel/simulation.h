#ifndef SIMULATION_H
#define SIMULATION_H

#include <QMainWindow>
#include <QTimerEvent>
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


    void station_clicked();
    void beacon_clicked();
    void block_clicked();
    void switch_clicked();

signals:
    void new_block(QString g, QString e, QString l, QString s, QString d);

private slots:
    void on_failSelectButton_clicked();

    void on_tempEdit_textEdited(const QString &arg1);



private:
    Ui::Simulation *ui;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // SIMULATION_H
