#include <QtTest>
#include <QApplication>

#include "../ctc/ctc_constants.h"
#include "../ctc/ctc_home.h"
#include "../ctc/block.h"
#include "../ctc/ctrain.h"
#include "../ctc/station.h"
#include "../ctc/switch.h"
#include "../ctc/trackline.h"
#include "../ctc/trainnetwork.h"

namespace ctc {

class CtcTest : public QObject
{
    Q_OBJECT

public:
    CtcTest();
    ~CtcTest();

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
    CtcGUI c;
    QVERIFY(c.Network()->IsAutomatic());
}

void CtcTest::switch_automatic()
{
    CtcGUI c;
    c.Network()->DisableAutomatic();
    QVERIFY(c.Network()->IsAutomatic() == false);
}

void CtcTest::verify_redline()
{
    CtcGUI c;
    TrackLine *tl = c.Network()->GetTrackLine(kRedlineName);
    QVERIFY(tl->GetBlockCount() == 77);
    QVERIFY(tl->GetStations().size() == 10);
}

void CtcTest::default_notrains()
{
    CtcGUI c;
    QVERIFY(c.Network()->GetTrains().size() == 0);
}

void CtcTest::schedule_redline()
{
    CtcGUI c;
    QVERIFY(c.Network()->GetTrains().size() == 0);
    TrackLine *rl = c.Network()->GetTrackLine(kRedlineName);
    CTrain *t = new CTrain(rl->GetStations().front(), QTime(0, 0), rl);
    c.Network()->AddTrain(t);
    QVERIFY(c.Network()->GetTrains().size() == 1);
    QVERIFY(c.Network()->GetTrain(1)->GetLine()->GetName() == kRedlineName);
}

void CtcTest::close_block()
{
    CtcGUI c;
    TrackLine *rl = c.Network()->GetTrackLine(kRedlineName);
    QVERIFY(rl->GetBlock(1)->IsClosed() == false);
    rl->GetBlock(1)->SetClosed(true, rl);
    QVERIFY(rl->GetBlock(1)->IsClosed() == true);
}

void CtcTest::flip_switch()
{
    CtcGUI c;
    TrackLine *rl = c.Network()->GetTrackLine(kRedlineName);
    QVERIFY(rl->GetSwitches().front()->PointingTo() == rl->GetSwitches().front()->LowerBlock());
    rl->GetSwitches().front()->UpdateState(rl->GetSwitches().front()->UpperBlock(), false);
    QVERIFY(rl->GetSwitches().front()->PointingTo() == rl->GetSwitches().front()->UpperBlock());
}

QTEST_MAIN(CtcTest)

}

#include "tst_ctc_test.moc"
