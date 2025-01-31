#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T11:21:43
#
#-------------------------------------------------

QT += core gui

CONFIG += qt warn_on thread

!exists ($(ROOTSYS)/include/rootcint.pri) {
    message (The Rootcint.pri was not found)
}
exists ($(ROOTSYS)/include/rootcint.pri) {
    include ($(ROOTSYS)/include/rootcint.pri)
}

# With C++11 support
greaterThan( QT_MAJOR_VERSION, 4) {
    QT += widgets serialport
    CONFIG += c++11
} else {
    QMAKE_CXXFLAGS += -std=c++11
    CONFIG += serialport
}

TARGET = ICControl

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    canvas.cpp

HEADERS  += mainwindow.h \
    canvas.h

FORMS    += mainwindow.ui


unix {
}

win32 {
    LIBS += -L$$PWD/../FTDI_DriverNew/i386/ -lftd2xx
    INCLUDEPATH += C:\root\include
    INCLUDEPATH += $$PWD/../FTDI_DriverNew
}

#RESOURCES += ICControl.qrc

DISTFILES += ChipsPositions.json \
    Chip1.2.json \
    Chip1.3.json \
    Chip1.4.json \
    Chip1.5.json \
    Chip1.8.json \
    Chip1.11.json \
    Chip2.1.json \
    Chip2.2.json \
    Chip2.4.json \
    Chip2.5.json \
    Chip2.6.json \
    Chip2.7.json \
    Chip2.8.json \
    Chip6.x.json

#TRANSLATIONS += ICControl_ru.ts
