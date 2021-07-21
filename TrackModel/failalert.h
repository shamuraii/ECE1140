#ifndef FAILALERT_H
#define FAILALERT_H

#include <QDialog>

namespace Ui {
class FailAlert;
}

class FailAlert : public QDialog
{
    Q_OBJECT

public:
    explicit FailAlert(QWidget *parent = nullptr);
    ~FailAlert();
    void setAlert(QString);

private:
    Ui::FailAlert *ui;
};

#endif // FAILALERT_H
