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
        greedycat.cpp \
        main.cpp \
        mainmenu.cpp \
        passabletile.cpp \
        player.cpp \
        settings.cpp \
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
    constants.h \
    entity.h \
    game.h \
    gamemap.h \
    greedycat.h \
    mainmenu.h \
    passabletile.h \
    player.h \
    settings.h \
    staticmap.h \
    tile.h \
    unpassabletile.h

QT += widgets \
    concurrent


RESOURCES += \
    assets.qrc \
    enviorment.qrc \
    maps.qrc

