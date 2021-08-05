#include "debug.h"
#include "ui_debug.h"

debug::debug(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::debug)
{
    ui->setupUi(this);
}

debug::~debug()
{
    delete ui;
}
