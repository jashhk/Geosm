TEMPLATE = app
TARGET = OgreQtProject

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

HEADERS       = mainwindow.h \
    Input.h \
    Result.h \
    cal.h \
    MyThread.h \
    QItemPanel_p.h \
    QItemPanel.h \
    helpdialog.h \
    mainwindow_p.h \
    ogreview.h
SOURCES       = main.cpp \
                mainwindow.cpp \
    cal.cpp \
    QItemPanel.cpp \
    helpdialog.cpp \
    ogreview.cpp
#! [0]
RESOURCES     = application.qrc
#! [0]

# install
target.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/application
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS application.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/application
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)

FORMS +=
