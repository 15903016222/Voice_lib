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
    ../beam.cpp \
    ../beam_group.cpp \
    ../alloter.cpp \
    ../dma.cpp

HEADERS += ../source_global.h \
    ../source.h \
    ../beam.h \
    ../beam_group.h \
    ../alloter.h \
    ../dma.h \
    test_source.h
