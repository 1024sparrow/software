equals(QT_MAJOR_VERSION, 5) {
        QT += core widgets multimedia
}

TEMPLATE = lib

DESTDIR = ../bin

MOC_DIR +=  tmp/moc
RCC_DIR +=  tmp/rcc
OBJECTS_DIR += tmp/obj
INCLUDEPATH +=  \
                . \
                ../include \
                ./tmp/moc
#QMAKE_DISTCLEAN += tmp/moc/* tmp/rcc/* tmp/obj/*
LIBS += -L../bin
