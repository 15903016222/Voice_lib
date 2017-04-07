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
    LIBS += -lX11 -lXtst

    linux-arm-g++ {
    DEVICE = phascan
    }

    linux-oe-g++ {
    DEVICE = phascan_ii
    }
}

CONFIG += $$DEVICE
DEFINES += $$upper($$DEVICE)

QT       -= gui

TARGET    = test_source
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

target.path = /home/root
INSTALLS += target

HEADERS += \
    test_source.h

SOURCES += \
    main.cpp \
    test_source.cpp

include($$PWD/../src/source-lib.pri)
INCLUDEPATH += $$PWD/../src/
