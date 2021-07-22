#ifndef STATIONDETAILS_H
#define STATIONDETAILS_H

#include <QDialog>

namespace Ui {
class StationDetails;
}

class StationDetails : public QDialog
{
    Q_OBJECT

public:
    explicit StationDetails(QWidget *parent = nullptr);
    ~StationDetails();


private:
    Ui::StationDetails *ui;
};

#endif // STATIONDETAILS_H
