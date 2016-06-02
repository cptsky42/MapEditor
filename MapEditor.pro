QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app

macx {
CONFIG += ppc ppc64 x86 x86_64
}

SOURCES += \
    src/main.cpp\
    src/ui/src/mainwindow.cpp \
    src/editor/src/gamemap.cpp

HEADERS += \
    src/ui/include/mainwindow.h \
    src/editor/include/gamemap.h \
    src/common/include/common.h \
    src/common/include/arch.h \
    src/common/include/endian.h \
    src/common/include/err.h \
    src/common/include/types.h \
    src/common/include/log.h

RESOURCES += \
    res/mainwindow.qrc

FORMS += \
    src/ui/form/mainwindow.ui

INCLUDEPATH += \
    src/ui/include \
    src/editor/include \
    src/common/include

# WIN32 stuff
win32 {
OTHER_FILES += \
    res/win32.rc

RC_FILE += \
    res/win32.rc

QMAKE_CXXFLAGS += -D_CRT_SECURE_NO_WARNINGS
}

# Mac OS X stuff
macx {
OTHER_FILES += \
    res/darwin.plist

ICON += \
    res/icon.icns

QMAKE_INFO_PLIST = res/darwin.plist
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.5.8

# START: qmake 4.8.4 workaround
QMAKE_INFO_PLIST_OUT = MapEditor.app/Contents/Info.plist

missing.target = dummy
missing.depends = MapEditor.app/Contents/Info.plist MapEditor.app/Contents/Resources/icon.icns

QMAKE_EXTRA_TARGETS = missing
QMAKE_PRE_LINK = make dummy
# END
}
