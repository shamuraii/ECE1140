#include "debugger.h"
#include "ui_debugger.h"

bool fail_code;

Debugger::Debugger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Debugger)
{
    ui->setupUi(this);

}

Debugger::~Debugger()
{
    delete ui;
}

void Debugger::setFailure(bool s){
    fail_code = s;

    QLabel *label = ui->fail_block_num;
    if(fail_code){
        label->setText("1");
    }else{
        label->setText("0");
    }
}

void Debugger::on_pushButton_clicked()
{
    QLabel *label = ui->location;
    label->setText("Oakland Station");

}

void Debugger::updateFail(QString block) {
    ui->fail_block_num->setText(block);
}
