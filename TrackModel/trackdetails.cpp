#include "trackdetails.h"
#include "ui_trackdetails.h"

bool heaters;

TrackDetails::TrackDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackDetails)
{
    ui->setupUi(this);

    QLabel *label = ui->heater_status;
    if(heaters){
        label->setText("ON");
    }else{
        label->setText("OFF");
    }




}

TrackDetails::~TrackDetails()
{
    delete ui;
}

void TrackDetails::setHeaters(bool b){
    heaters = b;

    QLabel *label = ui->heater_status;
    if(heaters){
        label->setText("ON");
    }else{
        label->setText("OFF");
    }
}

bool TrackDetails::getHeaters(){
    return heaters;
}


void TrackDetails::update_track(QString g, QString e, QString l, QString s, QString d){
    ui->grade_label->setText(g);
    ui->elevation_label->setText(e);
    ui->length_label->setText(l);
    ui->speed_label->setText(s);
    ui->direction_label->setText(d);
}
