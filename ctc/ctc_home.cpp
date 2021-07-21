#include <QPointer>
#include <QMessageBox>

#include "ctc_constants.h"
#include "ctc_home.h"
#include "ui_ctc_home.h"
#include "ctc_schedule_dialog.h"
#include "trainnetwork.h"

CtcGUI::CtcGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CtcGUI)
{
    ui->setupUi(this);
    network_ = new TrainNetwork();
    CreateRedLine();
}

CtcGUI::~CtcGUI()
{
    delete ui;
    delete network_;
}

TrainNetwork *CtcGUI::Network() {
    return network_;
}

void CtcGUI::on_upload_button_clicked()
{
    if (!upload_popup)
        upload_popup = new CtcUploadDialog(this);

    upload_popup->show();
}


void CtcGUI::on_view_list_button_clicked()
{
    if (!trains_popup)
        trains_popup = new CtcTrainsDialog(this);

    trains_popup->show();
    trains_popup->FillTable();
}


void CtcGUI::on_redline_button_clicked()
{
    if (!redline_popup)
        redline_popup = new CtcRedLineGui(this);

    redline_popup->show();
    redline_popup->UpdateDisplay();
}


void CtcGUI::on_debug_button_clicked()
{
    if (!debug_popup)
        debug_popup = new CtcDebugger(this);

    debug_popup->show();
    debug_popup->ReloadPage();
}

void CtcGUI::CreateRedLine() {
    TrackLine *red = new TrackLine(kRedlineBlockFile,
                                   kRedlineStationFile,
                                   kRedlineSwitchesFile,
                                   kRedlineName);
    network_->AddLine(red);
}

void CtcGUI::on_greenline_button_clicked()
{
    QMessageBox::information(this, "Sorry", "This has not been added yet.");
}

