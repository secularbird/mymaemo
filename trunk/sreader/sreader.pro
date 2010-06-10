# -------------------------------------------------
# Project created by QtCreator 2010-06-05T16:39:55
# -------------------------------------------------
QT += sql
TARGET = sreader
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    mmm_fontdialog.cpp
HEADERS += mainwindow.h \
    mmm_fontdialog.h
FORMS += mainwindow.ui

# -----------------------------------------------------------------
# Added section
# -----------------------------------------------------------------
unix { 
    # VARIABLES
    isEmpty(PREFIX):PREFIX = /opt/$${TARGET}
    BINDIR = /opt/$${TARGET}/bin
    DEFINES += DATADIR=\"$$DATADIR\" \
        PKGDATADIR=\"$$PKGDATADIR\"
    
    # MAKE INSTALL
    INSTALLS += target
    target.path = $$BINDIR
}
