DEVICE = "PHASCAN"

QT       -= gui

TARGET    = test_source
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += $$DEVICE

target.path = /home/root
INSTALLS += target

SOURCES += main.cpp \
    test_source.cpp

SOURCES += ../source.cpp \
    ../group_source.cpp \
    ../beam_source.cpp \
    ../dma.cpp

HEADERS += ../source_global.h \
    ../source.h \
    ../beam_source.h \
    ../group_source.h \
    ../dma.h \
    test_source.h
