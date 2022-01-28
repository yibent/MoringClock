QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    App/BasePage.cpp \
    App/BreathPage.cpp \
    App/BreathPage_1.cpp \
    App/ClockPage.cpp \
    App/MainPage.cpp \
    App/MeditationPage.cpp \
    App/MusicPostPage.cpp \
    Engine/Action.cpp \
    Engine/Audio.cpp \
    Engine/EventDispatcher.cpp \
    Engine/FileString.cpp \
    Engine/ImagePool.cpp \
    Engine/Label.cpp \
    Engine/Layer.cpp \
    Engine/Node.cpp \
    Engine/Ref.cpp \
    Engine/Scene.cpp \
    Engine/Schedule.cpp \
    Engine/Sprite.cpp \
    Engine/UI.cpp \
    Engine/Vec2.cpp \
    LightControl/myLight.cpp \
    LightControl/rgb2hsv.cpp \
    MyApp.cpp \
    main.cpp \
    Director.cpp

HEADERS += \
    App/BasePage.h \
    App/BreathPage.h \
    App/BreathPage_1.h \
    App/ClockPage.h \
    App/MainPage.h \
    App/MeditationPage.h \
    App/MusicPostPage.h \
    App/MyDefault.h \
    Director.h \
    Engine/Action.h \
    Engine/Audio.h \
    Engine/Default.h \
    Engine/EventDispatcher.h \
    Engine/FileString.h \
    Engine/ImagePool.h \
    Engine/Label.h \
    Engine/Layer.h \
    Engine/Node.h \
    Engine/Ref.h \
    Engine/Scene.h \
    Engine/Schedule.h \
    Engine/Sprite.h \
    Engine/UI.h \
    Engine/Vec2.h \
    GlobalDef.h \
    LightControl/myLight.h \
    LightControl/pwm.h \
    LightControl/rgb2hsv.h \
    LightControl/rpihw.h \
    LightControl/ws2811.h \
    MyApp.h

FORMS += \
    Director.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

unix:!macx: LIBS += -L$$PWD/LightControl/ -lws2811

INCLUDEPATH += $$PWD/LightControl
DEPENDPATH += $$PWD/LightControl

unix:!macx: PRE_TARGETDEPS += $$PWD/LightControl/libws2811.a

DISTFILES +=
