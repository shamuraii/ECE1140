#include "wsmainwindow.h"
#include "ui_wsmainwindow.h"
#include "block_info.h"
#include "debug.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPointer>
#include <QFont>
#include <string>
#include <QObject>

WSMainWindow::WSMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WSMainWindow)
{
    ui->setupUi(this);
    QObject::connect(&wssh::Get(), &wssh::UpdateGUI, this, &WSMainWindow::UpdateGUI);
    track_control::initialize();
    block_vector = track_control::getBlockVector("red");

    QHeaderView *ctc_header = ui->ctc_info->horizontalHeader();
    ctc_header->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *track_header = ui->trackmodel_info->horizontalHeader();
    track_header->setSectionResizeMode(QHeaderView::Stretch);
    ui->ctc_info->setColumnCount(1);
    ui->ctc_info->setRowCount(2);
    ui->trackmodel_info->setColumnCount(1);
    ui->trackmodel_info->setRowCount(2);
    QStringList ctc_labels;
    ctc_labels << "Suggested Speed" << "Suggested Authority";
    QStringList model_labels;
    model_labels << "Commanded Speed" << "Commanded Authority";
    ui->ctc_info->setVerticalHeaderLabels(ctc_labels);
    ui->trackmodel_info->setVerticalHeaderLabels(model_labels);
    fillTable("red");
}

WSMainWindow::~WSMainWindow()
{
    delete ui;
}

void WSMainWindow::fillTable(string line) {
    //CTC: authority, suggested speed (based on where the train is)
    //train model: commanded speed, authority
    int occupied_block;
    if(line == "red") {
        for(int i=0; i<76; i++) {
            if(track_control::getBlockOccupancy(i, false) == true)
                occupied_block = i;
        }
    } else {
        for(int i=0; i<150; i++) {
            if(track_control::getBlockOccupancy(i, true) == true)
                occupied_block = i;
        }
    }

    QString sugg_speed = QString::number(block_vector[occupied_block-1].speed);
    QString sugg_auth = QString::number(block_vector[occupied_block-1].authority);
    QString commanded_speed = QString::number(block_vector[occupied_block-1].speed);
    QString commanded_auth = QString::number(block_vector[occupied_block-1].authority);

    ui->ctc_info->setItem(1, 0, new QTableWidgetItem(sugg_speed));
    ui->ctc_info->setItem(1, 1, new QTableWidgetItem(sugg_auth));
    ui->trackmodel_info->setItem(1, 0, new QTableWidgetItem(commanded_speed));
    ui->trackmodel_info->setItem(1, 1, new QTableWidgetItem(commanded_auth));

    //ui->ctc_info = new QTableWidget(2, 2);
    //ui->trackmodel_info = new QTableWidget(2, 2);


//    QTableWidgetItem *sugg_auth = new QTableWidgetItem();
//    QTableWidgetItem *sugg_speed = new QTableWidgetItem();
//    QTableWidgetItem *commanded_auth = new QTableWidgetItem();
//    QTableWidgetItem *commanded_speed = new QTableWidgetItem();

//    QTableWidgetItem *sugg_auth_name = new QTableWidgetItem();
//    QTableWidgetItem *sugg_speed_name = new QTableWidgetItem();
//    QTableWidgetItem *commanded_auth_name = new QTableWidgetItem();
//    QTableWidgetItem *commanded_speed_name = new QTableWidgetItem();

//    qDebug() << occupied_block;
//    qDebug() << block_vector[occupied_block].speed;


//    sugg_speed_name->setText("Suggested Speed");
//    sugg_auth_name->setText("Suggested Authority");
//    commanded_speed_name->setText("Commanded Speed");
//    commanded_auth_name->setText("Commanded Authority");

//    ui->ctc_info->setItem(1, 1, sugg_auth_name);
//    ui->ctc_info->setItem(2, 1, sugg_speed_name);
//    ui->ctc_info->setItem(1, 2, sugg_auth);
//    ui->ctc_info->setItem(2, 2, sugg_speed);

//    ui->trackmodel_info->setItem(1, 1, commanded_auth_name);
//    ui->trackmodel_info->setItem(2, 1, commanded_speed_name);
//    ui->trackmodel_info->setItem(1, 2, commanded_auth);
//    ui->trackmodel_info->setItem(2, 2, commanded_speed);

    QString temp = "";
    if(track_control::getBlockMaintenanceMode(occupied_block, "red"))
        temp = "ON";
    else
        temp = "Off";
    ui->maintmode->setText(temp);

    ui->plc_file->setText(QString::fromStdString(track_control::getPLCFile()));
}

void WSMainWindow::on_debug_button_clicked()
{
    debug *debugWidget = new debug;
    debugWidget->show();
}


void WSMainWindow::on_uploadPLC_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Upload PLC file", "C://");
    QMessageBox::information(this, "Success", "PLC file successfully uploaded.");
}

void WSMainWindow::UpdateGUI() {
    fillTable("red");
}



