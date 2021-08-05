#include <QtTest>
#include "../TrainController/traincontroller.h"
#include "../TrainController/traincontrollerhandler.h"
#include "../TrainController/traincontrollersignalhandler.h"

// add necessary includes here

class TrainControllerTest : public QObject
{
    Q_OBJECT

public:
    TrainControllerTest();
    ~TrainControllerTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void service_brake_test();
    void emergency_brake_test();
    void manual_mode_test();
    void kp_ki_test();
    void headlights_test();
    void power_test();
    void authority_test();
    void train_info_buttons_test();
    void beacon_test();


};

TrainControllerTest::TrainControllerTest()
{

}

TrainControllerTest::~TrainControllerTest()
{

}

void TrainControllerTest::initTestCase()
{

}

void TrainControllerTest::cleanupTestCase()
{

}

void TrainControllerTest::service_brake_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.ToggleServiceBrake(0);
    QVERIFY(tc.trains[0].service_brake);
    tc.ToggleServiceBrake(0);
    QVERIFY(!tc.trains[0].service_brake);
}

void TrainControllerTest::emergency_brake_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.ToggleEmergencyBrake(0);
    QVERIFY(tc.trains[0].emergency_brake);
    tc.ToggleEmergencyBrake(0);
    QVERIFY(!tc.trains[0].emergency_brake);
}

void TrainControllerTest::manual_mode_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.ManualMode(0);
    QVERIFY(tc.trains[0].manual_mode);
    tc.NewCommandedSpeed(0, 50); // Setpoint speed cannot be greater than commanded speed
    // When comparing, speeds need to be converted to m/s
    QCOMPARE(tc.trains[0].commanded_speed, 50 * (5.0/18.0)); // 50 is kmph
    tc.NewSetpointSpeed(0,10);
    QCOMPARE(tc.trains[0].setpoint_speed, 10 * 0.44704); // 20 is mph
}

void TrainControllerTest::kp_ki_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.SetKp(0, 3000);
    QCOMPARE(tc.trains[0].kp, 3000);
    tc.SetKi(0, 100);
    QCOMPARE(tc.trains[0].ki, 100);

}

void TrainControllerTest::headlights_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.ToggleHeadlights(0);
    QVERIFY(tc.trains[0].headlights);
    tc.ToggleHeadlights(0);
    QVERIFY(!tc.trains[0].headlights);
}

void TrainControllerTest::power_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.NewCommandedSpeed(0, 30);
    tc.NewAuthority(0, 1);
    tc.NewActualSpeed(0,0); // Power should now be set to max
    QCOMPARE(tc.trains[0].power, 120000);
}

void TrainControllerTest::authority_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.NewAuthority(0,1);
    QVERIFY(tc.trains[0].authority);
    tc.NewAuthority(0,0);
    QVERIFY(!tc.trains[0].authority);
}

void TrainControllerTest::train_info_buttons_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.ToggleHeadlights(0);
    tc.ToggleCabinLights(0);
    tc.SetCabinTemp(0, 80);
    tc.ToggleLeftDoor(0);
    tc.ToggleRightDoor(0);

    QVERIFY(tc.trains[0].headlights);
    QVERIFY(tc.trains[0].cabin_lights);
    QVERIFY(tc.trains[0].cabin_temp);
    QVERIFY(tc.trains[0].left_door);
    QVERIFY(tc.trains[0].right_door);

}

void TrainControllerTest::beacon_test()
{
    TrainControllerHandler tc;
    tc.NewTrainController(0);
    tc.NewBeaconInfo(0,"Penn,Left");

    QCOMPARE(tc.trains[0].announcement, "Arriving at Penn");
    QCOMPARE(tc.trains[0].open_door, 1);

}


QTEST_APPLESS_MAIN(TrainControllerTest)

#include "tst_traincontrollertest.moc"
