#include "wsmainwindow.h"
#include "track_control.h"
#include "wssh.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    track_control track_controller;
    QApplication a(argc, argv);
    WSMainWindow w;
    w.show();
    return a.exec();
}
