QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TrackModel/beacon.cpp \
    TrackModel/debugger.cpp \
    TrackModel/failalert.cpp \
    TrackModel/failuremodeselector.cpp \
    TrackModel/helpmenu.cpp \
    TrackModel/mainwindow.cpp \
    TrackModel/simulation.cpp \
    TrackModel/stationdetails.cpp \
    TrackModel/trackdetails.cpp \
    TrackModel/trackmodelsh.cpp \
    TrackModel/trackselect.cpp \
    TrackModel/uploadtrack.cpp \
    TrainController/testui.cpp \
    TrainController/traincontroller.cpp \
    TrainController/traincontrollerhandler.cpp \
    TrainController/traincontrollersignalhandler.cpp \
    TrainController/traincontrollerui.cpp \
    TrainModel/controllerinterface.cpp \
    TrainModel/trackmodelinterface.cpp \
    TrainModel/trainmodelbeacondialog.cpp \
    TrainModel/trainmodeldata.cpp \
    TrainModel/trainmodeldatabase.cpp \
    TrainModel/trainmodeldebugdialog.cpp \
    TrainModel/trainmodelfailuredialog.cpp \
    TrainModel/trainmodelgui.cpp \
    TrainModel/trainmodelinterface.cpp \
    TrainModel/trainmodelmovementdialog.cpp \
    ctc/block.cpp \
    ctc/ctc_debugger.cpp \
    ctc/ctc_home.cpp \
    ctc/ctc_redline_gui.cpp \
    ctc/ctc_route_dialog.cpp \
    ctc/ctc_schedule_dialog.cpp \
    ctc/ctc_signal_handler.cpp \
    ctc/ctc_trains_dialog.cpp \
    ctc/ctc_upload_dialog.cpp \
    ctc/ctrain.cpp \
    ctc/station.cpp \
    ctc/switch.cpp \
    ctc/trackline.cpp \
    ctc/trainnetwork.cpp \
    main.cpp

HEADERS += \
    TrackModel/beacon.h \
    TrackModel/debugger.h \
    TrackModel/failalert.h \
    TrackModel/failuremodeselector.h \
    TrackModel/helpmenu.h \
    TrackModel/mainwindow.h \
    TrackModel/simulation.h \
    TrackModel/stationdetails.h \
    TrackModel/trackdetails.h \
    TrackModel/trackmodelsh.h \
    TrackModel/trackselect.h \
    TrackModel/uploadtrack.h \
    TrainController/testui.h \
    TrainController/traincontroller.h \
    TrainController/traincontrollerhandler.h \
    TrainController/traincontrollersignalhandler.h \
    TrainController/traincontrollerui.h \
    TrainModel/controllerinterface.h \
    TrainModel/trackmodelinterface.h \
    TrainModel/trainmodelbeacondialog.h \
    TrainModel/trainmodeldata.h \
    TrainModel/trainmodeldatabase.h \
    TrainModel/trainmodeldebugdialog.h \
    TrainModel/trainmodelfailuredialog.h \
    TrainModel/trainmodelgui.h \
    TrainModel/trainmodelinterface.h \
    TrainModel/trainmodelmovementdialog.h \
    connections.h \
    ctc/block.h \
    ctc/ctc_constants.h \
    ctc/ctc_debugger.h \
    ctc/ctc_home.h \
    ctc/ctc_redline_gui.h \
    ctc/ctc_route_dialog.h \
    ctc/ctc_schedule_dialog.h \
    ctc/ctc_signal_handler.h \
    ctc/ctc_trains_dialog.h \
    ctc/ctc_upload_dialog.h \
    ctc/ctrain.h \
    ctc/station.h \
    ctc/switch.h \
    ctc/trackline.h \
    ctc/trainnetwork.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    TrackModel/beacon.ui \
    TrackModel/debugger.ui \
    TrackModel/failalert.ui \
    TrackModel/failuremodeselector.ui \
    TrackModel/helpmenu.ui \
    TrackModel/mainwindow.ui \
    TrackModel/simulation.ui \
    TrackModel/stationdetails.ui \
    TrackModel/trackdetails.ui \
    TrackModel/trackselect.ui \
    TrackModel/uploadtrack.ui \
    TrainController/testui.ui \
    TrainController/traincontrollerui.ui \
    TrainModel/trainmodelbeacondialog.ui \
    TrainModel/trainmodeldebugdialog.ui \
    TrainModel/trainmodelfailuredialog.ui \
    TrainModel/trainmodelgui.ui \
    TrainModel/trainmodelmovementdialog.ui \
    ctc/ctc_debugger.ui \
    ctc/ctc_home.ui \
    ctc/ctc_redline_gui.ui \
    ctc/ctc_route_dialog.ui \
    ctc/ctc_schedule_dialog.ui \
    ctc/ctc_trains_dialog.ui \
    ctc/ctc_upload_dialog.ui
