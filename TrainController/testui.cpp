#include "testui.h"
#include "ui_testui.h"

TestUi::TestUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestUi)
{
    ui->setupUi(this);
    num_trains = 0;
    AddNewTrain(0);
}

TestUi::~TestUi()
{
    delete ui;
}

// Helper function to check if input is a number
bool TestUi::IsNumber(string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void TestUi::on_new_train_button_clicked()
{
    num_trains += 1;
    ui->train_index->addItem(QString::number(num_trains));
    emit NewTrain(num_trains - 1);
}

void TestUi::AddNewTrain(int index)
{
    qDebug() << "In Test Ui Add new train: " << index;
    num_trains += 1;
    ui->train_index->addItem(QString::number(index+1));
}

void TestUi::on_commanded_speed_button_clicked()
{
    if (num_trains == 0)
        return;

    string speed = ui->commanded_speed->text().toStdString();
    if (!IsNumber(speed))
    {
        cout << "\n" << "empty string or non number";
        return;
    }

    emit NewCommandedSpeed(ui->train_index->currentText().toInt() - 1,MPHToKMPH(stod(speed)));
}

void TestUi::ServiceBrake(int index, bool brake_state)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->service_brake_status->setText((brake_state) ? "On" : "Off");
}

void TestUi::EmergencyBrake(int index, bool brake_state)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->emergency_brake_status->setText((brake_state) ? "On" : "Off");
}

void TestUi::NewPower(int index, double power)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->power_value->setText(QString::number(power));
}

void TestUi::on_actual_speed_button_clicked()
{
    if (num_trains == 0)
        return;

    string speed = ui->actual_speed->text().toStdString();
    if (!IsNumber(speed))
    {
        cout << "\n" << "empty string or non number";
        return;
    }


    emit NewActualSpeed(ui->train_index->currentText().toInt() - 1,MPHToKMPH(stod(speed)));
}

void TestUi::Headlights(int index, bool lights_status)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->headlight_status->setText((lights_status) ? "On" : "Off");
}

void TestUi::CabinLights(int index, bool lights_status)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->cabin_lights_status->setText((lights_status) ? "On" : "Off");
}

void TestUi::CabinTemp(int index, double temp)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->cabin_temp_value->setText(QString::number(temp));
}

void TestUi::Announcement(int index, QString station)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->announcement_status->setText("Arriving at " + station);
}

void TestUi::LeftDoor(int index, bool door_status)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->left_door_status->setText((door_status) ? "Open" : "Closed");
}

void TestUi::RightDoor(int index, bool door_status)
{
    if (num_trains == 0)
        return;

    if (ui->train_index->currentText().toInt() - 1 == index)
        ui->right_door_status->setText((door_status) ? "Open" : "Closed");
}

void TestUi::on_emergency_brake_button_clicked()
{
    if (num_trains == 0)
        return;

    emit ToggleEmergencyBrake(ui->train_index->currentText().toInt() - 1);

}

// Updates the gui with the info from the currently viewed train
void TestUi::UpdateTest(TrainController train)
{
    // Speed info
    ui->actual_speed_value->setText(QString::number(MSToMPH(train.actual_speed)));
    ui->commanded_speed_value->setText(QString::number(MSToMPH(train.commanded_speed)));

    // Authority info
    ui->authority_status->setText(QString::number(train.authority));

    // Brake info
    ui->service_brake_status->setText((train.service_brake) ? "On" : "Off");
    ui->emergency_brake_status->setText((train.emergency_brake) ? "On" : "Off");

    // Train Car info
    ui->headlight_status->setText((train.headlights) ? "On" : "Off");
    ui->cabin_lights_status->setText((train.cabin_lights) ? "On" : "Off");
    ui->left_door_status->setText((train.left_door) ? "Open" : "Closed");
    ui->right_door_status->setText((train.right_door) ? "Open" : "Closed");
    ui->cabin_temp_value->setText((QString::number(train.cabin_temp)));

    // Power Info
    ui->power_value->setText(QString::number(train.power));

    // Announcement
    ui->announcement_status->setText("");

}


void TestUi::on_authority_button_clicked()
{
    if (num_trains == 0)
        return;

    string a = ui->authority->text().toStdString();
    if (!IsNumber(a))
    {
        cout << "\n" << "empty string or non number";
        return;
    }


    emit NewAuthority(ui->train_index->currentText().toInt() - 1,stoi(a));
}


void TestUi::on_failure_mode_button_clicked()
{
    if (num_trains == 0)
        return;

    emit FailureMode(ui->train_index->currentText().toInt() - 1, 0);
}

void TestUi::on_train_index_currentIndexChanged(int index)
{
    if (num_trains == 0)
            return;

    if (num_trains !=1)
        emit UpdateTestGui(ui->train_index->currentText().toInt() - 1);
}

double TestUi::MSToMPH(double speed)
{
    return speed*2.23694;
}

double TestUi::MPHToKMPH(double speed)
{
    return speed*1.60934;
}
