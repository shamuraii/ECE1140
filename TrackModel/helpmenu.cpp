#include "helpmenu.h"
#include "ui_helpmenu.h"

HelpMenu::HelpMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpMenu)
{
    ui->setupUi(this);
}

HelpMenu::~HelpMenu()
{
    delete ui;
}


