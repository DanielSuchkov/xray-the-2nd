TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    renderer.cpp \
    framebuffer.cpp \
    geometrymanager.cpp

LIBS += -lSDL2

HEADERS += \
    renderer.h \
    framebuffer.h \
    utils.h \
    geometrymanager.h
