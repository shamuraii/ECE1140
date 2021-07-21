#include "trainmodelmovementdialog.h"
#include "ui_trainmodelmovementdialog.h"

#include <string>
#include <iostream>

TrainModelMovementDialog::TrainModelMovementDialog(QWidget *parent, TrainModelData* d) :
    QDialog(parent),
    ui(new Ui::TrainModelMovementDialog),
    data(d)
{
    ui->setupUi(this);
    //update();
}

TrainModelMovementDialog::~TrainModelMovementDialog()
{
    delete ui;
}

void TrainModelMovementDialog::update()
{
    std::string s1 = "Commanded Power: " + std::to_string(data->getCommandedPower()) + " W";
    ui->label->setText(QString::fromStdString(s1));
    std::string s2 = "Actual Power: " + std::to_string(data->getActualPower()) + " W";
    ui->label_2->setText(QString::fromStdString(s2));
    std::string s3 = "Commanded Speed: " + std::to_string(data->getCommandedSpeed()) + " Mph";
    ui->label_3->setText(QString::fromStdString(s3));
    std::string s4 = "Actual Speed: " + std::to_string(data->getActualSpeed()) + " Mph";
    ui->label_4->setText(QString::fromStdString(s4));
    std::string s5 = "Authority: " + std::to_string(data->getAuthority());
    ui->label_5->setText(QString::fromStdString(s5));
    std::string s6 = "Acceleration Limit: " + std::to_string(data->getAccelLimit()) + " Mph/s";
    ui->label_6->setText(QString::fromStdString(s6));
    std::string s7 = "Deceleration Limit: " + std::to_string(data->getDecelLimit()) + " Mph/s";
    ui->label_7->setText(QString::fromStdString(s7));
    std::string s8 = "Speed Limit: " + std::to_string(data->getSpeedLimit()) + " Mph";
    ui->label_8->setText(QString::fromStdString(s8));
}
