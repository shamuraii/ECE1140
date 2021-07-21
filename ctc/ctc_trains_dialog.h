#ifndef CTC_TRAINS_DIALOG_H
#define CTC_TRAINS_DIALOG_H

#include <QDialog>
#include <QPointer>

#include "ctc_route_dialog.h"

namespace Ui {
class CtcTrainsDialog;
}

class CtcTrainsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CtcTrainsDialog(QWidget *parent = nullptr);
    ~CtcTrainsDialog();
    void FillTable();

private slots:
    void on_refresh_button_clicked();

    void on_back_button_clicked();

    void on_route_button_clicked();

private:
    Ui::CtcTrainsDialog *ui;
    QPointer<CtcRouteDialog> route_popup_;
};

#endif // CTC_TRAINS_DIALOG_H
