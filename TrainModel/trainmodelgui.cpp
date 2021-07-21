#include "trainmodelgui.h"
#include "ui_trainmodelgui.h"

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include <iostream>
#include <trainmodeldatabase.h>

TrainModelGUI::TrainModelGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainModelGUI)
{
    //Create a train
    int id = TrainModelDatabase::createTrain();
    data = TrainModelDatabase::getTrainByID(id);

    failureDialog.setTrain(data);

    //Home updates dialogs
    QObject::connect(this, &TrainModelGUI::GUIChanged, &failureDialog, &TrainModelFailureDialog::update);
    //QObject::connect(this, &TrainModelGUI::GUIChanged, &moveDialog, &TrainModelMovementDialog::update);
    //QObject::connect(this, &TrainModelGUI::GUIChanged, &beaconDialog, &TrainModelBeaconDialog::update);

    //Dialogs update home
    QObject::connect(&debugDialog, &TrainModelDebugDialog::dataChanged, this, &TrainModelGUI::updateGUI);
    ui->setupUi(this);
    drawTrain();
    updateGUI();

    //Speed calculation tick
    timer_interval = 100;
    connect(&timer, &QTimer::timeout, this, &TrainModelGUI::tick);
    timer.start(timer_interval);
}

TrainModelGUI::~TrainModelGUI()
{
    for (auto shape : shapes) delete shape;
    delete ui;
}

void TrainModelGUI::drawTrain()
{
    //TODO: create helper function to create and store rects and circles

    //Make background black
    train_scene.setBackgroundBrush(Qt::black);

    //Drawing train rects
    QGraphicsRectItem* rect1 = new QGraphicsRectItem(0,0,150,80);
    rect1->setBrush(Qt::white);
    shapes.push_back(rect1);
    train_scene.addItem(rect1);
    QGraphicsRectItem* rect2 = new QGraphicsRectItem(200,0,150,80);
    rect2->setBrush(Qt::white);
    shapes.push_back(rect2);
    train_scene.addItem(rect2);
    QGraphicsRectItem* rect3 = new QGraphicsRectItem(150,70,50,10);
    rect3->setBrush(Qt::white);
    shapes.push_back(rect3);
    train_scene.addItem(rect3);
    QGraphicsRectItem* rect4 = new QGraphicsRectItem(210,-60,30,60);
    rect4->setBrush(Qt::white);
    shapes.push_back(rect4);
    train_scene.addItem(rect4);
    QGraphicsRectItem* rect5 = new QGraphicsRectItem(320,-50,10,50);
    rect5->setBrush(Qt::white);
    shapes.push_back(rect5);
    train_scene.addItem(rect5);
    QGraphicsRectItem* rect6 = new QGraphicsRectItem(305,-60,40,10);
    rect6->setBrush(Qt::white);
    shapes.push_back(rect6);
    train_scene.addItem(rect6);

    //Drawing train wheels
    QGraphicsEllipseItem* circ1 = new QGraphicsEllipseItem(5,80,30,30);
    circ1->setBrush(Qt::white);
    shapes.push_back(circ1);
    train_scene.addItem(circ1);
    QGraphicsEllipseItem* circ2 = new QGraphicsEllipseItem(43,80,30,30);
    circ2->setBrush(Qt::white);
    shapes.push_back(circ2);
    train_scene.addItem(circ2);
    QGraphicsEllipseItem* circ3 = new QGraphicsEllipseItem(79,80,30,30);
    circ3->setBrush(Qt::white);
    shapes.push_back(circ3);
    train_scene.addItem(circ3);
    QGraphicsEllipseItem* circ4 = new QGraphicsEllipseItem(115,80,30,30);
    circ4->setBrush(Qt::white);
    shapes.push_back(circ4);
    train_scene.addItem(circ4);
    QGraphicsEllipseItem* circ5 = new QGraphicsEllipseItem(200,80,30,30);
    circ5->setBrush(Qt::white);
    shapes.push_back(circ5);
    train_scene.addItem(circ5);
    QGraphicsEllipseItem* circ6 = new QGraphicsEllipseItem(243,80,30,30);
    circ6->setBrush(Qt::white);
    shapes.push_back(circ6);
    train_scene.addItem(circ6);
    QGraphicsEllipseItem* circ7 = new QGraphicsEllipseItem(279,80,30,30);
    circ7->setBrush(Qt::white);
    shapes.push_back(circ7);
    train_scene.addItem(circ7);
    QGraphicsEllipseItem* circ8 = new QGraphicsEllipseItem(315,80,30,30);
    circ8->setBrush(Qt::white);
    shapes.push_back(circ8);
    train_scene.addItem(circ8);

    //Set scene
    ui->graphicsView->setScene(&train_scene);
}


void TrainModelGUI::on_pushButton_clicked()
{
    //moveDialog.show();
}


void TrainModelGUI::on_pushButton_2_clicked()
{
    //beaconDialog.show();
}


void TrainModelGUI::on_pushButton_3_clicked()
{
    failureDialog.show();
}

void TrainModelGUI::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1)
    {
        debugDialog.show();
    }
}

void TrainModelGUI::updateGUI()
{
    ui->label->setText("Train #" + QString::number(data->getID()) +  " @ " + QString::fromStdString(data->getCurrentStation()));
    ui->label_5->setText((data->getLeftDoors()) ? "Left Doors: Open" : "Left Doors: Closed");
    ui->label_2->setText((data->getRightDoors()) ? "Right Doors: Open" : "Right Doors: Closed");
    ui->label_3->setText((data->getCabinLights()) ? "Cabin Lights: On" : "Cabin Lights: Off");
    ui->label_6->setText((data->getHeadlights()) ? "Headlights: On" : "Headlights: Off");
    QString s = "Cabin Temp: " + QString::number(data->getCabinTemp()) + " F";
    ui->label_12->setText(s);
    ui->label_4->setText("Announcement: " + QString::fromStdString(data->getAnnouncement()));
    ui->label_7->setText("Length: " + QString::number(data->getLength()) + " ft");
    ui->label_8->setText("Height: " + QString::number(data->getHeight()) + " ft");
    ui->label_11->setText("Mass: " + QString::number(data->getMass()) + " lbs");
    ui->label_9->setText("Passengers: " + QString::number(data->getPassengers()));
    ui->label_10->setText("Crew: " + QString::number(data->getCrew()));
    emit GUIChanged();
}

void TrainModelGUI::tick()
{
    //Calculate train speed
    float change = 0;
    if (data->getBrakesOn() || data->getEbrakesOn()) change = ((float) timer_interval / 1000) * - (int) data->getDecelLimit();
    else if (data->getActualPower() > 0)
    {
        change = ((float) timer_interval / 1000) * data->getActualPower() / data->getMass();
    }
    float new_speed = data->getActualSpeed() + change;
    if (new_speed < 0) new_speed = 0;
    data->setActualSpeed(new_speed);
    emit GUIChanged();
}

