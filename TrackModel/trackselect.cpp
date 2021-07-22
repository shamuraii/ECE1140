#include "trackselect.h"
#include "ui_trackselect.h"

#include <QTableWidget>

TrackSelect::TrackSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrackSelect)
{
    ui->setupUi(this);
    FillTable();

    simulation = new Simulation(this);
}

TrackSelect::~TrackSelect()
{
    delete ui;
}

void TrackSelect::on_pushButton_2_clicked()
{
    simulation->show();
    simulation->emitTrackInfo();
}
void TrackSelect::FillTable() {
    QTableWidget *table = ui->track_table;

    table->setRowCount(11);
    table->setColumnCount(2);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSortingEnabled(true);
    ui->track_table->verticalHeader()->setVisible(false);
    ui->track_table->horizontalHeader()->setVisible(false);
}

