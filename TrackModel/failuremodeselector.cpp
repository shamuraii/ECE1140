#include "failuremodeselector.h"
#include "ui_failuremodeselector.h"
#include <QLabel>
#include <QCheckBox>

FailureModeSelector::FailureModeSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FailureModeSelector)
{
    ui->setupUi(this);
}

FailureModeSelector::~FailureModeSelector()
{
    delete ui;
}

void FailureModeSelector::on_apply_clicked()
{

    QCheckBox *box1 = ui->broken_rail;
    QCheckBox *box2 = ui->circuit_fail;
    QCheckBox *box3 = ui->power_fail;

    fail_alert = new FailAlert(this);
    fail_alert->show();


    if(box1->checkState()== Qt::Checked){
        fail_alert->setAlert("Block 1 Broken! Continue?");
        emit new_failure(ui->brokenRailBox->currentText());
    }else if(box2->checkState()== Qt::Checked){
        fail_alert->setAlert("Block 1 Circuit Failure! Continue?");
        emit new_failure(ui->trackFailBox->currentText());
    }else if(box3->checkState()== Qt::Checked){
        fail_alert->setAlert("Power Failure! Continue?");
    }else{

    }

}


