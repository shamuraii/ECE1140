#ifndef FAILUREMODESELECTOR_H
#define FAILUREMODESELECTOR_H

#include <QDialog>
#include "failalert.h"
#include "debugger.h"

namespace Ui {
class FailureModeSelector;
}

class FailureModeSelector : public QDialog
{
    Q_OBJECT

public:
    explicit FailureModeSelector(QWidget *parent = nullptr);
    ~FailureModeSelector();

signals:
    void new_failure(QString block);


private slots:
    void on_apply_clicked();

private:
    Ui::FailureModeSelector *ui;
    FailAlert *fail_alert;
    Debugger *debugger;

};

#endif // FAILUREMODESELECTOR_H
