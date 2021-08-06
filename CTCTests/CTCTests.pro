QT += testlib
QT += gui
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_ctc_test.cpp \
    ../ctc/block.cpp \
    ../ctc/ctc_debugger.cpp \
    ../ctc/ctc_greenline_gui.cpp \
    ../ctc/ctc_home.cpp \
    ../ctc/ctc_redline_gui.cpp \
    ../ctc/ctc_route_dialog.cpp \
    ../ctc/ctc_schedule_dialog.cpp \
    ../ctc/ctc_signal_handler.cpp \
    ../ctc/ctc_trains_dialog.cpp \
    ../ctc/ctc_upload_dialog.cpp \
    ../ctc/ctrain.cpp \
    ../ctc/station.cpp \
    ../ctc/switch.cpp \
    ../ctc/trackline.cpp \
    ../ctc/trainnetwork.cpp

HEADERS += \
    ../ctc/block.h \
    ../ctc/ctc_constants.h \
    ../ctc/ctc_debugger.h \
    ../ctc/ctc_greenline_gui.h \
    ../ctc/ctc_home.h \
    ../ctc/ctc_redline_gui.h \
    ../ctc/ctc_route_dialog.h \
    ../ctc/ctc_schedule_dialog.h \
    ../ctc/ctc_signal_handler.h \
    ../ctc/ctc_trains_dialog.h \
    ../ctc/ctc_upload_dialog.h \
    ../ctc/ctrain.h \
    ../ctc/station.h \
    ../ctc/switch.h \
    ../ctc/trackline.h \
    ../ctc/trainnetwork.h

FORMS += \
    ../ctc/ctc_debugger.ui \
    ../ctc/ctc_greenline_gui.ui \
    ../ctc/ctc_home.ui \
    ../ctc/ctc_redline_gui.ui \
    ../ctc/ctc_route_dialog.ui \
    ../ctc/ctc_schedule_dialog.ui \
    ../ctc/ctc_trains_dialog.ui \
    ../ctc/ctc_upload_dialog.ui
