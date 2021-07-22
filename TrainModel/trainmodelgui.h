#ifndef TRAINMODELGUI_H
#define TRAINMODELGUI_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <vector>
#include <QTimer>

#include "trainmodelmovementdialog.h"
#include "trainmodelbeacondialog.h"
#include "trainmodelfailuredialog.h"
#include "trainmodeldebugdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TrainModelGUI; }
QT_END_NAMESPACE

class TrainModelGUI : public QMainWindow
{
    Q_OBJECT

public:
    TrainModelGUI(QWidget *parent = nullptr);
    ~TrainModelGUI();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void updateGUI();

    void tick();

signals:
    void GUIChanged();

private:
    unsigned int timer_interval;

    std::vector<QGraphicsItem*> shapes;
    Ui::TrainModelGUI *ui;
    QGraphicsScene train_scene;

    TrainModelData* data;

    TrainModelMovementDialog moveDialog;
    TrainModelBeaconDialog beaconDialog;
    TrainModelFailureDialog failureDialog;
    TrainModelDebugDialog debugDialog;

    QTimer timer, long_timer;

    void drawTrain();
    void keyPressEvent(QKeyEvent *event);
};
#endif // TRAINMODELGUI_H
