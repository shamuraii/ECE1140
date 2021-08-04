#ifndef TESTUI_H
#define TESTUI_H

#include <QWidget>
#include <iostream>
#include <string>
#include "traincontroller.h"

using namespace std;

namespace Ui {
class TestUi;
}

class TestUi : public QWidget
{
    Q_OBJECT

public:
    explicit TestUi(QWidget *parent = nullptr);
    ~TestUi();

public slots:
    void ServiceBrake(int,bool);
    void NewPower(int,double);
    void Headlights(int,bool);
    void CabinLights(int,bool);
    void CabinTemp(int,double);
    void Announcement(int,QString);
    void LeftDoor(int,bool);
    void RightDoor(int,bool);
    void UpdateTest(TrainController);
    void EmergencyBrake(int,bool);
    void AddNewTrain(int);

signals:
    void NewTrain(int);
    void NewCommandedSpeed(int,double);
    void NewActualSpeed(int,double);
    void ToggleEmergencyBrake(int);
    void UpdateTestGui(int);
    void NewAuthority(int,int);
    void FailureMode(int, int);

private slots:
    void on_new_train_button_clicked();
    void on_commanded_speed_button_clicked();

    void on_actual_speed_button_clicked();

    void on_emergency_brake_button_clicked();

    void on_authority_button_clicked();

    void on_failure_mode_button_clicked();

    void on_train_index_currentIndexChanged(int index);

private:
    Ui::TestUi *ui;
    int num_trains;

    bool IsNumber(string);
    double MSToMPH(double);
    double MPHToKMPH(double);
};

#endif // TESTUI_H
