QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block_info.cpp \
    block_info1.cpp \
    block_info2.cpp \
    block_info3.cpp \
    debug.cpp \
    main.cpp \
    mainwindow.cpp \
    plc.cpp \
    track_control.cpp \
    wssh.cpp

HEADERS += \
    block_info.h \
    block_info1.h \
    block_info2.h \
    block_info3.h \
    debug.h \
    mainwindow.h \
    plc.h \
    track_control.h \
    wssh.h

FORMS += \
    block_info.ui \
    block_info1.ui \
    block_info2.ui \
    block_info3.ui \
    debug.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
