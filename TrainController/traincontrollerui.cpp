#include "traincontrollerui.h"
#include "ui_traincontrollerui.h"

TrainControllerUi::TrainControllerUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TrainControllerUi)
{
    ui->setupUi(this);
    SetUpSignals();
    NewTrain(0);

}

TrainControllerUi::~TrainControllerUi()
{
    delete ui;
}

// Connects all signals and slots between Uis and train controller handler
void TrainControllerUi::SetUpSignals()
{
    // Train gui and handler singal connection
    qDebug() << "Setting up Signals";
    QObject::connect(&train_handler, &TrainControllerHandler::GuiUpdate, this, &TrainControllerUi::Update);
    QObject::connect(&train_handler, &TrainControllerHandler::GuiNewTrain, this, &TrainControllerUi::NewTrain);
    QObject::connect(this, &TrainControllerUi::ToggleServiceBrake, &train_handler, &TrainControllerHandler::ToggleServiceBrake);
    QObject::connect(this, &TrainControllerUi::ToggleEmergencyBrake, &train_handler, &TrainControllerHandler::ToggleEmergencyBrake);
    QObject::connect(this, &TrainControllerUi::ToggleHeadlights, &train_handler, &TrainControllerHandler::ToggleHeadlights);
    QObject::connect(this, &TrainControllerUi::ToggleCabinLights, &train_handler, &TrainControllerHandler::ToggleCabinLights);
    QObject::connect(this, &TrainControllerUi::SetCabinTemp, &train_handler, &TrainControllerHandler::SetCabinTemp);
    QObject::connect(this, &TrainControllerUi::ToggleLeftDoor, &train_handler, &TrainControllerHandler::ToggleLeftDoor);
    QObject::connect(this, &TrainControllerUi::ToggleRightDoor, &train_handler, &TrainControllerHandler::ToggleRightDoor);
    QObject::connect(this, &TrainControllerUi::SetKp, &train_handler, &TrainControllerHandler::SetKp);
    QObject::connect(this, &TrainControllerUi::SetKi, &train_handler, &TrainControllerHandler::SetKi);
    QObject::connect(this, &TrainControllerUi::UpdateGui, &train_handler, &TrainControllerHandler::UpdateGui);
    QObject::connect(this, &TrainControllerUi::StartAnnouncement, &train_handler, &TrainControllerHandler::StartAnnouncement);
    QObject::connect(this, &TrainControllerUi::NewSetpointSpeed, &train_handler, &TrainControllerHandler::NewSetpointSpeed);
    QObject::connect(this, &TrainControllerUi::ToggleManualMode, &train_handler, &TrainControllerHandler::ManualMode);


    // Test gui and handler signal connection
    QObject::connect(&test_ui, &TestUi::NewTrain, &train_handler, &TrainControllerHandler::NewTrainController);
    QObject::connect(&test_ui, &TestUi::NewCommandedSpeed, &train_handler, &TrainControllerHandler::NewCommandedSpeed);
    QObject::connect(&train_handler, &TrainControllerHandler::GuiTestNewTrain, &test_ui, &TestUi::AddNewTrain);
    QObject::connect(&train_handler, &TrainControllerHandler::ServiceBrake, &test_ui, &TestUi::ServiceBrake);
    QObject::connect(&train_handler, &TrainControllerHandler::EmergencyBrake, &test_ui, &TestUi::EmergencyBrake);
    QObject::connect(&train_handler, &TrainControllerHandler::SendPower, &test_ui, &TestUi::NewPower);
    QObject::connect(&test_ui, &TestUi::NewActualSpeed, &train_handler, &TrainControllerHandler::NewActualSpeed);
    QObject::connect(&train_handler, &TrainControllerHandler::Headlights, &test_ui, &TestUi::Headlights);
    QObject::connect(&train_handler, &TrainControllerHandler::CabinLights, &test_ui, &TestUi::CabinLights);
    QObject::connect(&train_handler, &TrainControllerHandler::CabinTemp, &test_ui, &TestUi::CabinTemp);
    QObject::connect(&train_handler, &TrainControllerHandler::LeftDoor, &test_ui, &TestUi::LeftDoor);
    QObject::connect(&train_handler, &TrainControllerHandler::RightDoor, &test_ui, &TestUi::RightDoor);
    QObject::connect(&test_ui, &TestUi::ToggleEmergencyBrake, &train_handler, &TrainControllerHandler::ToggleEmergencyBrake);
    QObject::connect(&train_handler, &TrainControllerHandler::Announcement, &test_ui, &TestUi::Announcement);
    QObject::connect(&train_handler, &TrainControllerHandler::GuiTestUpdate, &test_ui, &TestUi::UpdateTest);
    QObject::connect(&test_ui, &TestUi::UpdateTestGui, &train_handler, &TrainControllerHandler::UpdateTestGui);
    QObject::connect(&test_ui, &TestUi::NewAuthority, &train_handler, &TrainControllerHandler::NewAuthority);
    QObject::connect(&test_ui, &TestUi::FailureMode, &train_handler, &TrainControllerHandler::FailureMode);

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
    qDebug() << "In Ui Add new train: " << num;
    ui->train_index->addItem(QString::number(num+1));
}

