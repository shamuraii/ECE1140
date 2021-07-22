#ifndef CTC_SCHEDULE_DIALOG_H
#define CTC_SCHEDULE_DIALOG_H

#include <QDialog>

#include "trackline.h"

using namespace ctc;

namespace Ui {
class CtcScheduleDialog;
}

class CtcScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CtcScheduleDialog(TrackLine *line, QWidget *parent = nullptr);
    ~CtcScheduleDialog();
public slots:
    void RefreshDisplay();

private slots:
    void on_cancel_button_clicked();

    void on_schedule_button_clicked();

private:
    Ui::CtcScheduleDialog *ui;
    TrackLine *line_;
};

#endif // CTC_SCHEDULE_DIALOG_H
