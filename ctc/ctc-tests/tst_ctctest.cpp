#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "../c3/ctc/ctc_home.h"
#include "../c3/ctc/ctc_constants.h"
#include "../c3/ctc/ctrain.h"
#include "../c3/ctc/trainnetwork.h"
#include "../c3/ctc/trackline.h"
#include "../c3/ctc/station.h"
#include "../c3/ctc/block.h"
#include "../c3/ctc/switch.h"

class CtcTest : public QObject
{
    Q_OBJECT

public:
    CtcTest();
    ~CtcTest();
    CtcGUI c;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void defaults_automatic();
    void switch_automatic();
    void verify_redline();
    void default_notrains();
    void schedule_redline();
    void close_block();
    void flip_switch();

};

CtcTest::CtcTest()
{
    c = CtcGUI();

}

CtcTest::~CtcTest()
{

}

void CtcTest::initTestCase()
{

}

void CtcTest::cleanupTestCase()
{

}

void CtcTest::defaults_automatic()
{
    QVERIFY(c.Network()->IsAutomatic());
}

void CtcTest::switch_automatic()
{
    c.Network()->DisableAutomatic();
    QVERIFY(c.Network()->IsAutomatic() == false);
}

void CtcTest::verify_redline()
{
    TrackLine *tl = c.Network()->GetTrackLine(kRedlineName);
    QVERIFY(tl->GetBlockCount() == 77);
    QVERIFY(tl->GetStations().size() == 10);
}

void CtcTest::default_notrains()
{
    QVERIFY(c.Network()->GetTrains().size() == 0);
}

void CtcTest::schedule_redline()
{
    QVERIFY(c.Network()->GetTrains().size() == 0);
    TrackLine *rl = c.Network()->GetTrackLine(kRedlineName);
    CTrain *t = new CTrain(rl->GetStations().front(), QTime(0, 0), rl);
    c.Network()->AddTrain(t);
    QVERIFY(c.Network()->GetTrains().size() == 1);
    QVERIFY(c.Network()->GetTrain(1)->GetLine()->GetName() == kRedlineName);
}

void CtcTest::close_block()
{
    TrackLine *rl = c.Network()->GetTrackLine(kRedlineName);
    QVERIFY(rl->GetBlock(1)->IsClosed() == false);
    rl->GetBlock(1)->SetClosed(true, rl);
    QVERIFY(rl->GetBlock(1)->IsClosed() == true);
}

void CtcTest::flip_switch()
{
    TrackLine *rl = c.Network()->GetTrackLine(kRedlineName);
    QVERIFY(rl->GetSwitches().front()->PointingTo() == rl->GetSwitches().front()->LowerBlock());
    rl->GetSwitches().front()->UpdateState(rl->GetSwitches().front()->UpperBlock(), false);
    QVERIFY(rl->GetSwitches().front()->PointingTo() == rl->GetSwitches().front()->UpperBlock());
}

QTEST_MAIN(CtcTest)

#include "tst_ctctest.moc"
