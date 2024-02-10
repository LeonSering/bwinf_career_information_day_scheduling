TARGET = Informationstag

LIBS += libglpk.so

QT += core \
    gui
HEADERS += cVeranstaltung.h \
    cTeilnehmer.h \
    cInformationstag.h \
    cAngebot.h \
    cThread.h \
    QtInformationstag.h
SOURCES += main.cpp \
    cAngebot.cpp \
    cTeilnehmer.cpp \
    cVeranstaltung.cpp \
    cInformationstag.cpp \
    cThread.cpp \
    QtInformationstag.cpp \


FORMS += qtinformationstag.ui
RESOURCES += 

