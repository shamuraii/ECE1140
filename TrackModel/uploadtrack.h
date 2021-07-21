#ifndef UPLOADTRACK_H
#define UPLOADTRACK_H

#include <QMainWindow>
#include "simulation.h"

namespace Ui {
class UploadTrack;
}

class UploadTrack : public QMainWindow
{
    Q_OBJECT

public:
    explicit UploadTrack(QWidget *parent = nullptr);
    ~UploadTrack();
    //Simulation *simulation;
    QString getFilename();


private slots:
    void on_loadTrack_clicked();

    void on_browseButton_clicked();

private:
    Ui::UploadTrack *ui;

};

#endif // UPLOADTRACK_H
