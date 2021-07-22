#include "tm_mainwindow.h"
#include "ui_tm_mainwindow.h"
#include "simulation.h"
#include "debugger.h"
#include "trackmodelsh.h"


TM_MainWindow::TM_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TM_MainWindow)
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

    connect(track_select->simulation, &Simulation::new_station, track_select->simulation->station_details, &StationDetails::update_station);

    connect(track_select->simulation, &Simulation::sendBlockInfo, &TrackModelSH::Get(), &TrackModelSH::updateBlockInfo);

    connect(&TrackModelSH::Get(), &TrackModelSH::sendDistanceTraveled, track_select->simulation, &Simulation::calculateBlock);

    connect(track_select->simulation, &Simulation::sendCurrentBlockNum, &TrackModelSH::Get(), &TrackModelSH::getCurrentBlockNum);

    connect(track_select->simulation, &Simulation::sendTrainAuthority, &TrackModelSH::Get(), &TrackModelSH::getTrainAuthority);
    connect(track_select->simulation, &Simulation::sendTrainSpeed, &TrackModelSH::Get(), &TrackModelSH::getTrainSpeed);

    connect(&TrackModelSH::Get(), &TrackModelSH::sendAuthVector, track_select->simulation, &Simulation::getAuthVector);
    connect(&TrackModelSH::Get(), &TrackModelSH::sendSpeedVector, track_select->simulation, &Simulation::getSpeedVector);
}

TM_MainWindow::~TM_MainWindow()
{
    delete ui;
}


void TM_MainWindow::on_pushButton_clicked()
{
    track_select->show();
}


void TM_MainWindow::on_pushButton_2_clicked()
{
    upload_track -> show();
}


void TM_MainWindow::on_pushButton_4_clicked()
{
    help -> show();
}


void TM_MainWindow::on_debug_button_clicked()
{
    debugger -> show();
}

