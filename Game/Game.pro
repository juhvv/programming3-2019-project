TEMPLATE = app
TARGET = CONQUEST

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    objectmanager.cpp \
    gameeventhandler.cpp \
    startwindow.cpp \
    mapwindow.cpp \
    buildings/goldmine.cpp \
    buildings/sawmill.cpp \
    player.cpp \
    ui/graphicsviewport.cpp \
    ui/customgraphicsitem.cpp \
    tiles/graphicstilebase.cpp \
    tiles/foresttileitem.cpp \
    tiles/grasstileitem.cpp \
    ui/customgraphicsscene.cpp \
    ui/tileoverlayitem.cpp \
    units/graphicsunitbase.cpp \
    tiles/watertileitem.cpp \
    tiles/mountaintileitem.cpp \
    gameobjectbase.cpp \
    buildings/gamebuildingbase.cpp \
    unitconstructor.cpp \
    savewindow.cpp \
    savegame.cpp \
    loadwindow.cpp \
    loadgame.cpp

HEADERS += \
    mapwindow.hh \
    objectmanager.hh \
    gameeventhandler.hh \
    startwindow.hh \
    buildings/goldmine.h \
    buildings/sawmill.h \
    player.hh \
    ui/graphicsviewport.h \
    ui/customgraphicsitem.h \
    tiles/graphicstilebase.h \
    tiles/foresttileitem.h \
    tiles/grasstileitem.h \
    ui/customgraphicsscene.h \
    ui/tileoverlayitem.h \
    units/graphicsunitbase.h \
    tiles/watertileitem.h \
    tiles/mountaintileitem.h \
    gameresourcemaps.hh \
    gameobjectbase.h \
    buildings/gamebuildingbase.h \
    unitconstructor.h \
    savewindow.hh \
    savegame.hh \
    loadwindow.hh \
    loadgame.hh

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    startwindow.ui \
    savewindow.ui \
    loadwindow.ui

DISTFILES +=

RESOURCES += \
    game_resources.qrc
