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

HEADERS += \
    mapwindow.hh \
    objectmanager.hh \
    gameeventhandler.hh \
    startwindow.hh \
    buildings/goldmine.h \
    buildings/sawmill.h \
    player.hh \
    ui/graphicsviewport.h \


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
    startwindow.ui

DISTFILES +=

RESOURCES += \
    game_resources.qrc
