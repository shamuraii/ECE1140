#ifndef CTC_CONSTANTS_H
#define CTC_CONSTANTS_H

#include <QString>
#include <vector>

double const kMPHperKMH = 0.621371;

QString const kRedlineBlockFile = QStringLiteral("C:\\Users\\Jeff\\Documents\\ECE 1140\\CTC Repo\\redline_blocks.csv");
QString const kRedlineStationFile = QStringLiteral("C:\\Users\\Jeff\\Documents\\ECE 1140\\CTC Repo\\redline_stations.csv");
QString const kRedlineSwitchesFile = QStringLiteral("C:\\Users\\Jeff\\Documents\\ECE 1140\\CTC Repo\\redline_switches.csv");
QString const kRedlineName = QStringLiteral("Red Line");
bool const kRedBool = 0;

QString const kGreenlineBlockFile = QStringLiteral("C:\\Users\\Jeff\\Documents\\ECE 1140\\CTC Repo\\greenline_blocks.csv");
QString const kGreenlineStationFile = QStringLiteral("C:\\Users\\Jeff\\Documents\\ECE 1140\\CTC Repo\\greenline_stations.csv");
QString const kGreenlineSwitchesFile = QStringLiteral("C:\\Users\\Jeff\\Documents\\ECE 1140\\CTC Repo\\greenline_switches.csv");
QString const kGreenlineName = QStringLiteral("Green Line");
bool const kGreenBool = 1;

#endif // CTC_CONSTANTS_H
