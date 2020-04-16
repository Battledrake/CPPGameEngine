#ifndef MAP
#define MAP

#include <string>
#include "./Constants.h"

class Map {
    public:
    Map(std::string textureId, float scale, int tileSize);
    ~Map();
    void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
    void AddTile(int sourceX, int sourceY, float x, float y, LayerType layer);
    private:
    std::string textureId;
    float scale;
    int tileSize;
};

#endif