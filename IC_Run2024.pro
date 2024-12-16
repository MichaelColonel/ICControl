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
#    CREATE_ROOT_DICT_FOR_CLASSES  = ${HEADERS} MyParticle.h MyDetector.h MyEvent.h ShowerMain.h
#    CREATE_ROOT_DICT_FOR_CLASSES *= ${HEADERS} RSLinkDef.h
}

#INCLUDEPATH += /usr/local/GATE/include/root

#LIBS += -L/usr/local/GATE/lib/root -lCore -lCint -lRIO -lNet -lHist \
#        -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix \
#        -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic

# With C++11 support
greaterThan( QT_MAJOR_VERSION, 4) {
    QT += widgets serialport
    CONFIG += c++11
} else {
    QMAKE_CXXFLAGS += -std=c++11
    CONFIG += serialport
}

TARGET = IC_Run2024

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    acquisitionthread.cpp \
    canvas.cpp

HEADERS  += mainwindow.h \
    acquisitionthread.h \
    canvas.h

FORMS    += mainwindow.ui


unix {
#    CONFIG += link_pkgconfig
#    PKGCONFIG += open62541
#    LIBS += -lftd2xx
}

win32 {
    LIBS += -L$$PWD/../FTDI_DriverNew/i386/ -lftd2xx
    INCLUDEPATH += C:\root\include
    INCLUDEPATH += $$PWD/../FTDI_DriverNew
}

#RESOURCES += BeamComposition.qrc

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
    Chip2.7.json

#TRANSLATIONS += BeamComposition_ru.ts
