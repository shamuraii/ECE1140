#include "ctc_home.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CtcGUI w;
    w.show();
    return a.exec();
}
