#-------------------------------------------------
#
# Project created by QtCreator 2010-06-05T16:39:55
#
#-------------------------------------------------

QT       += sql

TARGET = sreader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

# -----------------------------------------------------------------
#                      Added section
# -----------------------------------------------------------------
unix {
#VARIABLES
    isEmpty(PREFIX) {
            PREFIX = /opt/$${TARGET}
    }
BINDIR = /opt/$${TARGET}/bin

DEFINES += DATADIR=\"$$DATADIR\" PKGDATADIR=\"$$PKGDATADIR\"

#MAKE INSTALL

INSTALLS += target 

target.path =$$BINDIR

#desktop.path = $$DATADIR/applications/hildon
#desktop.files += $${TARGET}.desktop

#image.path = $$DATADIR
#desktop.files += $${TARGET}.png

}
