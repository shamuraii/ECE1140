#ifndef DEBUG_H
#define DEBUG_H

#include <QWidget>

namespace Ui {
class debug;
}

class debug : public QWidget
{
    Q_OBJECT

public:
    explicit debug(QWidget *parent = nullptr);
    ~debug();

private:
    Ui::debug *ui;
};

#endif // DEBUG_H
