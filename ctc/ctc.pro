QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    ctc_debugger.cpp \
    ctc_greenline_gui.cpp \
    ctc_home.cpp \
    ctc_redline_gui.cpp \
    ctc_route_dialog.cpp \
    ctc_schedule_dialog.cpp \
    ctc_signal_handler.cpp \
    ctc_trains_dialog.cpp \
    ctc_upload_dialog.cpp \
    ctrain.cpp \
    main.cpp \
    station.cpp \
    switch.cpp \
    trackline.cpp \
    trainnetwork.cpp

HEADERS += \
    block.h \
    ctc_constants.h \
    ctc_debugger.h \
    ctc_greenline_gui.h \
    ctc_home.h \
    ctc_redline_gui.h \
    ctc_route_dialog.h \
    ctc_schedule_dialog.h \
    ctc_signal_handler.h \
    ctc_trains_dialog.h \
    ctc_upload_dialog.h \
    ctrain.h \
    station.h \
    switch.h \
    trackline.h \
    trainnetwork.h

FORMS += \
    ctc_debugger.ui \
    ctc_greenline_gui.ui \
    ctc_home.ui \
    ctc_redline_gui.ui \
    ctc_route_dialog.ui \
    ctc_schedule_dialog.ui \
    ctc_trains_dialog.ui \
    ctc_upload_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
