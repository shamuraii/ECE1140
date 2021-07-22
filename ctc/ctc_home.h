#ifndef CTC_HOME_H
#define CTC_HOME_H

#include <QMainWindow>
#include <QPointer>

#include "ctc_schedule_dialog.h"
#include "ctc_upload_dialog.h"
#include "ctc_trains_dialog.h"
#include "ctc_redline_gui.h"
#include "ctc_debugger.h"
#include "trainnetwork.h"

using namespace ctc;

QT_BEGIN_NAMESPACE
namespace Ui { class CtcGUI; }
QT_END_NAMESPACE

class CtcGUI : public QMainWindow
{
    Q_OBJECT
private:
    Ui::CtcGUI *ui;
    QPointer<CtcDebugger> debug_popup;
    QPointer<CtcUploadDialog> upload_popup;
    QPointer<CtcTrainsDialog> trains_popup;
    QPointer<CtcRedLineGui> redline_popup;

    TrainNetwork *network_;

    void CreateRedLine();

public:
    CtcGUI(QWidget *parent = nullptr);
    ~CtcGUI();

    TrainNetwork *Network();

private slots:

    void on_upload_button_clicked();

    void on_view_list_button_clicked();

    void on_redline_button_clicked();

    void on_debug_button_clicked();
    void on_greenline_button_clicked();
};
#endif // CTC_HOME_H
