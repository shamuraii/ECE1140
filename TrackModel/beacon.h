#ifndef BEACON_H
#define BEACON_H

#include <QDialog>

namespace Ui {
class Beacon;
}

class Beacon : public QDialog
{
    Q_OBJECT

public:
    explicit Beacon(QWidget *parent = nullptr);
    ~Beacon();

private:
    Ui::Beacon *ui;
};

#endif // BEACON_H
