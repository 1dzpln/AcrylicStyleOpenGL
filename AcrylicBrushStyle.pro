#-------------------------------------------------
#
# Project created by QtCreator 2020-09-26T17:49:10
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AcrylicBrushStyle
TEMPLATE = app

UI_DIR = ./build
MOC_DIR = ./build
OBJECTS_DIR = ./build
RCC_DIR = ./build
DESTDIR = ./bin

CONFIG += c++14

SOURCES += \
        ResourceManager/shadermanager.cpp \
        ResourceManager/texturemanager.cpp \
        SceneManager/openglwidget.cpp \
        ModelManager/modelmanager.cpp \
        core.cpp \
        main.cpp \
        mainwindow.cpp \


HEADERS += \
        ResourceManager/shadermanager.h \
        ResourceManager/shadersettings.h \
        ResourceManager/texturemanager.h \
        SceneManager/openglwidget.h \
        ModelManager/modelmanager.h \
        ModelManager/simplemeshdata.h \
        core.h \
        mainwindow.h \

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc

