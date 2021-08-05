#include <QString>

#include "ctc_debugger.h"
#include "ui_ctc_debugger.h"
#include "ctrain.h"
#include "ctc_home.h"
#include "ctc_constants.h"

CtcDebugger::CtcDebugger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CtcDebugger)
{
    ui->setupUi(this);
    network_ = qobject_cast<CtcGUI*>(this->parent())->Network();

    connect(ui->train_box, &QComboBox::currentIndexChanged, this, &CtcDebugger::RefreshTrainData);
    connect(ui->station_box, &QComboBox::currentIndexChanged, this, &CtcDebugger::RefreshStationData);
    connect(network_, &TrainNetwork::NetworkUpdated, this, &CtcDebugger::RefreshTrainData);
    connect(network_, &TrainNetwork::TrainAdded, this, &CtcDebugger::ReloadPage);
}

CtcDebugger::~CtcDebugger()
{
    delete ui;
}

void CtcDebugger::ReloadPage() {
    ui->train_box->clear();
    for (CTrain *t : network_->GetTrains()) {
        ui->train_box->addItem(QStringLiteral("Train %1").arg(t->GetNum()));
    }
    ui->station_box->clear();
    for (Station *s : network_->GetTrackLine(kRedlineName)->GetStations()) {
        ui->station_box->addItem(s->GetName());
    }

    RefreshTrainData();
    RefreshStationData();
}

void CtcDebugger::RefreshTrainData() {
    ui->line_text->clear();
    ui->route_text->clear();
    ui->stops_text->clear();
    ui->depart_text->clear();
    ui->dest_text->clear();
    ui->loc_text->clear();
    ui->outs_text->clear();
    ui->advance_button->disconnect();

    QComboBox *box = ui->train_box;
    if (box && !box->currentText().isEmpty()) {
        int t_num = box->currentText().remove(0, 6).toInt();
        CTrain *t = network_->GetTrain(t_num);
        if (t) {
            connect(ui->advance_button, &QPushButton::clicked, t, &CTrain::DebugAdvanceTrain);
            ui->line_text->setText(t->GetLine()->GetName());
            ui->route_text->setText(t->GetRouteString());
            ui->stops_text->setText(t->GetStopsString());
            ui->depart_text->setText(t->GetDepartTime().toString("hh:mm"));
            ui->dest_text->setText(t->GetDestination()->GetName());
            ui->loc_text->setText(QString::number(t->GetLocation()->GetNum()));
            QString out_str = "Suggested Speed: " + QString::number(t->GetSugSpeed(true));
            out_str.append(" mph");
            out_str.append("\n");
            out_str.append("Suggested Authority: " + QString::number(t->GetSugAuth()));
            ui->outs_text->setText(out_str);
        }
    }
}

void CtcDebugger::RefreshStationData() {
    ui->station_loc_text->clear();
    ui->throughput_text->clear();
    ui->throughput_button->disconnect();

    QComboBox *box = ui->station_box;
    if (box && !box->currentText().isEmpty()) {
        QString station_name = box->currentText();
        Station *s = network_->GetTrackLine(kRedlineName)->GetStation(station_name);
        if (s) {
            connect(ui->throughput_button, &QPushButton::clicked, this, &CtcDebugger::SetThroughput);
            ui->station_loc_text->setText(QString::number(s->GetBlockNum()));
            ui->throughput_text->setText(0);
        }
    }
}

void CtcDebugger::SetThroughput() {
    QComboBox *box = ui->station_box;
    if (box && !box->currentText().isEmpty()) {
        QString station_name = box->currentText();
        Station *s = network_->GetTrackLine(kRedlineName)->GetStation(station_name);
        int throughput = ui->throughput_text->text().toInt();
        if (s) {
            network_->GetTrackLine(kRedlineName)->UpdateSales(throughput);
        }
    }
}
