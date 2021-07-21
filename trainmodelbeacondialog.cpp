#include "trainmodelbeacondialog.h"
#include "ui_trainmodelbeacondialog.h"

TrainModelBeaconDialog::TrainModelBeaconDialog(QWidget *parent, TrainModelData* d) :
    QDialog(parent),
    ui(new Ui::TrainModelBeaconDialog),
    data(d)
{
    ui->setupUi(this);
    //update();
}

TrainModelBeaconDialog::~TrainModelBeaconDialog()
{
    delete ui;
}

void TrainModelBeaconDialog::update()
{
    ui->label->setText("Current: " + QString::fromStdString(data->getCurrentStation()));
    ui->label_2->setText("Previous: " + QString::fromStdString(data->getLastStation()));
    ui->label_3->setText((data->getDoorSide()) ? "Door Side: Left" : "Door Side: Right");
}
