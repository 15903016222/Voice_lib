
PUBLIC_HEADERS += \
    $$PWD/beam_group.h \
    $$PWD/beam.h \
    $$PWD/source.h \
    $$PWD/source_global.h

PRIVATE_HEADERS += \
    $$PWD/alloter.h

SOURCES += \
    $$PWD/source.cpp \
    $$PWD/beam.cpp \
    $$PWD/alloter.cpp \
    $$PWD/beam_group.cpp


phascan {
    PRIVATE_HEADERS += \
        $$PWD/dma.h
    SOURCES += \
        $$PWD/dma.cpp
}

HEADERS += $$PUBLIC_HEADERS $$PRIVATE_HEADERS

documentation.files = $$PUBLIC_HEADERS
