#ifndef TRACKSELECT_H
#define TRACKSELECT_H

#include <QDialog>
#include "simulation.h"


namespace Ui {
class TrackSelect;
}

class TrackSelect : public QDialog
{
    Q_OBJECT

public:
    explicit TrackSelect(QWidget *parent = nullptr);
    ~TrackSelect();
    void FillTable();
    Simulation *simulation;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::TrackSelect *ui;

};

#endif // TRACKSELECT_H
