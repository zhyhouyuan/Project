#-------------------------------------------------
#
# Project created by QtCreator 2020-03-12T16:44:47
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       +=xml
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rule-design
TEMPLATE = app
RC_ICONS = main.ico
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    src/connectionpool.cpp \
    src/datamanage.cpp \
    src/link.cpp \
    src/node.cpp \
    src/rule_fact.cpp \
    src/viewmodel.cpp \
    uisrc/addruledialog.cpp \
    uisrc/addsqltable.cpp \
    uisrc/change_wdialog.cpp \
    uisrc/changedialog.cpp \
    uisrc/checkdialog.cpp \
    uisrc/datain0.cpp \
    uisrc/finddialog.cpp \
    uisrc/gcombox.cpp \
    uisrc/logdialog.cpp \
    uisrc/scene.cpp \
    uisrc/tiltleitem.cpp \
    uisrc/titlebar.cpp \
    main.cpp \
    mainwindow.cpp


HEADERS += \
    src/connectionpool.h \
    src/datamanage.h \
    src/link.h \
    src/node.h \
    src/rule_fact.h \
    src/viewmodel.h \
    uisrc/addruledialog.h \
    uisrc/addsqltable.h \
    uisrc/change_wdialog.h \
    uisrc/changedialog.h \
    uisrc/checkdialog.h \
    uisrc/datain0.h \
    uisrc/finddialog.h \
    uisrc/gcombox.h \
    uisrc/logdialog.h \
    uisrc/scene.h \
    uisrc/tiltleitem.h \
    uisrc/titlebar.h \
    mainwindow.h



FORMS += \
    uisrc/addruledialog.ui \
    uisrc/addsqltable.ui \
    uisrc/change_wdialog.ui \
    uisrc/changedialog.ui \
    uisrc/datain0.ui \
    uisrc/finddialog.ui \
    uisrc/logdialog.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

DISTFILES +=
