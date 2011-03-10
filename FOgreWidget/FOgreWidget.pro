#-------------------------------------------------
#
# Project created by QtCreator 2011-03-10T17:04:44
#
#-------------------------------------------------

QT       += core gui

TARGET = FOgreWidget

unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
}
win32 {
    # You may need to change this include directory
    OGREHOME = C:\Users\Jash\Documents\OgreSDK_vc10_v1-7-2
    LIBS += -L$$OGREHOME\\boost_1_42\\lib
    Release:LIBS += -L$$OGREHOME\\lib\\release
    Debug:LIBS += -L$$OGREHOME\\lib\\debug
    INCLUDEPATH += $$OGREHOME\\include
    INCLUDEPATH += $$OGREHOME\\include\\OIS
    INCLUDEPATH += $$OGREHOME\\include\\OGRE
    INCLUDEPATH += $$OGREHOME\\boost_1_42
}
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
    LIBS *= -lOgreMain_d -lOIS_d
}
CONFIG(release, debug|release):LIBS *= -lOgreMain -lOIS

SOURCES += main.cpp\
        fogrewidget.cpp

HEADERS  += fogrewidget.h

FORMS    += fogrewidget.ui
