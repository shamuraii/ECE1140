#include <QFileDialog>
#include <QMessageBox>

#include "uploadtrack.h"
#include "ui_uploadtrack.h"

UploadTrack::UploadTrack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UploadTrack)
{
    ui->setupUi(this);

    //simulation = new Simulation(this);
}

UploadTrack::~UploadTrack()
{
    delete ui;
}


void UploadTrack::on_browseButton_clicked()
{
    QString file_name;
    file_name = QFileDialog::getOpenFileName(this, "Select File",
                                                         "", "XLSX Files (*.xlsx)");
    if (file_name.isNull()) {
        QMessageBox::warning(this, "Error", "No file was selected.");
        ui->file_label->setText("None");
    } else if (!file_name.endsWith(".xlsx")) {
        QMessageBox::warning(this, "Error", "Please select an excel file");
        ui->file_label->setText("None");
        file_name.clear();
    } else {
        ui->file_label->setText(file_name);
    }
}


void UploadTrack::on_loadTrack_clicked()
{
    //simulation->show();
}

QString UploadTrack::getFilename(){
    return ui->file_label->text();
}

