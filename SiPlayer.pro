#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T12:13:53
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SiPlayer
TEMPLATE = app


SOURCES += main.cpp\
    myplayer.cpp \
    siplayer.cpp \
    mediafilemanager.cpp \
    myxml.cpp \
    config.cpp

HEADERS  += \
    myplayer.h \
    siplayer.h \
    mediafilemanager.h \
    myxml.h \
    config.h
