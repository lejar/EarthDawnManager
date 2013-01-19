#-------------------------------------------------
#
# Project created by QtCreator 2013-01-12T00:21:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = EarthDawnManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    twoinputdialog.cpp

HEADERS  += mainwindow.h \
    enums.h \
    utils.h \
    twoinputdialog.h

FORMS    += mainwindow.ui \
    twoinputdialog.ui
