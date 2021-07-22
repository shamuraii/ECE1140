#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "block_info.h"
#include <QPixmap>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pm("C:/Users/Mahya/OneDrive/Desktop/School/jr/ECE1140/track_layout.png");
    ui->track_image->setPixmap(pm);
    ui->track_image->setScaledContents(true);

    QPixmap pm1("C:/Users/Mahya/OneDrive/Desktop/School/jr/ECE1140/red_track_layout.png");
    ui->red_line->setPixmap(pm1);
    ui->red_line->setScaledContents(true);

    QPixmap pm2("C:/Users/Mahya/OneDrive/Desktop/School/jr/ECE1140/green_track_layout.png");
    ui->green_line->setPixmap(pm2);
    ui->green_line->setScaledContents(true);

    ui->authority->setText("2");
    ui->commanded_speed->setText("70");
    ui->maintenance_mode->setText("Off");
    ui->safe_authority->setText("2");
    ui->suggested_speed->setText("25");
    ui->train_location->setText("Green B");
}

void MainWindow::blockWidgetPopup()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_red_a_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'A');
}

void MainWindow::on_red_b_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'B');
}


void MainWindow::on_red_c_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'C');
}


void MainWindow::on_red_d_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'D');
}


void MainWindow::on_red_e_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'E');
}


void MainWindow::on_red_f_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'F');
}


void MainWindow::on_red_g_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'G');
}


void MainWindow::on_red_h_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'H');
}


void MainWindow::on_red_i_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'I');
}


void MainWindow::on_red_j_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'J');
}

void MainWindow::on_red_k_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'K');
}


void MainWindow::on_red_l_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'L');
}


void MainWindow::on_red_m_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("red", 'M');
}

void MainWindow::on_green_b_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("green", 'B');
}

void MainWindow::on_green_c_clicked()
{
    QWidget *blockWidget = new block_info;
    blockWidget->show();
    block_info::fillTable("green", 'C');
}

void MainWindow::on_pushButton_clicked()
{
    int arg1 = ui->comboBox->currentIndex();

    if(arg1 == 0) {
        ui->authority->setText("2");
        ui->commanded_speed->setText("70");
        ui->maintenance_mode->setText("Off");
        ui->safe_authority->setText("2");
        ui->suggested_speed->setText("25");
        ui->train_location->setText("Green B");
    } else if (arg1 == 1) {
        ui->authority->setText("4");
        ui->commanded_speed->setText("65");
        ui->maintenance_mode->setText("Off");
        ui->safe_authority->setText("4");
        ui->suggested_speed->setText("65");
        ui->train_location->setText("Red J");
    } else {
        ui->authority->setText("3");
        ui->commanded_speed->setText("65");
        ui->maintenance_mode->setText("Off");
        ui->safe_authority->setText("3");
        ui->suggested_speed->setText("45");
        ui->train_location->setText("Green G");
    }
}
