QT       += core \
            gui\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




SOURCES += \
    addnet.cpp \
    addnets.cpp \
    allocationdevices.cpp \
    allocationunitsdialog.cpp \
    allocationunitsedit.cpp \
    codeeditor.cpp \
    content.cpp \
    dependence.cpp \
    dependenceedit.cpp \
    device.cpp \
    devices.cpp \
    error.cpp \
    errors.cpp \
    generalsettings.cpp \
    group.cpp \
    groups.cpp \
    hub.cpp \
    hubs.cpp \
    main.cpp \
    mainwindow.cpp \
    networkdialog.cpp \
    networkwidget.cpp \
    paintwidget.cpp \
    redirectmessages.cpp \
    redirectmsg.cpp \
    room.cpp \
    rooms.cpp \
    table.cpp \
    toolbarwidget.cpp \
    unit.cpp \
    unitdep.cpp \
    units.cpp

HEADERS += \
    addnet.h \
    addnets.h \
    allocationdevices.h \
    allocationunitsdialog.h \
    allocationunitsedit.h \
    codeeditor.h \
    content.h \
    dependence.h \
    dependenceedit.h \
    device.h \
    devices.h \
    error.h \
    errors.h \
    generalsettings.h \
    group.h \
    groups.h \
    hub.h \
    hubs.h \
    mainwindow.h \
    networkdialog.h \
    networkwidget.h \
    paintwidget.h \
    redirectmessages.h \
    redirectmsg.h \
    room.h \
    rooms.h \
    table.h \
    toolbarwidget.h \
    unit.h \
    unitdep.h \
    units.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    style.css

RESOURCES += \
    resources.qrc
