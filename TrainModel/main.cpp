#include "trainmodelgui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrainModelGUI w;
    w.show();
    return a.exec();
}
