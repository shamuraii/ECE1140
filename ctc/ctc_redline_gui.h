#ifndef CTC_REDLINE_GUI_H
#define CTC_REDLINE_GUI_H

#include <QDialog>
#include <QPointer>

#include "ctc_schedule_dialog.h"
#include "trackline.h"

using namespace ctc;

namespace Ui {
class CtcRedLineGui;
}

class CtcRedLineGui : public QDialog
{
    Q_OBJECT

public:
    explicit CtcRedLineGui(QWidget *parent = nullptr);
    ~CtcRedLineGui();
public slots:
    void UpdateThroughput(int persons);

    void UpdateDisplay();

private slots:
    void on_schedule_button_clicked();

    void on_back_button_clicked();

    void block_clicked();

    void switch_clicked();

private:
    Ui::CtcRedLineGui *ui;
    QPointer<CtcScheduleDialog> schedule_popup;

    TrackLine *GetRedLine();

signals:
    void NeedUpdate();
};

#endif // CTC_REDLINE_GUI_H
