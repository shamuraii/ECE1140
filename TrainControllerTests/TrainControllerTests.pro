QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_traincontrollertest.cpp \
    ../TrainController/traincontroller.cpp \
    ../TrainController/traincontrollerhandler.cpp \
    ../TrainController/traincontrollersignalhandler.cpp

HEADERS += \
    ../TrainController/traincontroller.h \
    ../TrainController/traincontrollerhandler.h \
    ../TrainController/traincontrollersignalhandler.h
