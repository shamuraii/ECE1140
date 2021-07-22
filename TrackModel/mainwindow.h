#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simulation.h"
#include "uploadtrack.h"
#include "helpmenu.h"
#include "trackselect.h"
#include "debugger.h"
#include "trackmodelsh.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
