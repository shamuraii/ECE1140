#ifndef WSMAINWINDOW_H
#define WSMAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "track_control.h"
#include "wssh.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WSMainWindow; }
QT_END_NAMESPACE

class WSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    WSMainWindow(QWidget *parent = nullptr);
    //void blockWidgetPopup();
    ~WSMainWindow();
    void fillTable(string line);

private slots:
    void on_debug_button_clicked();
    void on_uploadPLC_clicked();
    void UpdateGUI();

private:
    vector<track_control::Block> block_vector;
    string line;
    Ui::WSMainWindow *ui;
};
#endif // WSMAINWINDOW_H
