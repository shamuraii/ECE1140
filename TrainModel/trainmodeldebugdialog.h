#ifndef TRAINMODELDEBUGDIALOG_H
#define TRAINMODELDEBUGDIALOG_H

#include <QDialog>
#include "trainmodeldata.h"

namespace Ui {
class TrainModelDebugDialog;
}

class TrainModelDebugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainModelDebugDialog(QWidget *parent = nullptr, TrainModelData* d = nullptr);
    ~TrainModelDebugDialog();

private:
    Ui::TrainModelDebugDialog *ui;
    TrainModelData* data;

signals:
    void dataChanged();

public slots:
    void update();
private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
};

#endif // TRAINMODELDEBUGDIALOG_H
