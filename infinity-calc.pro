#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T22:42:11
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = infinity-calc
TEMPLATE = app
VERSION = 1.0.3011


SOURCES += main.cpp\
        dashboard.cpp \
    quick_calc.cpp \
    test_func.cpp \
    source_code.cpp \
    about_me.cpp \
    google_analytics.cpp \
    INT.cpp

HEADERS  += dashboard.h \
    quick_calc.h \
    test_func.h \
    source_code.h \
    about_me.h \
    google_analytics.h \
    INT.h

FORMS    += dashboard.ui \
    quick_calc.ui \
    test_func.ui \
    source_code.ui \
    about_me.ui

RESOURCES += \
    graphics.qrc \
    sources.qrc

# [14-11-2016] RC_ICONS is used to change the default application icon
RC_ICONS = graphics/icon_splash/icon.ico
