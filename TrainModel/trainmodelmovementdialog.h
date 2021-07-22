#ifndef TRAINMODELMOVEMENTDIALOG_H
#define TRAINMODELMOVEMENTDIALOG_H

#include <QDialog>

#include "trainmodeldata.h"

namespace Ui {
class TrainModelMovementDialog;
}

class TrainModelMovementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainModelMovementDialog(QWidget *parent = nullptr, TrainModelData* d = nullptr);
    ~TrainModelMovementDialog();

    void setTrain(TrainModelData*);

public slots:
    void update();

private:
    Ui::TrainModelMovementDialog *ui;
    TrainModelData* data;
};

#endif // TRAINMODELMOVEMENTDIALOG_H
