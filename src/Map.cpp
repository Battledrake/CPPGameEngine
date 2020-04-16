#include <fstream>
#include "./Map.h"
#include "./Game.h"
#include "./EntityManager.h"
#include "./Components/TileComponent.h"

extern EntityManager manager;
Map::Map(std::string textureId, float scale, int tileSize)
{
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
    // TODO: read the map tile definitions from the .map file
    std::fstream mapFile;
    mapFile.open(filePath);

    for(int y = 0; y < mapSizeY; ++y) {
        for(int x = 0; x < mapSizeX; ++x) {
            char ch;
            mapFile.get(ch);
            int srcRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = atoi(&ch) * tileSize;
            AddTile(srcRectX, srcRectY, x * (tileSize * scale), y * (tileSize * scale), LayerType::TILEMAP_LAYER);
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int srcRectX, int srcRectY, float x, float y, LayerType layer)
{
    //TODO: Add a new tile entity in the game scene
    Entity& newTile(manager.AddEntity("Tile", layer));
    newTile.AddComponent<TileComponent>(srcRectX, srcRectY, x, y, tileSize, scale, textureId);
}