#include "simulation.h"
#include "ui_simulation.h"
#include "trackmodelsh.h"

#include <QTime>
#include <QFile>
#include <QMessageBox>
#include <sstream>
#include <QObject>
#include <vector>
#include <QDebug>


Simulation::Simulation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Simulation)
{
    ui->setupUi(this);
    startTimer(1000);

    fail_mode_selec = new FailureModeSelector(this);
    station_details = new StationDetails(this);
    track_details = new TrackDetails(this);
    beacon = new Beacon(this);
    timer = std::make_shared<QTimer>(new QTimer());
    ptimer = std::make_shared<QTimer>(new QTimer());

    timer->setInterval(1000);
    ptimer->setInterval(400);

    currentBlockNum = 0;

    QObject::connect(timer.get(), &QTimer::timeout, &TrackModelSH::Get(), &TrackModelSH::getTimerTicked);
    QObject::connect(ptimer.get(), &QTimer::timeout, &TrackModelSH::Get(), &TrackModelSH::getPTimerTicked);


    QList<QPushButton*> buttons = ui->centralwidget->findChildren<QPushButton*>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton* button : buttons) {
       QString button_name = button->objectName();
       if (button_name.contains("yard", Qt::CaseInsensitive)) {
           // Yard button has no effects
           continue;
       } else if (button_name.startsWith("station")) {
           connect(button, &QPushButton::clicked, this, &Simulation::station_clicked);
       } else if (button_name.startsWith("beacon")) {
           connect(button, &QPushButton::clicked, this, &Simulation::beacon_clicked);
       } else if (button_name.startsWith("block")) {
           connect(button, &QPushButton::clicked, this, &Simulation::block_clicked);
       } else if (button_name.startsWith("switch")) {
           connect(button, &QPushButton::clicked, this, &Simulation::switch_clicked);
       } else {
           // Add the block closed/opened handler
           //connect(button, &QPushButton::clicked, this, &Simulation::block_clicked);
       }
   }

    QStringList blockData;
    QFile file("redline_TrackDetails.csv");

    int blockCount = 76;
    int stationCount = 85;
    int beaconCount = 101;

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    setLine(0);

    while(!in.atEnd()) {
        QString line = in.readLine();

        blockData = line.split(",");

        if(blockData.at(0).toInt() > 0 && blockData.at(0).toInt() <= blockCount){
            setSpeed(blockData.at(3).toInt());
            setLength(blockData.at(1).toInt());
            setGrade(blockData.at(2).toDouble());
            setElevation(blockData.at(4).toDouble());
        }
        if(blockData.at(0).toInt() > blockCount + 1 && blockData.at(0).toInt() <= stationCount){
            setStationName(blockData.at(1));
            setTicketSales(blockData.at(2).toInt());
            setBoarding(blockData.at(3).toInt());
            setDisembarking(blockData.at(4).toInt());
        }
        if(blockData.at(0).toInt() > stationCount && blockData.at(0).toInt() <= beaconCount){
            setBeaconStation(blockData.at(1));
            setBeaconSide(blockData.at(2));
        }

    }


    file.close();
}

Simulation::~Simulation()
{
    delete ui;
}


void Simulation::getAuthVector(std::vector<bool> auth){
    emit sendTrainAuthority(auth[getCurrentBlockNum()]);
}

void Simulation::getSpeedVector(std::vector<int> speed){
    emit sendTrainSpeed(speed[getCurrentBlockNum()]);
}

void Simulation::getBeaconVector(std::vector<QString>,std::vector<QString>){

    emit sendBeacon(1, beaconStation[getCurrentBlockNum()] + "," + beaconSide[getCurrentBlockNum()]);
}

void Simulation::emitTrackInfo(){
    emit sendBlockInfo(getSpeed(), getLength(), getLine());
}

void Simulation::on_failSelectButton_clicked()
{

    fail_mode_selec->show();
}

void Simulation::calculateBlock(int trainNum, double distance){

    setTotalDistance(distance + getTotalDistance());
    qDebug() << "Total Distance: " << getTotalDistance();


    double totalMeters = getTotalDistance();
    int blockNum = 0;

    if (totalMeters < 75) {
        blockNum = 0;
    } else if (totalMeters < 150) {
        blockNum = 9;
    } else if (totalMeters < 225) {
        blockNum = 8;
    } else if (totalMeters < 300) {
        blockNum = 7;
    } else if (totalMeters < 350){
        blockNum = 6;
    } else if (totalMeters < 400){
        blockNum = 5;
    } else if (totalMeters < 450){
        blockNum = 4;
    } else if (totalMeters < 500){
        blockNum = 3;
    } else if (totalMeters < 550){
        blockNum = 2;
    } else if (totalMeters < 600){
        blockNum = 1;
    } else if (totalMeters < 650){
        blockNum = 16;
    }
    setPrevBlockNum(getCurrentBlockNum());
    setCurrentBlockNum(blockNum);

    emit sendCurrentBlockNum(getCurrentBlockNum(), getPrevBlockNum());
    setOccupied();
}


