#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T19:03:27
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       +=xml
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Rule-manage
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
        main.cpp \
    src/addruledialog.cpp \
    src/addsqltable.cpp \
    src/changedialog.cpp \
    src/checkdialog.cpp \
    src/finddialog.cpp \
    src/gcombox.cpp \
    src/logdialog.cpp \
    src/tiltleitem.cpp \
    src/titlebar.cpp \
    srcsq/connectionpool.cpp \
    srcsq/datamanage.cpp \
    srcsq/link.cpp \
    srcsq/node.cpp \
    srcsq/nodeinfodialog.cpp \
    srcsq/rule_fact.cpp \
    srcsq/scene.cpp \
    srcsq/viewmodel.cpp \
    srcsq/xml.cpp \
    src/mainwindow.cpp


HEADERS += \
    src/addruledialog.h \
    src/addsqltable.h \
    src/changedialog.h \
    src/checkdialog.h \
    src/finddialog.h \
    src/gcombox.h \
    src/logdialog.h \
    src/tiltleitem.h \
    src/titlebar.h \
    srcsq/connectionpool.h \
    srcsq/datamanage.h \
    srcsq/link.h \
    srcsq/node.h \
    srcsq/nodeinfodialog.h \
    srcsq/rule_fact.h \
    srcsq/scene.h \
    srcsq/viewmodel.h \
    srcsq/xml.h \
    src/mainwindow.h


FORMS += \
    src/addruledialog.ui \
    src/addsqltable.ui \
    src/changedialog.ui \
    src/finddialog.ui \
    src/logdialog.ui \
    src/mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

DISTFILES +=
