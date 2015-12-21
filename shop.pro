#-------------------------------------------------
#
# Project created by QtCreator 2015-12-16T01:31:09
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    finddialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    finddialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    finddialog.ui
