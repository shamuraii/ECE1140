QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controllerinterface.cpp \
    main.cpp \
    trackmodelinterface.cpp \
    trainmodelbeacondialog.cpp \
    trainmodeldata.cpp \
    trainmodeldatabase.cpp \
    trainmodeldebugdialog.cpp \
    trainmodelfailuredialog.cpp \
    trainmodelgui.cpp \
    trainmodelinterface.cpp \
    trainmodelmovementdialog.cpp

HEADERS += \
    controllerinterface.h \
    trackmodelinterface.h \
    trainmodelbeacondialog.h \
    trainmodeldata.h \
    trainmodeldatabase.h \
    trainmodeldebugdialog.h \
    trainmodelfailuredialog.h \
    trainmodelgui.h \
    trainmodelinterface.h \
    trainmodelmovementdialog.h

FORMS += \
    trainmodelbeacondialog.ui \
    trainmodeldebugdialog.ui \
    trainmodelfailuredialog.ui \
    trainmodelgui.ui \
    trainmodelmovementdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
