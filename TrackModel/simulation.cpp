#include "simulation.h"
#include "ui_simulation.h"
#include "trackmodelsh.h"

#include <QTime>
#include <QFile>
#include <QMessageBox>
#include <sstream>
#include <QObject>


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
}

Simulation::~Simulation()
{
    delete ui;
}

void Simulation::on_failSelectButton_clicked()
{

    fail_mode_selec->show();
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

