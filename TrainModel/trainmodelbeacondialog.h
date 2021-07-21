#ifndef TRAINMODELBEACONDIALOG_H
#define TRAINMODELBEACONDIALOG_H

#include <QDialog>

#include "trainmodeldata.h"

namespace Ui {
class TrainModelBeaconDialog;
}

class TrainModelBeaconDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainModelBeaconDialog(QWidget *parent = nullptr, TrainModelData* d = nullptr);
    ~TrainModelBeaconDialog();

private:
    Ui::TrainModelBeaconDialog *ui;
    TrainModelData* data;

public slots:
    void update();
};

#endif // TRAINMODELBEACONDIALOG_H
