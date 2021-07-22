#ifndef CTC_ROUTE_DIALOG_H
#define CTC_ROUTE_DIALOG_H

#include <QDialog>

#include "trackline.h"
#include "ctrain.h"

using namespace ctc;

namespace Ui {
class CtcRouteDialog;
}

class CtcRouteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CtcRouteDialog(CTrain *train, QWidget *parent = nullptr);
    ~CtcRouteDialog();

private slots:
    void on_cancel_button_clicked();

    void on_route_text_editingFinished();

    void on_save_button_clicked();

private:
    Ui::CtcRouteDialog *ui;
    CTrain *train_;
    TrackLine *line_;
};

#endif // CTC_ROUTE_DIALOG_H
