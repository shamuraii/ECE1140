#include <QApplication>

#include "ctc/ctc_home.h"
#include "TrackModel/mainwindow.h"
#include "TrainController/traincontrollerui.h"
#include "TrainModel/trainmodelgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CtcGUI ctc;
    ctc.show();
    MainWindow trackm;
    trackm.show();
    TrainControllerUi trc;
    trc.show();
    TrainModelGUI trainm;
    trainm.show();

    return a.exec();
}