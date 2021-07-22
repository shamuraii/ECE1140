#include "simulation.h"
#include "ui_simulation.h"
#include "trackmodelsh.h"

#include <QTime>
#include <QFile>
#include <QMessageBox>
#include <sstream>
#include <QObject>
#include <vector>


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
    QFile file("C:\\Users\\Amy\\Documents\\GitHub\\ECE1140\\TrackModel\\redline_TrackDetails.csv");

    int lineCount = 76;

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    setLine(0);

    while(!in.atEnd()) {
        QString line = in.readLine();

        blockData = line.split(",");

        if(blockData.at(0).toInt() > 0 && blockData.at(0).toInt() <= lineCount){
            setSpeed(blockData.at(3).toInt());
            setLength(blockData.at(1).toInt());
            setGrade(blockData.at(2).toInt());
            setElevation(blockData.at(4).toInt());
        }

    }


    file.close();
    emitTrackInfo();
}

Simulation::~Simulation()
{
    delete ui;
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
    int prevBlock;

    double totalMeters = getTotalDistance();
    int blockNum = 0;

    //subtracting distance from the yard to block 9
    totalMeters = totalMeters - 75;

    if(totalMeters > 0){
        for(blockNum = 9; totalMeters > 0; blockNum--){
            totalMeters = totalMeters - getLength().at(blockNum);
        }
        setCurrentBlockNum(blockNum + 1);
    }else{
        setCurrentBlockNum(0);
    }

    if(blockNum == 7 || blockNum == 8){
        prevBlock = blockNum + 1;
    }else{
        prevBlock = 0;
    }

    emit sendCurrentBlockNum(getCurrentBlockNum(), prevBlock);
    setOccupied();
}


void Simulation::timerEvent(QTimerEvent *event)
{
    QLabel *label2 = ui->date_label;
    label2->setText(QDate::currentDate().toString("MM/dd/yyyy"));
    QLabel *label = ui->time_label;
    label->setText(QTime::currentTime().toString("hh:mm:ss"));
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
    QString s, t, tr, b, d;
    int station_num;
    QStringList stationData;
    QFile file("C:\\Users\\Amy\\Documents\\GitHub\\ECE1140\\TrackModel\\redline_TrackDetails.csv");

    station_num = button->text().toInt();

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();

        stationData = line.split(",");

        if(stationData.at(0).toInt() == station_num){
            s = stationData.at(1);
            t = stationData.at(2);
            b = stationData.at(3);
            d = stationData.at(4);
        }

    }


    file.close();

    emit new_station(s,t,"1",b,d);

    station_details->show();
}

void Simulation::beacon_clicked(){

    beacon->show();
}

void Simulation::block_clicked(){

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString g, e, l, s, d;
    int block_num;
    QStringList blockData;
    QFile file("C:\\Users\\Amy\\Documents\\GitHub\\ECE1140\\TrackModel\\redline_TrackDetails.csv");

    block_num = button->text().toInt();

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();

        blockData = line.split(",");

        if(blockData.at(0).toInt()==block_num){
            g = blockData.at(2);
            e = blockData.at(4);
            l = blockData.at(1);
            s = blockData.at(3);
            d = blockData.at(5);
        }

    }


    file.close();

    emit new_block(g,e,l,s,d);
    track_details ->show();
}

void Simulation::switch_clicked(){

}


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
double Simulation::getTotalDistance(){
    return totalDistance;
}
void Simulation::setTotalDistance(double d){
    totalDistance = d;
}

void Simulation::setOccupied(){
    QString block = "block" + QString::number(getCurrentBlockNum());

    QLabel * lbl = this->findChild<QLabel *>(block);

    lbl->setStyleSheet(ui->yellowBlock->styleSheet());


}
