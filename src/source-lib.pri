
PUBLIC_HEADERS += \
    $$PWD/source.h \
    $$PWD/beam.h \
    $$PWD/beams.h \
    $$PWD/source_global.h \
    $$PWD/encoder.h \
    $$PWD/scan.h \
    $$PWD/driving.h \
    $$PWD/axis.h

PRIVATE_HEADERS += \
    $$PWD/alloter.h \
    $$PWD/source_p.h

SOURCES += \
    $$PWD/source.cpp \
    $$PWD/source_p.cpp \
    $$PWD/beam.cpp \
    $$PWD/beams.cpp \
    $$PWD/alloter.cpp \
    $$PWD/encoder.cpp \
    $$PWD/scan.cpp \
    $$PWD/driving.cpp \
    $$PWD/axis.cpp

phascan {
    PRIVATE_HEADERS += \
        $$PWD/dma.h
    SOURCES += \
        $$PWD/dma.cpp
}

HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS

documentation.files = $$PUBLIC_HEADERS
