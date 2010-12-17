# -------------------------------------------------
# Project created by QtCreator 2010-12-16T10:22:01
# -------------------------------------------------
QT += network \
    sql \
    svg \
    testlib
TARGET = posmoderne
TEMPLATE = app
SRCPATH = src
UIPATH = ui
SOURCES += $$SRCPATH/main.cpp \
    $$SRCPATH/MainWindow.cpp \
    src/db/DatabaseHolder.cpp
HEADERS += $$SRCPATH/MainWindow.h \
    src/db/DatabaseHolder.h
FORMS += $$UIPATH/MainWindow.ui
