#ifndef TILECOMPONENT
#define TILECOMPONENT

#include <SDL2/SDL.h>
#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../ResourceManagers/AssetManager.h"
#include "../ResourceManagers/TextureManager.h"
#include "./Component.h"

class TileComponent : public Component {
   public:
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    glm::vec2 position;

    TileComponent(int srcRectX, int srcRectY, float x, float y, int tileSize, float tileScale, std::string assetTextureId) {
        texture = Game::assetManager->GetTexture(assetTextureId);

        srcRect.x = srcRectX;
        srcRect.y = srcRectY;
        srcRect.w = tileSize;
        srcRect.h = tileSize;

        destRect.x = x;
        destRect.y = y;
        destRect.w = tileSize * tileScale;
        destRect.h = tileSize * tileScale;

        position.x = x;
        position.y = y;
    }

    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    void Update(float deltaTime) override {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    void Render() {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
#endif