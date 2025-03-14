QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    enemy.cpp \
    fasttower.cpp \
    gamescene.cpp \
    healthbar.cpp \
    main.cpp \
    mainwindow.cpp \
    poisontower.cpp \
    powertower.cpp \
    slowtower.cpp \
    tower.cpp \
    towerbutton.cpp \
    upgradebutton.cpp

HEADERS += \
    ../CSC3002_project_enemy/bullet.h \
    bullet.h \
    enemy.h \
    fasttower.h \
    gamescene.h \
    globals.h \
    healthbar.h \
    mainwindow.h \
    poisontower.h \
    powertower.h \
    slowtower.h \
    tower.h \
    towerbutton.h \
    upgradebutton.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    effectofbullet.qrc \
    res.qrc \
    resource.qrc \
    towernew.qrc

DISTFILES += \
    ../../../../../../../../../../../../../../Desktop/image/c97ed5720d784778bfb19aa8e61eb2e0.png \
    ../GIF/录屏2024-12-03 15.01.08_matting.gif \
    ../GIF/录屏2024-12-03 15.01.08_matting.gif
