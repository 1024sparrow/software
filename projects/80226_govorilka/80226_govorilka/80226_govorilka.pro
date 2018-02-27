DEFINES += CONSOLE_DEBUG

equals(QT_MAJOR_VERSION, 4) {
        DEFINES += QT4_USING
}
QT += xml

include(../include/boris_h/makeapp_base.pri)
TARGET = 80226_govorilka
LIBS += \
    -lboris

SOURCES += \
    main.cpp \
    gameplay.cpp \
    display.cpp

HEADERS += \
    gameplay.h \
    display.h
