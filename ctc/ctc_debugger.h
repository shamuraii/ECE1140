#ifndef CTC_DEBUGGER_H
#define CTC_DEBUGGER_H

#include <QDialog>

#include "trainnetwork.h"

using namespace ctc;

namespace Ui {
class CtcDebugger;
}

class CtcDebugger : public QDialog
{
    Q_OBJECT

public:
    explicit CtcDebugger(QWidget *parent = nullptr);
    ~CtcDebugger();

public slots:
    void ReloadPage();
    void RefreshTrainData();
    void RefreshStationData();
    void SetThroughput();
signals:
    void UpdatedThroughput(int persons);

private:
    Ui::CtcDebugger *ui;
    TrainNetwork *network_;
};

#endif // CTC_DEBUGGER_H
