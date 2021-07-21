#include "traincontrollerui.h"
#include "ui_traincontrollerui.h"

TrainControllerUi::TrainControllerUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TrainControllerUi)
{
    ui->setupUi(this);
}

TrainControllerUi::~TrainControllerUi()
{
    delete ui;
}

// Helper function to check if input is a number
bool TrainControllerUi::IsNumber(string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void TrainControllerUi::NewTrain(int num)
{
    ui->train_index->addItem(QString::number(num));
}

// Updates the gui with the info from the currently viewed train
void TrainControllerUi::Update(TrainController train)
{
    // Speed info
    ui->actual_speed->setText(QString::number(train.actual_speed));
    ui->commanded_speed->setText((QString::number(train.commanded_speed)));
    ui->setpoint_speed->setText(QString::number(train.setpoint_speed));

    // Authority info
    ui->authority_status->setText(QString::number(train.authority));

    // Brake info
    ui->service_brake_status->setText((train.service_brake) ? "On" : "Off");
    ui->emergency_brake_status->setText((train.emergency_brake) ? "On" : "Off");

    // Train Car info
    ui->headlights_button->setText((train.headlights) ? "On" : "Off");
    ui->cabin_lights_button->setText((train.cabin_lights) ? "On" : "Off");
    ui->left_door_button->setText((train.left_door) ? "Open" : "Closed");
    ui->right_door_button->setText((train.right_door) ? "Open" : "Closed");
    ui->cabin_temp_value->setText((QString::number(train.cabin_temp)));

    // Manual mode
    ui->setpoint_speed_edit->setValue(50);
    //ui->setpoint_speed_button->setEnabled(train.manual_mode);

    //Kp and Ki info
    ui->ki_value->setText(QString::number(train.ki));
    ui->kp_value->setText(QString::number(train.kp));


}


void TrainControllerUi::on_service_brake_button_clicked()
{
    emit ToggleServiceBrake(ui->train_index->currentIndex());
}


void TrainControllerUi::on_headlights_button_clicked()
{
    emit ToggleHeadlights(ui->train_index->currentIndex());
}


void TrainControllerUi::on_cabin_lights_button_clicked()
{
    emit ToggleCabinLights(ui->train_index->currentIndex());
}


void TrainControllerUi::on_cabin_temp_button_clicked()
{
    // Make sure value wasnt empty or a string
    string s = ui->cabin_temp_value->text().toStdString();
    if (!IsNumber(s))
    {
        return;
    }

    int temp = stod(s);

    // Checks temp value is reasonable
    if (temp < 40 || temp > 90)
        return;

    emit SetCabinTemp(ui->train_index->currentIndex(), temp);

}


void TrainControllerUi::on_announcement_button_clicked()
{
    emit StartAnnouncement(ui->train_index->currentIndex());
}


void TrainControllerUi::on_setpoint_speed_button_clicked()
{
    int s = ui->setpoint_speed_edit->text().toInt();

    emit NewSetpointSpeed(ui->train_index->currentIndex(), s);
}


void TrainControllerUi::on_left_door_button_clicked()
{
    // Wont open door if train is moving
    if (ui->actual_speed->text().toInt() != 0)
        return;

    // Toggle left door
    emit ToggleLeftDoor(ui->train_index->currentIndex());
}


void TrainControllerUi::on_right_door_button_clicked()
{
    // Wont open door if train is moving
    if (ui->actual_speed->text().toInt() != 0)
        return;

    // Toggle right door
    emit ToggleRightDoor(ui->train_index->currentIndex());
}


void TrainControllerUi::on_kp_set_button_clicked()
{
    // Make sure value wasnt empty or a string
    string s = ui->kp_value->text().toStdString();
    if (!IsNumber(s))
    {
        // cout << "\n" << "empty string or non number";
        return;
    }

    double kp = stod(s);

    // validates kp value
    if (kp > 0)
        emit SetKp(ui->train_index->currentIndex(), kp);
}


void TrainControllerUi::on_ki_set_button_clicked()
{
    // Make sure value wasnt empty or a string
    string s = ui->ki_value->text().toStdString();
    if (!IsNumber(s))
    {
        // cout << "\n" << "empty string or non number";
        return;
    }

    double ki = stod(s);

    // validates ki value
    if (ki > 0)
        emit SetKi(ui->train_index->currentIndex(), ki);
}


void TrainControllerUi::on_train_index_currentIndexChanged(int index)
{
    // Update gui to the currently viewed train
    emit UpdateGui(index);
}


void TrainControllerUi::on_emergency_brake_button_clicked()
{
    emit ToggleEmergencyBrake(ui->train_index->currentIndex());

    // Update gui
    //string text = ui->emergency_brake_status->text().toStdString();
    //ui->emergency_brake_status->setText((text == "Off") ? "On" : "Off");
    emit UpdateGui(ui->train_index->currentIndex());
}

