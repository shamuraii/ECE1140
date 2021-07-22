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

void TrainModelMovementDialog::setTrain(TrainModelData* d)
{
    data = d;
    update();
}

void TrainModelMovementDialog::update()
{
    std::string s1 = "Commanded Power: " + std::to_string(data->getCommandedPower()) + " W";
    ui->label->setText(QString::fromStdString(s1));
    std::string s2 = "Actual Power: " + std::to_string(data->getActualPower()) + " W";
    ui->label_2->setText(QString::fromStdString(s2));
    std::string s3 = "Commanded Speed: " + std::to_string(0.621*data->getCommandedSpeed()) + " Mph";
    ui->label_3->setText(QString::fromStdString(s3));
    std::string s4 = "Actual Speed: " + std::to_string(2.237*data->getActualSpeed()) + " Mph";
    ui->label_4->setText(QString::fromStdString(s4));
    std::string s5 = "Authority: " + std::to_string(data->getAuthority());
    ui->label_5->setText(QString::fromStdString(s5));
}
