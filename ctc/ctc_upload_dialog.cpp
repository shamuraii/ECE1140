#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "ctc_upload_dialog.h"
#include "ui_ctc_upload_dialog.h"
#include "ctc_home.h"
#include "trainnetwork.h"
#include "trackline.h"
#include "ctrain.h"
#include "station.h"

CtcUploadDialog::CtcUploadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcUploadDialog)
{
    ui->setupUi(this);
    network_ = qobject_cast<CtcGUI*>(this->parent())->Network();
}

CtcUploadDialog::~CtcUploadDialog()
{
    delete ui;
}

void CtcUploadDialog::on_select_file_button_clicked()
{
    file_name = QFileDialog::getOpenFileName(this, "Select File",
                                                     "", "csv Files (*.csv)");
    if (file_name.isNull()) {
        QMessageBox::warning(this, "Error", "No file was selected.");
        ui->file_label->setText("None");
    } else if (!file_name.endsWith(".csv")) {
        QMessageBox::warning(this, "Error", "Please select a valid csv file");
        ui->file_label->setText("None");
        file_name.clear();
    } else {
        ui->file_label->setText(file_name);
    }
}


void CtcUploadDialog::on_cancel_button_clicked()
{
    this->close();
}


void CtcUploadDialog::on_load_button_clicked()
{
    if (QFile::exists(ui->file_label->text())) {
        std::ifstream fin;
        std::string line;
        std::string val;
        std::stringstream ss;

        // Open the Block File
        fin.open(ui->file_label->text().toStdString());
        while (std::getline(fin, line)) {
            ss = std::stringstream(line);

            // Get Destination name
            std::getline(ss, val, ',');
            QString dest_name = QString::fromStdString(val);
            // Get Departure Time
            std::getline(ss, val, ',');
            QTime depart = QTime::fromString(QString::fromStdString(val), "HHmm");
            // Get Track Line
            std::getline(ss, val, ',');
            QString line_name = QString::fromStdString(val);

            // Find destination station
            TrackLine *l = network_->GetTrackLine(line_name);
            Station *d = l->GetStation(dest_name);

            // Add train to network
            network_->AddTrain(new CTrain(d, depart, l));
        }
        fin.close();
        fin.clear();

        QMessageBox::information(this, "Success", "Train schedule has been loaded.");
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "Provided file does not exist.");
    }
}

