#ifndef CTC_UPLOAD_DIALOG_H
#define CTC_UPLOAD_DIALOG_H

#include <QDialog>

#include "trainnetwork.h"

using namespace ctc;

namespace Ui {
class CtcUploadDialog;
}

class CtcUploadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CtcUploadDialog(QWidget *parent = nullptr);
    ~CtcUploadDialog();

private slots:
    void on_select_file_button_clicked();

    void on_cancel_button_clicked();

    void on_load_button_clicked();

private:
    Ui::CtcUploadDialog *ui;
    TrainNetwork *network_;
    QString file_name;
};

#endif // CTC_UPLOAD_DIALOG_H
