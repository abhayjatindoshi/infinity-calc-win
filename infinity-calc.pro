#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T22:42:11
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = infinity-calc
TEMPLATE = app


SOURCES += main.cpp\
        dashboard.cpp \
    quick_calc.cpp \
    test_func.cpp \
    source_code.cpp \
    settings.cpp \
    about_me.cpp \
    sources/INT.cpp \
    google_analytics.cpp

HEADERS  += dashboard.h \
    quick_calc.h \
    test_func.h \
    source_code.h \
    settings.h \
    about_me.h \
    sources/INT.h \
    google_analytics.h

FORMS    += dashboard.ui \
    quick_calc.ui \
    test_func.ui \
    source_code.ui \
    settings.ui \
    about_me.ui

RESOURCES += \
    graphics.qrc \
    sources.qrc

# [14-11-2016] RC_ICONS is used to change the default application icon
RC_ICONS = graphics/icon_splash/icon.ico