void Simulation::timerEvent(QTimerEvent *event)
{
    QLabel *label2 = ui->date_label;
    label2->setText(QDate::currentDate().toString("MM/dd/yyyy"));
    QLabel *label = ui->time_label;
    label->setText(TrackModelSH::Get().sim_time_.toString("hh:mm:ss"));
}

void Simulation::on_tempEdit_textEdited(const QString &arg1)
{
    if(arg1.toInt() <= 32){
        track_details->setHeaters(true);
    }else{
        track_details->setHeaters(false);
    }
}

void Simulation::station_clicked(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int station_num;

    station_num = button->text().toInt() - 1;

    emit new_station(getStationName().at(station_num),QString::number(getTicketSales().at(station_num)),"1",QString::number(getBoarding().at(station_num)),QString::number(getDisembarking().at(station_num)));

    station_details->show();
}

void Simulation::beacon_clicked(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int beacon_num;

    beacon_num = button->text().toInt() - 1;

    emit new_beacon(getBeaconStation().at(beacon_num),getBeaconSide().at(beacon_num));
    beacon->show();
}

void Simulation::block_clicked(){

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int block_num;

    block_num = button->text().toInt() - 1;

    emit new_block(QString::number(getGrades().at(block_num)),QString::number(getElevation().at(block_num)),QString::number(getLength().at(block_num)),QString::number(getSpeed().at(block_num)),"Two-Way");
    track_details ->show();
}

void Simulation::switch_clicked(){

}


//BLOCK DETAILS SETTERS AND GETTERS

void Simulation::setLength(int l){
    lengths.push_back(l);
}

std::vector<int> Simulation::getLength(){
    return lengths;
}

void Simulation::setSpeed(int s){
    speed_limits.push_back(s);
}

std::vector<int> Simulation::getSpeed(){
    return speed_limits;
}

void Simulation::setLine(bool l){
    line = l;
}

bool Simulation::getLine(){
    return line;
}

void Simulation::setGrade(double g){
    grade.push_back(g);
}

std::vector<double> Simulation::getGrades(){
    return grade;
}

void Simulation::setElevation(double e){
    elevation.push_back(e);
}

std::vector<double> Simulation::getElevation(){
    return elevation;
}

int Simulation::getCurrentBlockNum(){
    return currentBlockNum;
}
void Simulation::setCurrentBlockNum(int blockNum){
    currentBlockNum = blockNum;
}

int Simulation::getPrevBlockNum(){
    return prevBlockNum;
}

void Simulation::setPrevBlockNum(int p){
    prevBlockNum = p;
}

double Simulation::getTotalDistance(){
    return totalDistance;
}
void Simulation::setTotalDistance(double d){
    totalDistance = d;
}


//BEACON DETAILS SETTERS AND GETTERS

std::vector<QString> Simulation::getBeaconStation(){
    return beaconStation;
}
void Simulation::setBeaconStation(QString s){
    beaconStation.push_back(s);
}
std::vector<QString> Simulation::getBeaconSide(){
    return beaconSide;
}
void Simulation::setBeaconSide(QString s){
    beaconSide.push_back(s);
}

//STATION DETAIL SETTERS AND GETTERS

std::vector<QString> Simulation::getStationName(){
    return stationName;
}

void Simulation::setStationName(QString n){
    stationName.push_back(n);
}

std::vector<int> Simulation::getTicketSales(){
    return ticketSales;
}

void Simulation::setTicketSales(int t){


    ticketSales.push_back(t);
}

std::vector<int> Simulation::getBoarding(){
    return boarding;
}

void Simulation::setBoarding(int b){
    boarding.push_back(b);
}

std::vector<int> Simulation::getDisembarking(){
    return disembarking;
}

void Simulation::setDisembarking(int d){
    disembarking.push_back(d);
}


//MOVING TRAIN


void Simulation::setOccupied(){
    QString block = "block" + QString::number(getCurrentBlockNum());
    QString prevBlock = "block" + QString::number(getPrevBlockNum());
    qDebug() << "TM: block = " << block;

    QLabel * lbl = ui->centralwidget->findChild<QLabel*>(block);
    QLabel * lbl2 = ui->centralwidget->findChild<QLabel *>(prevBlock);

    //if (lbl2) {
    //    lbl2->setStyleSheet(ui->blueBlock->styleSheet());
    //}
    if (lbl) {
        qDebug() << "TM: found lbl!!!";
        lbl->setStyleSheet(ui->yellowBlock->styleSheet());
    }
}

void Simulation::on_startButton_clicked()
{
    timer->setInterval(1000);
    ptimer->setInterval(400);
    timer->start();
    ptimer->start();
}

void Simulation::on_startButton_2_clicked()
{
    timer->setInterval(100);
    ptimer->setInterval(40);
    timer->start();
    ptimer->start();
}

void Simulation::on_stopButton_clicked()
{
    timer->stop();
    ptimer->stop();
}
