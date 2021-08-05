#ifndef WSMAINWINDOW_H
#define WSMAINWINDOW_H

#include <QMainWindow>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class WSMainWindow; }
QT_END_NAMESPACE

class WSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    WSMainWindow(QWidget *parent = nullptr);
    void blockWidgetPopup();
    ~WSMainWindow();

private slots:
    void on_pushButton_clicked();
    void on_red_a_clicked();
    void on_red_b_clicked();
    void on_red_c_clicked();
    void on_red_d_clicked();
    void on_red_e_clicked();
    void on_red_f_clicked();
    void on_red_g_clicked();
    void on_red_h_clicked();
    void on_red_i_clicked();
    void on_red_j_clicked();
    void on_red_k_clicked();
    void on_red_l_clicked();
    void on_red_m_clicked();

    void on_green_b_clicked();
    void on_green_c_clicked();   

private:
    Ui::WSMainWindow *ui;
};
#endif // WSMAINWINDOW_H
