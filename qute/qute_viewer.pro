######################################################################
# Automatically generated by qmake (2.01a) wt. lis 23 13:04:10 2010
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . app include
INCLUDEPATH += . include
DEFINES += VIEWER
CONFIG += help

# Input
HEADERS += include/mainwindow.h include/helpbrowser.h \
    include/aboutbox.h
SOURCES += app/main.cpp app/mainwindow.cpp src/helpbrowser.cpp \
    src/aboutbox.cpp

FORMS += \
    app/viewerwindow.ui \
    app/aboutbox.ui

TRANSLATIONS = ../lang/qute_viewer_pl.ts
CODECFORTR = UTF-8

RCC_DIR = "../build/build-viewer"
UI_DIR = "../build/build-viewer"
MOC_DIR = "../build/build-viewer"
OBJECTS_DIR = "../build/build-viewer"

CONFIG(debug, debug|release) {
    DESTDIR = ../build/debug
} else {
    DESTDIR = ../build/release
}
