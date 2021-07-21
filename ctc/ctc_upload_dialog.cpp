#include <QFileDialog>
#include <QMessageBox>

#include "ctc_upload_dialog.h"
#include "ui_ctc_upload_dialog.h"

CtcUploadDialog::CtcUploadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcUploadDialog)
{
    ui->setupUi(this);
}

CtcUploadDialog::~CtcUploadDialog()
{
    delete ui;
}

void CtcUploadDialog::on_select_file_button_clicked()
{
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

