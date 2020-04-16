#ifndef ASSETMANAGER
#define ASSETMANAGER

#include <map>
#include <string>

class EntityManager;
class SDL_Texture;

class AssetManager {
   public:
    AssetManager(EntityManager* manager);
    ~AssetManager();
    void ClearData();
    void AddTexture(std::string textureId, const char* filePath);
    SDL_Texture* GetTexture(std::string textureId);

   private:
    EntityManager* manager;
    std::map<std::string, SDL_Texture*> textures;
};

#endif