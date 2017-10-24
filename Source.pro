#-------------------------------------------------
#
# Project created by QtCreator 2016-11-30T18:45:32
#
#-------------------------------------------------

#------------------------------------------------------------
# Support Devices:
#  pcunix     : Qt5.6.0, gcc.4.8.4
#  pcwin      : Qt5.7.0, MSVC2015
#  phascan    : Qt4.8.6, arm-angstrom-linux-gnueabi-gcc.4.5.3
#  phascan_ii : Qt5.4.3, arm-phytec-linux-gnueabi-gcc.4.9.2
#-------------------------------------------------------------
win32 {
    DEVICE = pcwin
}
unix {
    DEVICE = pcunix

    linux-arm-g++ {
    DEVICE = phascan
    }

    linux-oe-g++ {
    DEVICE = phascan_ii
    }
}

CONFIG += SOURCE_LIBRARY $$DEVICE
DEFINES += $$upper($$DEVICE)

QT       -= gui

TEMPLATE = lib

VERSION = $$system(git describe --tags `git rev-list --tags --max-count=1`)


TARGET = source-$$DEVICE
CONFIG(debug, debug|release) {
      TARGET = $$join(TARGET,,,"-debug")
}

include($$PWD/src/source-lib.pri)

target.path = /lib
documentation.path  = /

INSTALLS += target documentation
