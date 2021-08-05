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

void debug::on_pushButton_clicked()
{
    bool ok;
    int block_num = ui->lineEdit->text().toInt(&ok);

    if(block_num>=0 && block_num<=150 && ok) {
        wssh::Get().SetTrainPresence(block_num, 1);
    }

}

