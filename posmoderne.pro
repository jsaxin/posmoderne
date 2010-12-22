# -------------------------------------------------
# Project created by QtCreator 2010-12-16T10:22:01
# -------------------------------------------------
QT += network sql
# svg \
# testlib

#CONFIG += qt release
CONFIG += qt debug

TARGET   = posmoderne
TEMPLATE = app
SOURCES += src/main.cpp \
           src/MainWindow.cpp \
           src/db/DatabaseHolder.cpp \
           src/db/MenuModel.cpp
HEADERS += src/MainWindow.h \
           src/db/DatabaseHolder.h \
           src/db/MenuModel.h
FORMS   += ui/MainWindow.ui
