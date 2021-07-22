QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    beacon.cpp \
    debugger.cpp \
    failalert.cpp \
    failuremodeselector.cpp \
    helpmenu.cpp \
    main.cpp \
    simulation.cpp \
    stationdetails.cpp \
    tm_mainwindow.cpp \
    trackdetails.cpp \
    trackmodelsh.cpp \
    trackselect.cpp \
    train.cpp \
    uploadtrack.cpp

HEADERS += \
    beacon.h \
    debugger.h \
    failalert.h \
    failuremodeselector.h \
    helpmenu.h \
    simulation.h \
    stationdetails.h \
    tm_mainwindow.h \
    trackdetails.h \
    trackmodelsh.h \
    trackselect.h \
    train.h \
    uploadtrack.h

FORMS += \
    beacon.ui \
    debugger.ui \
    failalert.ui \
    failuremodeselector.ui \
    helpmenu.ui \
    simulation.ui \
    stationdetails.ui \
    tm_mainwindow.ui \
    trackdetails.ui \
    trackselect.ui \
    uploadtrack.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
