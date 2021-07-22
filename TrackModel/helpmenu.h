#ifndef HELPMENU_H
#define HELPMENU_H

#include <QMainWindow>


namespace Ui {
class HelpMenu;
}

class HelpMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit HelpMenu(QWidget *parent = nullptr);
    ~HelpMenu();

private slots:


private:
    Ui::HelpMenu *ui;
};

#endif // HELPMENU_H
