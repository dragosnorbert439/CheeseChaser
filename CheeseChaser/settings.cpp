#include "settings.h"

Settings *Settings::instance = 0;

Settings *Settings::getInstance()
{
    if(!instance) instance = new Settings;
    return instance;
}

Settings::Settings()
{
}

Settings::~Settings()
{
}

bool Settings::saveSettings(const QString mapName, const QString fileName)
{
    //qDebug() << "Map name: " << mapName;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    file.close();

    //qDebug() << document;
    QJsonObject jsonObject = document.object();
    QJsonValueRef reference = jsonObject.find("map").value();
    QJsonObject saveValue = reference.toObject();
    //saveValue.insert("map", mapName);
    saveValue["map"] = mapName;
    reference = mapName;
    document.setObject(jsonObject);

    //qDebug() << document;

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) return false;
    file.write(document.toJson());
    file.close();

    //qDebug() << "All good. Map name: " << mapName;

    // lastly, update the current map name

    return true;
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

    // json value of map
    QJsonValue selectedMapNameJV = jsonObject.value("map").toString();
    // get all the available static maps (ONLY WITH static_map_N name)
    for (unsigned int i = 1; i < MAX_STATIC_MAPS; ++i)
    {
        if (QFile::exists(STATIC_MAPS_NAME + QString().number(i)))
        {
            mapNames.push_back(STATIC_MAPS_NAME + QString().number(i));
            QFile mapFile(mapNames.last());
            mapFile.open(QIODevice::ReadOnly | QIODevice::Text);
            mapAliasNames.push_back(mapFile.readLine());
            mapFile.close();
        }
        else
        {
            if (i == 1) return false;
            break;
        }
    }

    // check if selected map from settings exists
    if (!mapNames.contains(selectedMapNameJV.toString())) selectedMapNameJV = mapNames.first();
    else selectedMapIndex = mapNames.indexOf(selectedMapNameJV.toString());

    // set initial map name
    initialMapName = selectedMapNameJV.toString();

    return true;
}

const QString Settings::getSelectedMapName() const
{
    return mapNames[selectedMapIndex];
}

void Settings::setSelectedMapNameIndex(const unsigned int index)
{
    selectedMapIndex = index;
}

const QStringList Settings::getAllMapNames() const
{
    return mapAliasNames;
}






