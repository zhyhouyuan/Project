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
    addruledialog.cpp \
    addsqltable.cpp \
    changedialog.cpp \
    checkdialog.cpp \
    connectionpool.cpp \
    datain0.cpp \
    datamanage.cpp \
    finddialog.cpp \
    gcombox.cpp \
    link.cpp \
    logdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    node.cpp \
    rule_fact.cpp \
    scene.cpp \
    viewmodel.cpp \
    change_wdialog.cpp \
    titlebar.cpp \
    tiltleitem.cpp

HEADERS += \
    addruledialog.h \
    addsqltable.h \
    changedialog.h \
    checkdialog.h \
    connectionpool.h \
    datain0.h \
    datamanage.h \
    finddialog.h \
    gcombox.h \
    link.h \
    logdialog.h \
    mainwindow.h \
    node.h \
    rule_fact.h \
    scene.h \
    viewmodel.h \
    change_wdialog.h \
    titlebar.h \
    tiltleitem.h

FORMS += \
    addruledialog.ui \
    addsqltable.ui \
    changedialog.ui \
    datain0.ui \
    finddialog.ui \
    logdialog.ui \
    mainwindow.ui \
    change_wdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

DISTFILES +=
