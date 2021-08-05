#include <QMessageBox>

#include "ctc_home.h"
#include "ctc_redline_gui.h"
#include "ui_ctc_redline_gui.h"
#include "trackline.h"
#include "block.h"
#include "station.h"
#include "switch.h"
#include "trainnetwork.h"
#include "ctc_constants.h"

CtcRedLineGui::CtcRedLineGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcRedLineGui)
{
    ui->setupUi(this);

    TrainNetwork *network = qobject_cast<CtcGUI*>(this->parent())->Network();
    connect(this, &CtcRedLineGui::NeedUpdate, this, &CtcRedLineGui::UpdateDisplay);
    connect(network, &TrainNetwork::NetworkUpdated, this, &CtcRedLineGui::UpdateDisplay);
    connect(GetRedLine(), &TrackLine::ThroughputUpdated, this, &CtcRedLineGui::UpdateThroughput);

    QList<QPushButton*> buttons = ui->main_frame->findChildren<QPushButton*>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton* button : buttons) {
        QString button_name = button->objectName();
        if (button_name.contains("yard", Qt::CaseInsensitive)) {
            // Yard button has no effects
            continue;
        } else if (button_name.startsWith("sw")) {
            // Add the switch handler
            connect(button, &QPushButton::clicked, this, &CtcRedLineGui::switch_clicked);
        } else {
            // Add the block closed/opened handler
            connect(button, &QPushButton::clicked, this, &CtcRedLineGui::block_clicked);
        }
    }
    UpdateDisplay();
}

CtcRedLineGui::~CtcRedLineGui()
{
    delete ui;
}

void CtcRedLineGui::on_schedule_button_clicked()
{
    if (!schedule_popup)
        schedule_popup = new CtcScheduleDialog(GetRedLine(), this);

    schedule_popup->show();
    schedule_popup->RefreshDisplay();
}

void CtcRedLineGui::on_back_button_clicked()
{
    this->close();
}

void CtcRedLineGui::block_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int block_num = button->text().toInt();
        Block *b = GetRedLine()->GetBlock(block_num);
        b->SetClosed(!b->IsClosed(), kRedBool);
    } else {
        QMessageBox::warning(this, "Error", "Invalid block_clicked signal sent.");
    }
    emit NeedUpdate();
}

void CtcRedLineGui::switch_clicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int sw_num = button->objectName().remove(0,2).toInt();
        Switch *sw = GetRedLine()->GetSwitch(sw_num);
        if (sw->InMaintenance()) {
            int result = QMessageBox::question(this, "Maintenance Mode", "Currently, switch in maintenance mode. Would you like to disable maintenance mode?",
                                 QMessageBox::No | QMessageBox::Yes);
            if (result == QMessageBox::Yes) {
                sw->SetMaintenance(false, kRedBool);
                return;
            }
        } else {
            int result = QMessageBox::question(this, "Maintenance Mode", "Currently, switch is NOT in maintenance mode. Would you like to enable maintenance mode?",
                                 QMessageBox::No | QMessageBox::Yes);
            if (result == QMessageBox::Yes) {
                sw->SetMaintenance(true, kRedBool);
            } else {
                return;
            }
        }

        int result = QMessageBox::question(this, "Flip Switch", "Flip Switch Position?",
                                            QMessageBox::No | QMessageBox::Yes);
        if (result == QMessageBox::Yes) {
            if (sw->PointingTo() == sw->LowerBlock()) {
                sw->UpdateState(sw->UpperBlock(), kRedBool);
            } else {
                sw->UpdateState(sw->LowerBlock(), kRedBool);
            }
        }
    } else {
        QMessageBox::warning(this, "Error", "Invalid block_clicked signal sent.");
    }
    emit NeedUpdate();
}

void CtcRedLineGui::UpdateDisplay() {
    QList<QPushButton*> buttons = ui->main_frame->findChildren<QPushButton*>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton* button : buttons) {
        QString button_name = button->objectName();
        if (button_name.contains("yard", Qt::CaseInsensitive)) {
            // Yard button has no effects
            continue;
        } else if (button_name.startsWith("sw")) {
            // Update SW Display
            int sw_num = button_name.remove(0,2).toInt();
            Switch *sw = GetRedLine()->GetSwitch(sw_num);
            if (sw->PointingTo() == sw->LowerBlock()) {
                button->setStyleSheet(ui->legend_switch0->styleSheet());
            } else {
                button->setStyleSheet(ui->legend_switch1->styleSheet());
            }
            button->setText(QString::number(sw->PointingTo()));
        } else {
            // Update Block Display
            int block_num = button->text().toInt();
            Block *b = GetRedLine()->GetBlock(block_num);

            if (b->IsOccupied()) {
                // If occupied, use occupied colors regardless of status
                button->setStyleSheet(ui->legend_occupied->styleSheet());
            } else if (b->IsClosed()) {
                button->setStyleSheet(ui->legend_closed->styleSheet());
            } else {
                button->setStyleSheet(ui->legend_free->styleSheet());
            }
        }
    }
}

void CtcRedLineGui::UpdateThroughput(int persons) {
    ui->throughput_text->setText(QString::number(persons) + " persons/hour");
}

TrackLine *CtcRedLineGui::GetRedLine() {
    TrainNetwork *network = qobject_cast<CtcGUI*>(this->parent())->Network();
    return network->GetTrackLine(kRedlineName);
}

