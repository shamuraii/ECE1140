#ifndef DEBUG_H
#define DEBUG_H

#include <QWidget>
#include "wssh.h"

namespace Ui {
class debug;
}

class debug : public QWidget
{
    Q_OBJECT

public:
    explicit debug(QWidget *parent = nullptr);
    ~debug();

private slots:
    void on_pushButton_clicked();

private:
    Ui::debug *ui;
};

#endif // DEBUG_H
