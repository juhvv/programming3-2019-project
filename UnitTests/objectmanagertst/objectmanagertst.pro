QT += testlib
QT += widgets
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += -L$$OUT_PWD/../../Course/CourseLib/ -lCourseLib

INCLUDEPATH += $$PWD/../../Course/CourseLib \
    $$PWD/../../Game/
DEPENDPATH += $$PWD/../../Course/CourseLib \
    $$PWD/../../Game/

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/libCourseLib.a

HEADERS += \
    ../../Game/buildings/base.h \
    ../../Game/buildings/gamebuildingbase.h \
    ../../Game/buildings/gamefarm.h \
    ../../Game/buildings/gameoutpost.h \
    ../../Game/buildings/goldmine.h \
    ../../Game/buildings/sawmill.h \
    ../../Game/tiles/foresttileitem.h \
    ../../Game/tiles/graphicstilebase.h \
    ../../Game/tiles/grasstileitem.h \
    ../../Game/tiles/mountaintileitem.h \
    ../../Game/tiles/swamptileitem.h \
    ../../Game/tiles/watertileitem.h \
    ../../Game/ui/customgraphicsitem.h \
    ../../Game/ui/customgraphicsscene.h \
    ../../Game/ui/graphicsviewport.h \
    ../../Game/ui/tileoverlayitem.h \
    ../../Game/units/builder.h \
    ../../Game/units/graphicsunitbase.h \
    ../../Game/units/scout.h \
    ../../Game/units/worker.h \
    ../../Game/gameeventhandler.hh \
    ../../Game/gameobjectbase.h \
    ../../Game/gameresourcemaps.hh \
    ../../Game/loadgame.hh \
    ../../Game/loadwindow.hh \
    ../../Game/mapwindow.hh \
    ../../Game/objectmanager.hh \
    ../../Game/player.hh \
    ../../Game/savegame.hh \
    ../../Game/savewindow.hh \
    ../../Game/startwindow.hh \
    ../../Game/unitconstructor.h

SOURCES +=  tst_objectmanager.cpp \
    ../../Game/buildings/base.cpp \
    ../../Game/buildings/gamebuildingbase.cpp \
    ../../Game/buildings/gamefarm.cpp \
    ../../Game/buildings/gameoutpost.cpp \
    ../../Game/buildings/goldmine.cpp \
    ../../Game/buildings/sawmill.cpp \
    ../../Game/tiles/foresttileitem.cpp \
    ../../Game/tiles/graphicstilebase.cpp \
    ../../Game/tiles/grasstileitem.cpp \
    ../../Game/tiles/mountaintileitem.cpp \
    ../../Game/tiles/swamptileitem.cpp \
    ../../Game/tiles/watertileitem.cpp \
    ../../Game/ui/customgraphicsitem.cpp \
    ../../Game/ui/customgraphicsscene.cpp \
    ../../Game/ui/graphicsviewport.cpp \
    ../../Game/ui/tileoverlayitem.cpp \
    ../../Game/units/builder.cpp \
    ../../Game/units/graphicsunitbase.cpp \
    ../../Game/units/scout.cpp \
    ../../Game/units/worker.cpp \
    ../../Game/gameeventhandler.cpp \
    ../../Game/gameobjectbase.cpp \
    ../../Game/loadgame.cpp \
    ../../Game/loadwindow.cpp \
    ../../Game/mapwindow.cpp \
    ../../Game/objectmanager.cpp \
    ../../Game/player.cpp \
    ../../Game/savegame.cpp \
    ../../Game/savewindow.cpp \
    ../../Game/startwindow.cpp \
    ../../Game/unitconstructor.cpp

FORMS += \
    ../../Game/endwindow.ui \
    ../../Game/loadwindow.ui \
    ../../Game/mapwindow.ui \
    ../../Game/savewindow.ui \
    ../../Game/startwindow.ui
