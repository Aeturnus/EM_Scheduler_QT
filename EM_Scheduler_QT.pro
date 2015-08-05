#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T22:52:34
#
#-------------------------------------------------

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -Wno-sign-compare

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EM_Scheduler_QT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../EM_Scheduler/Date.cpp \
    ../EM_Scheduler/Day.cpp \
    ../EM_Scheduler/Scheduler.cpp \
    ../EM_Scheduler/Shift.cpp \
    ../EM_Scheduler/Student.cpp \
    ../EM_Scheduler/Parser.cpp \
    ../EM_Scheduler/xlsoutput.cpp \
    newrotators.cpp \
    newschedule.cpp \
    setdate.cpp \
    editpreferences.cpp \
    displayschedule.cpp \
    displaydateshifts.cpp \
    displayshift.cpp \
    testframe.cpp \
    shiftselect.cpp \
    displaystudent.cpp \
    studentselect.cpp \
    editschedule.cpp

HEADERS  += mainwindow.h \
    ../EM_Scheduler/Date.h \
    ../EM_Scheduler/Day.h \
    ../EM_Scheduler/Scheduler.h \
    ../EM_Scheduler/Shift.h \
    ../EM_Scheduler/Student.h \
    ../EM_Scheduler/xlsoutput.h \
    ../EM_Scheduler/Parser.h \
    newrotators.h \
    newschedule.h \
    setdate.h \
    editpreferences.h \
    displayschedule.h \
    displaydateshifts.h \
    displayshift.h \
    testframe.h \
    shiftselect.h \
    displaystudent.h \
    studentselect.h \
    editschedule.h

FORMS    += mainwindow.ui \
    newrotators.ui \
    newschedule.ui \
    setdate.ui \
    editpreferences.ui \
    displayschedule.ui \
    displaydateshifts.ui \
    displayshift.ui \
    testframe.ui \
    shiftselect.ui \
    displaystudent.ui \
    studentselect.ui \
    editschedule.ui

LIBS  += "C:/lib/xlslib-qt/lib/libxls.a"
INCLUDEPATH += "C:/lib/xlslib-qt/include"
