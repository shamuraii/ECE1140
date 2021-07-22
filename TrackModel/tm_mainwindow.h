#ifndef TM_MAINWINDOW_H
#define TM_MAINWINDOW_H

#include <QMainWindow>
#include "simulation.h"
#include "uploadtrack.h"
#include "helpmenu.h"
#include "trackselect.h"
#include "debugger.h"
#include "trackmodelsh.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TM_MainWindow; }
QT_END_NAMESPACE

class TM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TM_MainWindow(QWidget *parent = nullptr);
    ~TM_MainWindow();
    UploadTrack *upload_track;
    HelpMenu *help;
    TrackSelect *track_select;
    Debugger *debugger;
    TrackModelSH *tmsh;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_debug_button_clicked();

private:
    Ui::TM_MainWindow *ui;

};
#endif // TM_MAINWINDOW_H
