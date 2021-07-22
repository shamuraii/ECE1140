#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QDialog>


namespace Ui {
class Debugger;
}

class Debugger : public QDialog
{
    Q_OBJECT

public:
    explicit Debugger(QWidget *parent = nullptr);
    ~Debugger();
    void setFailure(bool);

public slots:
    void updateFail(QString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Debugger *ui;
};

#endif // DEBUGGER_H
