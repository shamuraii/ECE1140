#include "block_info.h"
#include "ui_block_info.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QPointer>
#include <QFont>

std::string line;
char section;
vector<track_control::Block> block_vector;
vector<track_control::Block> section_blocks;

block_info::block_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::block_info)
{
    ui->setupUi(this);
    QString sect = QString(section);
    QString t = "Section";
    t.append(section);
    ui->title->setText(t);
}

block_info::~block_info()
{
    delete ui;
}

void block_info::ShowComponentInfo() {
    int size = section_blocks.size();

    ui->switch_frame->setVisible(false);
    ui->rx_frame->setVisible(false);
    ui->sw_toggle->setVisible(false);
    ui->rx_toggle->setVisible(false);

    for(int i=0; i<size; i++) {
        //check switch presence
        if(section_blocks[i].sw.presence == true) {
            ui->switch_frame->setVisible(true);
            if(section_blocks[i].maintenance_mode == 1)
                ui->sw_toggle->setVisible(true);
        }


        //check rx presence
        if(section_blocks[i].rx.presence == true) {
            ui->rx_frame->setVisible(true);
            if(section_blocks[i].maintenance_mode == 1)
                ui->rx_toggle->setVisible(true);
        }
    }
}

void block_info::on_PLCUpload_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Upload PLC file", "C://");
    QMessageBox::information(this, "Success", "PLC file successfully uploaded.");
}

void block_info::fillTable(std::string l, char sect)
{
    line = l;
    section = sect;

    QTableWidget *table = ui->tableWidget;
    QStringList headers = {"Block No.", "Track State", "Train Presence"};

    table->setRowCount(0);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSortingEnabled(true);

    block_vector = track_control::getBlockVector(line);
    int vector_size = block_vector.size();
    for(int i=0; i<vector_size; i++) {
        if(block_vector[i].section == section) {
            section_blocks.push_back(block_vector[i]);

            table->insertRow(table->rowCount());
            table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(QString::number(block_vector[i].id)));

            if(block_vector[i].fail == 0)
                table->setItem(table->rowCount()-1, 0, new QTableWidgetItem("OK"));
            else
                table->setItem(table->rowCount()-1, 0, new QTableWidgetItem("Failure"));

            if(block_vector[i].occupancy == 0)
                table->setItem(table->rowCount()-1, 0, new QTableWidgetItem("-"));
            else
                table->setItem(table->rowCount()-1, 0, new QTableWidgetItem("Occupied"));
        }
    }
    ShowComponentInfo();
}

void block_info::UpdateUI() {
    fillTable(line, section);
}

void block_info::on_togglemaintenance_clicked()
{
    int size = section_blocks.size();
    bool maint;
    for(int i = 0; i<size; i++) {
        if(line == "red") {
            maint = track_control::getBlockMaintenanceMode(section_blocks[i].id, "red");
            track_control::setBlockMaintenanceMode(section_blocks[i].id, !maint, "red");
        } else {
            maint = track_control::getBlockMaintenanceMode(section_blocks[i].id, "green");
            track_control::setBlockMaintenanceMode(section_blocks[i].id, !maint, "green");
        }
    }
}

