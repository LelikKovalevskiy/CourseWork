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
    mycircle.cpp \
    myshape.cpp \
    myrect.cpp

HEADERS  += mainwindow.h \
    myview.h \
    mycircle.h \
    myshape.h \
    myrect.h

OTHER_FILES += \
    ../build-Cource-Desktop_Qt_5_2_1_MinGW_32bit-Debug/test.svg \
    ../build-Cource-Desktop_Qt_5_2_1_MinGW_32bit-Debug/result.svg
