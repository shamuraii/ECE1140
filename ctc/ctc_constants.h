#ifndef CTC_CONSTANTS_H
#define CTC_CONSTANTS_H

#include <QString>
#include <vector>

double const kMPHperKMH = 0.621371;

QString const kRedlineBlockFile = QStringLiteral("redline_blocks.csv");
QString const kRedlineStationFile = QStringLiteral("redline_stations.csv");
QString const kRedlineSwitchesFile = QStringLiteral("redline_switches.csv");
QString const kRedlineName = QStringLiteral("Red Line");
bool const kRedBool = 0;

QString const kGreenlineBlockFile = QStringLiteral("greenline_blocks.csv");
QString const kGreenlineStationFile = QStringLiteral("greenline_stations.csv");
QString const kGreenlineSwitchesFile = QStringLiteral("greenline_switches.csv");
QString const kGreenlineName = QStringLiteral("Green Line");
bool const kGreenBool = 1;

#endif // CTC_CONSTANTS_H
