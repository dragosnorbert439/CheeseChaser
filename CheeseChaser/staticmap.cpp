#include "staticmap.h"

StaticMap::StaticMap(QGraphicsScene* scene) : GameMap()
{
    gameScene = scene;
    setMap();
}

StaticMap::~StaticMap()
{
    /*for (auto& entity : *entities)
    {
        delete entity;
    }*/
}

void StaticMap::setMap()
{
    QFile file(":/staticmap/static_map_2");
    QString line;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "StaticMap::setMap::ERROR::Could not open text file!";
        return;
    }

    QTextStream in(&file);
    QStringList fields;
    line = in.readLine();
    fields = line.split(" ");
    if (!(setCols(fields[1].toInt()) && setRows(fields[0].toInt())))
    {
        qDebug() << "StaticMap::setMap::ERROR::Could not set map dimensions!";
        return;
    }

    // [EN] the map
    bool playerIsPlaced = false;
    map = new Tile**[rows];
    for (int i = 0; i < rows; ++i) map[i] = new Tile*[cols];

    for (int i = 0; i < rows; ++i)
    {
        line = in.readLine();
        fields = line.split(" ");

        for (int j = 0; j < cols; ++j)
        {
            switch (fields[j].toInt())
            {
            case 0: // empty tile
                map[i][j] = new PassableTile(j, i);
                break;
            case 1: // wall
                map[i][j] = new UnpassableTile(j, i);
                break;
            case 2: // player
                map[i][j] = new PassableTile(j, i);
                if (!playerIsPlaced)
                {
                    player = new Player(this, j, i);
                    entities->append(player);
                    playerIsPlaced = true;
                }
                break;
            case 3: // cheese
                map[i][j] = new PassableTile(j, i);
                entities->append(new Cheese(j, i));
                break;
            case 4: // cat
                map[i][j] = new PassableTile(j, i);
                entities->append(new Cat(this, j, i));
                catThreadAnswers.append(&static_cast<Cat*>(entities->last())->done);
                break;
            default:
                qDebug() << "StaticMap::setMap::ERROR::Something went wrong!";
            }

            gameScene->addItem(map[i][j]);
        }
    }

    file.close();

    for (auto& entity : *entities)
    {
        gameScene->addItem(entity);
    }
}

void StaticMap::setScene(QGraphicsScene *scene)
{
    gameScene = scene;
}
