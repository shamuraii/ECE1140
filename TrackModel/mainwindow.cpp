#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulation.h"
#include "debugger.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    debugger = new Debugger(this);
    track_select = new TrackSelect(this);
    upload_track = new UploadTrack(this);
    help = new HelpMenu(this);

    connect(track_select->simulation->fail_mode_selec, &FailureModeSelector::new_failure,
            debugger, &Debugger::updateFail);
    connect(track_select->simulation, &Simulation::new_block, track_select->simulation->track_details, &TrackDetails::update_track);
    //connect(upload_track->simulation, &Simulation::new_block, upload_track->simulation->track_details, &TrackDetails::update_track);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    track_select->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    upload_track -> show();
}


void MainWindow::on_pushButton_4_clicked()
{
    help -> show();
}


void MainWindow::on_debug_button_clicked()
{
    debugger -> show();
}

