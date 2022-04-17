#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDir>

class Settings
{
public:
    static Settings* getInstance();
    void deleteInstance();

    Settings(Settings &other) = delete;
    void operator=(const Settings &other) = delete;

    bool readOptionsFromJson(const QString fileName = ":/settings/settings.json");

protected:
    static Settings *instance;

    Settings();
    ~Settings();
};

#endif // SETTINGS_H
