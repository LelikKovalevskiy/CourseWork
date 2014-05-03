#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T14:26:01
#
#-------------------------------------------------

QT       += core gui
QT       += svg
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cource
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myview.cpp \
    mycircle.cpp

HEADERS  += mainwindow.h \
    myview.h \
    mycircle.h

OTHER_FILES += \
    test.svg
