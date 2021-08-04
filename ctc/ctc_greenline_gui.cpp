#include <QMessageBox>

#include "ctc_home.h"
#include "ctc_greenline_gui.h"
#include "ui_ctc_greenline_gui.h"
#include "trackline.h"
#include "block.h"
#include "station.h"
#include "switch.h"
#include "trainnetwork.h"
#include "ctc_constants.h"

CtcGreenLineGui::CtcGreenLineGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcGreenLineGui)
{
    ui->setupUi(this);

    TrainNetwork *network = qobject_cast<CtcGUI*>(this->parent())->Network();
    connect(this, &CtcGreenLineGui::NeedUpdate, this, &CtcGreenLineGui::UpdateDisplay);
    connect(network, &TrainNetwork::NetworkUpdated, this, &CtcGreenLineGui::UpdateDisplay);
    connect(GetGreenLine(), &TrackLine::ThroughputUpdated, this, &CtcGreenLineGui::UpdateThroughput);

    QList<QPushButton*> buttons = ui->main_frame->findChildren<QPushButton*>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton* button : buttons) {
        QString button_name = button->objectName();
        if (button_name.contains("yard", Qt::CaseInsensitive)) {
            // Yard button has no effects
            continue;
        } else if (button_name.startsWith("sw")) {
            // Add the switch handler
            connect(button, &QPushButton::clicked, this, &CtcGreenLineGui::switch_clicked);
        } else {
            // Add the block closed/opened handler
            connect(button, &QPushButton::clicked, this, &CtcGreenLineGui::block_clicked);
        }
    }
    UpdateDisplay();
}

CtcGreenLineGui::~CtcGreenLineGui()
{
    delete ui;
}

void CtcGreenLineGui::on_schedule_button_clicked()
{
    if (!schedule_popup)
        schedule_popup = new CtcScheduleDialog(GetGreenLine(), this);

    schedule_popup->show();
    schedule_popup->RefreshDisplay();
}

void CtcGreenLineGui::on_back_button_clicked()
{
    this->close();
}

void CtcGreenLineGui::block_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int block_num = button->text().toInt();
        Block *b = GetGreenLine()->GetBlock(block_num);
        b->SetClosed(!b->IsClosed(), kRedBool);
    } else {
        QMessageBox::warning(this, "Error", "Invalid block_clicked signal sent.");
    }
    emit NeedUpdate();
}

void CtcGreenLineGui::switch_clicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int sw_num = button->text().toInt();
        Switch *sw = GetGreenLine()->GetSwitch(sw_num);
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

void CtcGreenLineGui::UpdateDisplay() {
    QList<QPushButton*> buttons = ui->main_frame->findChildren<QPushButton*>(QString(), Qt::FindDirectChildrenOnly);
    for (QPushButton* button : buttons) {
        QString button_name = button->objectName();
        if (button_name.contains("yard", Qt::CaseInsensitive)) {
            // Yard button has no effects
            continue;
        } else if (button_name.startsWith("sw")) {
            // Update SW Display
            int sw_num = button->text().toInt();
            Switch *sw = GetGreenLine()->GetSwitch(sw_num);
            if (sw->PointingTo() == sw->LowerBlock()) {
                button->setStyleSheet(ui->legend_switch0->styleSheet());
            } else {
                button->setStyleSheet(ui->legend_switch1->styleSheet());
            }
            button->setText(QString::number(sw->PointingTo()));
        } else {
            // Update Block Display
            int block_num = button->text().toInt();
            Block *b = GetGreenLine()->GetBlock(block_num);

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

void CtcGreenLineGui::UpdateThroughput(int persons) {
    ui->throughput_text->setText(QString::number(persons) + " persons/hour");
}

TrackLine *CtcGreenLineGui::GetGreenLine() {
    TrainNetwork *network = qobject_cast<CtcGUI*>(this->parent())->Network();
    return network->GetTrackLine(kGreenlineName);
}

