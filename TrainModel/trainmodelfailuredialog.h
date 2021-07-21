#ifndef TRAINMODELFAILUREDIALOG_H
#define TRAINMODELFAILUREDIALOG_H

#include <QDialog>

#include "trainmodeldata.h"

namespace Ui {
class TrainModelFailureDialog;
}

class TrainModelFailureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainModelFailureDialog(QWidget *parent = nullptr, TrainModelData* d = nullptr);
    ~TrainModelFailureDialog();

    void setTrain(TrainModelData*);

signals:
    //void updateGUI();
    void brakeToggled(int, bool);
    void eBrakeToggled(int, bool);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

public slots:
    void update();

private:
    Ui::TrainModelFailureDialog *ui;
    bool brakes, ebrakes, engine_fail, signal_fail, brake_fail;

    TrainModelData* data;


};

#endif // TRAINMODELFAILUREDIALOG_H
