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

    bool readOptionsFromJson(const QString fileName = ":/settings/settings.json");

    const QString getSelectedMapName() const;
    void setSelectedMapNameIndex(const unsigned int index);
    const QStringList getAllMapNames() const;

protected:
    static Settings *instance;
    QStringList mapNames;
    unsigned int selectedMapIndex {0};

    Settings();
    ~Settings();
};

#endif // SETTINGS_H
