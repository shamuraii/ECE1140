#include "simulation.h"
#include "ui_simulation.h"

#include <QTime>
#include <QFile>
#include <QMessageBox>


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

    QList<QPushButton*> buttons = ui->centralwidget->findChildren<QPushButton*>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton* button : buttons) {
       QString button_name = button->objectName();
       if (button_name.contains("yard", Qt::CaseInsensitive)) {
           // Yard button has no effects
           continue;
       } else if (button_name.startsWith("station")) {
           // Add the switch handler
           connect(button, &QPushButton::clicked, this, &Simulation::station_clicked);
       } else if (button_name.startsWith("beacon")) {
           // Add the switch handler
           connect(button, &QPushButton::clicked, this, &Simulation::beacon_clicked);
       } else if (button_name.startsWith("block")) {
           // Add the switch handler
           connect(button, &QPushButton::clicked, this, &Simulation::block_clicked);
       } else if (button_name.startsWith("switch")) {
           // Add the switch handler
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
    station_details->show();
}

void Simulation::beacon_clicked(){

    beacon->show();
}

void Simulation::block_clicked(){

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString g, e, l, s, d;
    QFile file("redline_TrackDetails.xlsx");

    if (button) {
        int block_num = button->text().toInt();
    } else {
        QMessageBox::warning(this, "Error", "Invalid block_clicked signal sent.");
    }

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();

        QMessageBox msgbox;
        msgbox.setText(line);
    }


    file.close();

    emit new_block(g,e,l,s,d);
    track_details ->show();
}

void Simulation::switch_clicked(){

}

