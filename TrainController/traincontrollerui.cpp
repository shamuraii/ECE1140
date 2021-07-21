#include "traincontrollerui.h"
#include "ui_traincontrollerui.h"

TrainControllerUi::TrainControllerUi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TrainControllerUi)
{
    ui->setupUi(this);
    SetUpSignals();

}

TrainControllerUi::~TrainControllerUi()
{
    delete ui;
}

// Connects all signals and slots between Uis and train controller handler
void TrainControllerUi::SetUpSignals()
{
    // Train gui and handler singal connection
    QObject::connect(&train_handler, SIGNAL(GuiUpdate(TrainController)), this, SLOT(Update(TrainController)));
    QObject::connect(&train_handler, SIGNAL(GuiNewTrain(int)), this, SLOT(NewTrain(int)));
    QObject::connect(this, SIGNAL(ToggleServiceBrake(int)), &train_handler, SLOT(ToggleServiceBrake(int)));
    QObject::connect(this, SIGNAL(ToggleEmergencyBrake(int)), &train_handler, SLOT(ToggleEmergencyBrake(int)));
    QObject::connect(this, SIGNAL(ToggleHeadlights(int)), &train_handler, SLOT(ToggleHeadlights(int)));
    QObject::connect(this, SIGNAL(ToggleCabinLights(int)), &train_handler, SLOT(ToggleCabinLights(int)));
    QObject::connect(this, SIGNAL(SetCabinTemp(int,double)), &train_handler, SLOT(SetCabinTemp(int,double)));
    QObject::connect(this, SIGNAL(ToggleLeftDoor(int)), &train_handler, SLOT(ToggleLeftDoor(int)));
    QObject::connect(this, SIGNAL(ToggleRightDoor(int)), &train_handler, SLOT(ToggleRightDoor(int)));
    QObject::connect(this, SIGNAL(SetKp(int,double)), &train_handler, SLOT(SetKp(int,double)));
    QObject::connect(this, SIGNAL(SetKi(int,double)), &train_handler, SLOT(SetKi(int,double)));
    QObject::connect(this, SIGNAL(UpdateGui(int)), &train_handler, SLOT(UpdateGui(int)));
    QObject::connect(this, SIGNAL(StartAnnouncement(int)), &train_handler, SLOT(StartAnnouncement(int)));
    QObject::connect(this, SIGNAL(NewSetpointSpeed(int,double)), &train_handler, SLOT(NewSetpointSpeed(int,double)));


    // Test gui and handler signal connection
    QObject::connect(&test_ui, SIGNAL(NewTrain(int)), &train_handler, SLOT(NewTrainController(int)));
    QObject::connect(&test_ui, SIGNAL(NewCommandedSpeed(int,double)), &train_handler, SLOT(NewCommandedSpeed(int,double)));
    QObject::connect(&train_handler, SIGNAL(ServiceBrake(int,bool)), &test_ui, SLOT(ServiceBrake(int,bool)));
    QObject::connect(&train_handler, SIGNAL(EmergencyBrake(int,bool)), &test_ui, SLOT(EmergencyBrake(int,bool)));
    QObject::connect(&train_handler, SIGNAL(SendPower(int,double)), &test_ui, SLOT(NewPower(int,double)));
    QObject::connect(&test_ui, SIGNAL(NewActualSpeed(int,double)), &train_handler, SLOT(NewActualSpeed(int,double)));
    QObject::connect(&train_handler, SIGNAL(Headlights(int,bool)), &test_ui, SLOT(Headlights(int,bool)));
    QObject::connect(&train_handler, SIGNAL(CabinLights(int,bool)), &test_ui, SLOT(CabinLights(int,bool)));
    QObject::connect(&train_handler, SIGNAL(CabinTemp(int,double)), &test_ui, SLOT(CabinTemp(int,double)));
    QObject::connect(&train_handler, SIGNAL(LeftDoor(int,bool)), &test_ui, SLOT(LeftDoor(int,bool)));
    QObject::connect(&train_handler, SIGNAL(RightDoor(int,bool)), &test_ui, SLOT(RightDoor(int,bool)));\
    QObject::connect(&test_ui, SIGNAL(ToggleEmergencyBrake(int)), &train_handler, SLOT(ToggleEmergencyBrake(int)));
    QObject::connect(&train_handler, SIGNAL(Announcement(int,string)), &test_ui, SLOT(Announcement(int,string)));
    QObject::connect(&train_handler, SIGNAL(GuiTestUpdate(TrainController)), &test_ui, SLOT(UpdateTest(TrainController)));
    QObject::connect(&test_ui, SIGNAL(UpdateTestGui(int)), &train_handler, SLOT(UpdateTestGui(int)));
    QObject::connect(&test_ui, SIGNAL(NewAuthority(int,int)), &train_handler, SLOT(NewAuthority(int,int)));
    QObject::connect(&test_ui, SIGNAL(FailureMode(int,string)), &train_handler, SLOT(FailureMode(int,string)));

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


void TrainControllerUi::on_debugger_clicked()
{
    test_ui.show();
}

