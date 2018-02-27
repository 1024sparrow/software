equals(QT_MAJOR_VERSION, 5) {
        QT += core widgets
}

LIBS += -L../bin
INCLUDEPATH += \
                ../include \
                ./tmp/moc
DESTDIR = ../bin

MOC_DIR +=  tmp/moc
RCC_DIR +=  tmp/rcc
OBJECTS_DIR += tmp/obj
#QMAKE_DISTCLEAN += tmp/moc/* tmp/rcc/* tmp/obj/*
