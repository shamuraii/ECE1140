#ifndef TRACKDETAILS_H
#define TRACKDETAILS_H

#include <QDialog>


namespace Ui {
class TrackDetails;
}

class TrackDetails : public QDialog
{
    Q_OBJECT

public:
    explicit TrackDetails(QWidget *parent = nullptr);
    ~TrackDetails();
    void setHeaters(bool);
    bool getHeaters();

public slots:
    void update_track(QString, QString, QString, QString, QString);

private:
    Ui::TrackDetails *ui;
};

#endif // TRACKDETAILS_H
