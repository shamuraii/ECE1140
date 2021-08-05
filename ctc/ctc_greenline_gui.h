#ifndef CTC_GREENLINE_GUI_H
#define CTC_GREENLINE_GUI_H

#include <QDialog>
#include <QPointer>

#include "ctc_schedule_dialog.h"
#include "trackline.h"

using namespace ctc;

namespace Ui {
class CtcGreenLineGui;
}

class CtcGreenLineGui : public QDialog
{
    Q_OBJECT

public:
    explicit CtcGreenLineGui(QWidget *parent = nullptr);
    ~CtcGreenLineGui();
public slots:
    void UpdateThroughput(int persons);

    void UpdateDisplay();

private slots:
    void on_schedule_button_clicked();

    void on_back_button_clicked();

    void block_clicked();

    void switch_clicked();

private:
    Ui::CtcGreenLineGui *ui;
    QPointer<CtcScheduleDialog> schedule_popup;

    TrackLine *GetGreenLine();

signals:
    void NeedUpdate();
};

#endif // CTC_GREENLINE_GUI_H
