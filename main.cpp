#include <QApplication>
#include <QTimer>
#include <QObject>

#include "connections.h"
#include "ctc/ctc_home.h"
#include "TrackController/wsmainwindow.h"
#include "TrackModel/tm_mainwindow.h"
#include "TrainController/traincontrollerui.h"
#include "TrainModel/trainmodelgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConnectSystem();

    CtcGUI ctc;
    ctc.show();
    WSMainWindow ws;
    ws.show();
    TM_MainWindow trackm;
    trackm.show();
    TrainControllerUi trc;
    trc.show();
    TrainModelGUI trainm;
    trainm.show();

    return a.exec();
}
