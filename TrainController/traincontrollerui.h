#ifndef TRAINCONTROLLERUI_H
#define TRAINCONTROLLERUI_H

#include <QWidget>
#include "traincontrollerhandler.h"
#include "traincontroller.h"
#include "testui.h"
#include "traincontrollersignalhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TrainControllerUi; }
QT_END_NAMESPACE

class TrainControllerUi : public QWidget
{
    Q_OBJECT

public:
    TrainControllerUi(QWidget *parent = nullptr);
    ~TrainControllerUi();

public slots:
    void NewTrain(int);
    void Update(TrainController);

signals:
    void lights(int,bool);
    void ToggleServiceBrake(int);
    void ToggleHeadlights(int);
    void ToggleCabinLights(int);
    void SetCabinTemp(int,double);
    void StartAnnouncement(int);
    void NewSetpointSpeed(int,double);
    void ToggleLeftDoor(int);
    void ToggleRightDoor(int);
    void SetKp(int,double);
    void SetKi(int,double);
    void UpdateGui(int);
    void ToggleEmergencyBrake(int);
    void ToggleManualMode(int);


private slots:

    void on_service_brake_button_clicked();

    void on_headlights_button_clicked();

    void on_cabin_lights_button_clicked();

    void on_cabin_temp_button_clicked();

    void on_announcement_button_clicked();

    void on_setpoint_speed_button_clicked();

    void on_left_door_button_clicked();

    void on_right_door_button_clicked();

    void on_kp_set_button_clicked();

    void on_ki_set_button_clicked();

    void on_train_index_currentIndexChanged(int index);

    void on_emergency_brake_button_clicked();

    void on_debugger_clicked();

    void on_manual_mode_button_clicked();

private:
    Ui::TrainControllerUi *ui;

    bool IsNumber(string);
    void SetUpSignals();

    TrainControllerHandler train_handler;
    TestUi test_ui;
};
#endif // TRAINCONTROLLERUI_H
