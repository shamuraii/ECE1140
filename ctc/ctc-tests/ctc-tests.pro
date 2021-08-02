QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_ctctest.cpp \
    ../c3/ctc/block.cpp \
    ../c3/ctc/ctc_debugger.cpp \
    ../c3/ctc/ctc_home.cpp \
    ../c3/ctc/ctc_redline_gui.cpp \
    ../c3/ctc/ctc_route_dialog.cpp \
    ../c3/ctc/ctc_schedule_dialog.cpp \
    ../c3/ctc/ctc_signal_handler.cpp \
    ../c3/ctc/ctc_trains_dialog.cpp \
    ../c3/ctc/ctc_upload_dialog.cpp \
    ../c3/ctc/ctrain.cpp \
    ../c3/ctc/main.cpp \
    ../c3/ctc/station.cpp \
    ../c3/ctc/switch.cpp \
    ../c3/ctc/trackline.cpp \
    ../c3/ctc/trainnetwork.cpp

SUBDIRS += \
    ../c3/ctc/ctc.pro

FORMS += \
    ../c3/ctc/ctc_debugger.ui \
    ../c3/ctc/ctc_home.ui \
    ../c3/ctc/ctc_redline_gui.ui \
    ../c3/ctc/ctc_route_dialog.ui \
    ../c3/ctc/ctc_schedule_dialog.ui \
    ../c3/ctc/ctc_trains_dialog.ui \
    ../c3/ctc/ctc_upload_dialog.ui

HEADERS += \
    ../c3/ctc/block.h \
    ../c3/ctc/ctc_constants.h \
    ../c3/ctc/ctc_debugger.h \
    ../c3/ctc/ctc_home.h \
    ../c3/ctc/ctc_redline_gui.h \
    ../c3/ctc/ctc_route_dialog.h \
    ../c3/ctc/ctc_schedule_dialog.h \
    ../c3/ctc/ctc_signal_handler.h \
    ../c3/ctc/ctc_trains_dialog.h \
    ../c3/ctc/ctc_upload_dialog.h \
    ../c3/ctc/ctrain.h \
    ../c3/ctc/station.h \
    ../c3/ctc/switch.h \
    ../c3/ctc/trackline.h \
    ../c3/ctc/trainnetwork.h
