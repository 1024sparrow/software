equals(QT_MAJOR_VERSION, 5) {
        QT += multimedia
}
equals(QT_MAJOR_VERSION, 4) {
        DEFINES += QT4_USING
        QT += phonon
}

QT += xml sql core widgets sql multimedia

include(boris_h/makelib_base.pri)
DEFINES += BORIS_MAKE_DLL
#DEFINES += CONSOLE_DEBUG
TARGET = boris

HEADERS += \
    boris_h/debug.h \
    boris_h/btr.h \
    boris_h/dialog.h \
    boris_h/labeltextmanupulator.h \
    boris_h/musicplayer.h \
    boris_h/archiever/archiever.h \
    boris_h/xml_driven/tablemodelcolumnsextensible.h \
    boris_h/xml_driven/tablemodelcolumnsextension.h \
    boris_h/xml_driven/xmldebugwidget.h \
    boris_h/xml_driven/xmldelegate.h \
    boris_h/xml_driven/xmldelegateplugin.h \
    boris_h/xml_driven/xmlpublisher.h \
    boris_h/xml_driven/xmlstring.h \
    boris_h/xml_driven/xmlsubscriber.h \
    boris_h/xml_driven/xmlundoredo.h \
    xml_driven/private/xmldelegateprivate.h \
    musicplayer_p.h \
    musicplayer_p_qt4.h \
    musicplayer_p_qt5.h \
    sqlite_debug/sqlitetableswidget.h \
    sqlite_debug/sqlitetester.h \
    boris_h/sqlitedebugwidget.h \
    boris_h/xml_driven/xmllistwidget.h \
    xml_driven/private/xmllistwidgetprivatemodel.h \
    xml_driven/private/xmllistwidgetprivate.h

SOURCES += \
    dialog.cpp \
    labeltextmanupulator.cpp \
    archiever/archiever.cpp \
    xml_driven/tablemodelcolumnsextensible.cpp \
    xml_driven/tablemodelcolumnsextension.cpp \
    xml_driven/xmldebugwidget.cpp \
    xml_driven/xmldelegate.cpp \
    xml_driven/xmldelegateplugin.cpp \
    xml_driven/xmlpublisher.cpp \
    xml_driven/xmlsubscriber.cpp \
    xml_driven/private/xmldelegateprivate.cpp \
    musicplayer.cpp \
    musicplayer_p.cpp \
    musicplayer_p_qt4.cpp \
    musicplayer_p_qt5.cpp \
    sqlite_debug/sqlitetableswidget.cpp \
    sqlite_debug/sqlitetester.cpp \
    sqlite_debug/sqlitedebugwidget.cpp \
    xml_driven/xmlundoredo.cpp \
    xml_driven/xmllistwidget.cpp \
    xml_driven/private/xmllistwidgetprivatemodel.cpp \
    xml_driven/private/xmllistwidgetprivate.cpp

RESOURCES += \
    boris.qrc
