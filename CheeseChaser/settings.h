#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDir>
#include <QFileDialog>
#include <QStringList>

#include "constants.h"

class Settings
{
public:
    static Settings* getInstance();
    //void deleteInstance(); /// TODO

    Settings(Settings &other) = delete;
    void operator=(const Settings &other) = delete;

    bool readOptionsFromJson(const QString fileName = JSON_SETTINGS_FILE);
    bool saveSettings(const QString mapName, const QString fileName = JSON_SETTINGS_FILE);

    const QString getSelectedMapName() const;
    void setSelectedMapNameIndex(const unsigned int index);
    const QStringList getAllMapNames() const;

protected:
    static Settings *instance;
    QStringList mapNames;
    QStringList mapAliasNames;
    QString initialMapName { STATIC_MAPS_NAME + "1" };
    unsigned int selectedMapIndex {0};

    Settings();
    ~Settings();
};

#endif // SETTINGS_H
