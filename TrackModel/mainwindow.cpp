#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulation.h"
#include "debugger.h"
#include "trackmodelsh.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    debugger = new Debugger(this);
    track_select = new TrackSelect(this);
    upload_track = new UploadTrack(this);
    help = new HelpMenu(this);
    tmsh = new TrackModelSH(this);

    connect(track_select->simulation->fail_mode_selec, &FailureModeSelector::new_failure,
            debugger, &Debugger::updateFail);
    connect(track_select->simulation, &Simulation::new_block, track_select->simulation->track_details, &TrackDetails::update_track);
    //connect(upload_track->simulation, &Simulation::new_block, upload_track->simulation->track_details, &TrackDetails::update_track);

    connect(track_select->simulation, &Simulation::new_station, track_select->simulation->station_details, &StationDetails::update_station);

    connect(track_select->simulation, &Simulation::sendBlockInfo, &TrackModelSH::Get(), &TrackModelSH::updateBlockInfo);

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