// Updates the gui with the info from the currently viewed train
void TrainControllerUi::Update(TrainController train)
{
    // Speed info
    ui->actual_speed->setText(QString::number(MSToMPH(train.actual_speed)));
    ui->commanded_speed->setText((QString::number(MSToMPH(train.commanded_speed))));
    ui->setpoint_speed->setText(QString::number(MSToMPH(train.setpoint_speed)));

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
    ui->cabin_temp->setText((QString::number(train.cabin_temp)));

    // Manual mode
    ui->setpoint_speed_edit->setValue(train.setpoint_speed);
    ui->manual_mode_status->setText((train.manual_mode) ? "On" : "Off");
    //ui->setpoint_speed_button->setEnabled(train.manual_mode);

    //Kp and Ki info
    ui->ki_value->setText(QString::number(train.ki));
    ui->kp_value->setText(QString::number(train.kp));


}


void TrainControllerUi::on_service_brake_button_clicked()
{
    emit ToggleServiceBrake(ui->train_index->currentText().toInt() - 1);
}


void TrainControllerUi::on_headlights_button_clicked()
{
    emit ToggleHeadlights(ui->train_index->currentText().toInt() - 1);
}


void TrainControllerUi::on_cabin_lights_button_clicked()
{
    emit ToggleCabinLights(ui->train_index->currentText().toInt() - 1);
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

    emit SetCabinTemp(ui->train_index->currentText().toInt() - 1, temp);

}


void TrainControllerUi::on_announcement_button_clicked()
{
    emit StartAnnouncement(ui->train_index->currentText().toInt() - 1);
}


void TrainControllerUi::on_setpoint_speed_button_clicked()
{
    int s = ui->setpoint_speed_edit->text().toInt();

    emit NewSetpointSpeed(ui->train_index->currentText().toInt() - 1, s);
}


void TrainControllerUi::on_left_door_button_clicked()
{
    // Wont open door if train is moving
    if (ui->actual_speed->text().toInt() != 0)
        return;

    // Toggle left door
    emit ToggleLeftDoor(ui->train_index->currentText().toInt() - 1);
}


void TrainControllerUi::on_right_door_button_clicked()
{
    // Wont open door if train is moving
    if (ui->actual_speed->text().toInt() != 0)
        return;

    // Toggle right door
    emit ToggleRightDoor(ui->train_index->currentText().toInt() - 1);
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
        emit SetKp(ui->train_index->currentText().toInt() - 1, kp);
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
        emit SetKi(ui->train_index->currentText().toInt() - 1, ki);
}


void TrainControllerUi::on_train_index_currentIndexChanged(int index)
{
    // Update gui to the currently viewed train
    emit UpdateGui(ui->train_index->currentText().toInt() - 1);
}


void TrainControllerUi::on_emergency_brake_button_clicked()
{
    emit ToggleEmergencyBrake(ui->train_index->currentText().toInt() - 1);

    // Update gui
    //string text = ui->emergency_brake_status->text().toStdString();
    //ui->emergency_brake_status->setText((text == "Off") ? "On" : "Off");
    emit UpdateGui(ui->train_index->currentText().toInt() - 1);
}


void TrainControllerUi::on_debugger_clicked()
{
    test_ui.show();
}


void TrainControllerUi::on_manual_mode_button_clicked()
{
    emit ToggleManualMode(ui->train_index->currentText().toInt() - 1);
}

// Utility function to convert m/s to mph
double TrainControllerUi::MSToMPH(double speed)
{
    return speed*2.23694;
}
