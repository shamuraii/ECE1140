#ifndef CTC_UPLOAD_DIALOG_H
#define CTC_UPLOAD_DIALOG_H

#include <QDialog>

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

private:
    Ui::CtcUploadDialog *ui;
    QString file_name;
};

#endif // CTC_UPLOAD_DIALOG_H
