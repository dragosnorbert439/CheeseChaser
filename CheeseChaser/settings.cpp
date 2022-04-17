#include "settings.h"

Settings *Settings::instance = 0;

Settings *Settings::getInstance()
{
    if(!instance) instance = new Settings;
    return instance;
}

void Settings::deleteInstance()
{
    this->~Settings();
}

Settings::Settings()
{
    qDebug() << "Settings private constructor called";
}

Settings::~Settings()
{
    qDebug() << "Settings destructor called;";
}

bool Settings::readOptionsFromJson(QString fileName)
{
    // open and read from the file, then close it
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QString val = file.readAll();
    file.close();

    // convert qstring to qjsondocument
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if (document.isEmpty() || document.isNull()) return false;

    // json object from document
    QJsonObject jsonObject = document.object();
    qDebug() << jsonObject;

    //
    QString path = QDir::temp().absoluteFilePath(":/staticmap/static_map_1");
    qDebug() << path;

    return true;
}






