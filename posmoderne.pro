# -------------------------------------------------
# Project created by QtCreator 2010-12-16T10:22:01
# -------------------------------------------------
QT += network \
    sql

# svg \
# testlib
# CONFIG += qt release
CONFIG += qt \
    debug
TARGET = posmoderne
TEMPLATE = app
SOURCES += src/main.cpp \
    src/MainWindow.cpp \
    src/db/DatabaseHolder.cpp \
    src/db/menu/MenuModel.cpp \
    src/db/menu/MenuPivotModel.cpp \
    src/db/menu/Menu.cpp \
    src/db/menu/MenuCategory.cpp \
    src/db/menu/MenuItem.cpp \
    src/db/menu/MenuTreeModel.cpp
HEADERS += src/MainWindow.h \
    src/db/DatabaseHolder.h \
    src/db/menu/MenuModel.h \
    src/db/menu/MenuPivotModel.h \
    src/db/menu/Menu.h \
    src/db/menu/MenuCategory.h \
    src/db/menu/MenuItem.h \
    src/db/menu/MenuTreeModel.h
FORMS += ui/MainWindow.ui
