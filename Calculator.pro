QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app


HEADERS       = button.h \
                calculator.h \
    factorial.h
SOURCES       = button.cpp \
                calculator.cpp \
                main.cpp
RESOURCES +=
                RC_FILE = images/calc.rc
