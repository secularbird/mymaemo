CONFIG += qt

TARGET = sreader

# keep the tree clean
DESTDIR = build
OBJECTS_DIR = build
MOC_DIR = src/.tmp
UI_DIR = src/

# In Eclipse, "clean" removes binaries too.  This is also needed to work around timestamp
# issues between host and VM in ESbox.
QMAKE_CLEAN += $$DESTDIR/sreader

# Instead of building separate Debug/Optimized targets, you can do this:
# CONFIG += debug_and_release
#
# CONFIG(debug, debug|release) {
#     TARGET = sreader-debug
# } else {
#     TARGET = sreader
# }

HEADERS     = src/mainwindow.h \
			  src/mmm_settingdialog.h \
			  src/mmm_configuremanager.h \
			  src/system.h
SOURCES     = src/main.cpp \
              src/mainwindow.cpp \
              src/mmm_settingdialog.cpp \
              src/mmm_configuremanager.cpp \
              src/system.cpp
              
FORMS		= uiform/mainwindow.ui 

# TEMPLATE = app
# DESTDIR = /path/to/installation
# DEFINES += MACRO_1 ... 

# CONFIG += link_pkgconfig
# PKGCONFIG += ogg dbus-1

# install
target.path = /opt/sreader/bin

desktop.path = /usr/share/applications/hildon
desktop.files += resource/sreader.desktop

icons32.files += resource/32X32/sreader.png
icons32.path = /usr/share/icons/hicolor/32x32/apps/

#32X32icons.path = /usr/share/icons/hicolor/scalable/apps/

INSTALLS += target desktop icons32

