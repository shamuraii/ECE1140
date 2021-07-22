#include "wsmainwindow.h"
#include "ui_wsmainwindow.h"
#include "block_info.h"
#include "track_control.h"
#include <QPixmap>
#include <string>

WSMainWindow::WSMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WSMainWindow)
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

    vector<track_control::Block> block_vector = track_control::getBlockVector("red");
    int block_num;
    bool auth;
    int comm_speed;
    bool maint_mode;
    bool safe_auth;
    int sug_speed;
    QString location;

    for (int i=0; i<76; i++) {
        if(block_vector[i].occupancy == 1) {
            block_num = track_control::getBlockID(i);
            auth = track_control::getBlockAuthority(block_num);
            comm_speed = track_control::getBlockSpeed(block_num);
            maint_mode = track_control::getBlockMaintenanceMode(block_num, "red");
            safe_auth = track_control::getBlockAuthority(block_num);
            sug_speed = track_control::getBlockSpeed(block_num);
            location = QString::fromStdString("Red " + to_string(block_num));
        }
    }

    ui->authority->setText(QString::number(auth));
    ui->commanded_speed->setText(QString::number(comm_speed));
    ui->maintenance_mode->setText(QString::number(maint_mode));
    ui->safe_authority->setText(QString::number(safe_auth));
    ui->suggested_speed->setText(QString::number(sug_speed));
    ui->train_location->setText(location);
}

void WSMainWindow::blockWidgetPopup()
{

}

WSMainWindow::~WSMainWindow()
{
    delete ui;
}

void WSMainWindow::on_red_a_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'A');
}

void WSMainWindow::on_red_b_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'B');
}


void WSMainWindow::on_red_c_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'C');
}


void WSMainWindow::on_red_d_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'D');
}


void WSMainWindow::on_red_e_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'E');
}


void WSMainWindow::on_red_f_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'F');
}


void WSMainWindow::on_red_g_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'G');
}


void WSMainWindow::on_red_h_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'H');
}


void WSMainWindow::on_red_i_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'I');
}


void WSMainWindow::on_red_j_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'J');
}

void WSMainWindow::on_red_k_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'K');
}


void WSMainWindow::on_red_l_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'L');
}


void WSMainWindow::on_red_m_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("red", 'M');
}

void WSMainWindow::on_green_b_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("green", 'B');
}

void WSMainWindow::on_green_c_clicked()
{
    block_info *blockWidget = new block_info;
    blockWidget->show();
    blockWidget->fillTable("green", 'C');
}

void WSMainWindow::on_pushButton_clicked()
{
    int arg1 = ui->comboBox->currentIndex();

}
