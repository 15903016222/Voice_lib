#-------------------------------------------------
#
# Project created by QtCreator 2016-11-30T18:45:32
#
#-------------------------------------------------

#------------------------------------------------------------
# Support Devices:
#  PC_UNIX    : Qt5.6.0, gcc.4.8.4
#  PC_WIN     : Qt5.7.0, MSVC2015
#  PHASCAN    : Qt4.8.6, arm-angstrom-linux-gnueabi-gcc.4.5.3
#  PHASCAN_II : Qt5.4.3, arm-phytec-linux-gnueabi-gcc.4.9.2
#-------------------------------------------------------------

QT       -= gui

TARGET = Source
TEMPLATE = lib

VERSION = $$system(git describe --tags `git rev-list --tags --max-count=1`)

win32 {
    DEVICE = PC_WIN
    TARGET = Source_Win

}

else: linux-oe-g++ {
    DEVICE = PHASCAN_II
    TARGET = Source_Phascan_II
}

else: linux-arm-g++ {
    DEVICE = PHASCAN
    TARGET = Source_Phascan
    SOURCES += dma.cpp
    HEADERS += dma.h
}

else: linux-g++ {
    DEVICE = PC_UNIX
    TARGET = Source_Linux
}

CONFIG(debug, debug|release) {
      TARGET = $$join(TARGET,,,_debug)
}

DEFINES += SOURCE_LIBRARY $$DEVICE

SOURCES += source.cpp \
    beam.cpp \
    alloter.cpp \
    beam_group.cpp

HEADERS +=\
        source_global.h \
    source.h \
    beam.h \
    alloter.h \
    beam_group.h


target.path = /lib
documentation.path  = /
documentation.files = beam_group.h beam.h source.h source_global.h

INSTALLS += target documentation
