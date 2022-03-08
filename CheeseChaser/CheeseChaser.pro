QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        activeentity.cpp \
        cat.cpp \
        cheese.cpp \
        entity.cpp \
        game.cpp \
        gamemap.cpp \
        main.cpp \
        mainmenu.cpp \
        passabletile.cpp \
        player.cpp \
        staticmap.cpp \
        tile.cpp \
        unpassabletile.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    activeentity.h \
    cat.h \
    cheese.h \
    entity.h \
    game.h \
    gamemap.h \
    mainmenu.h \
    passabletile.h \
    player.h \
    staticmap.h \
    tile.h \
    unpassabletile.h

OTHER_FILES += "C:\Egyetem\Allamvizsga\CheeseChaserV2022\CheeseChaser\res"

QT += widgets

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    res/cat.png \
    res/cheese.png \
    res/configuration.json \
    res/ground.png \
    res/mouse.png \
    res/static_map_1.txt \
    res/static_map_2.txt \
    res/wall.png

RESOURCES += \
    assets.qrc \
    enviorment.qrc \
    maps.qrc

