#ifndef SPRITECOMPONENT
#define SPRITECOMPONENT

#include <SDL2/SDL.h>
#include <memory>
#include "../ResourceManagers/AssetManager.h"
#include "../ResourceManagers/TextureManager.h"
#include "./TransformComponent.h"

class SpriteComponent : public Component {
   public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(std::string assetTextureId, bool isFixed = false) {
        this->isFixed = isFixed;
        SetTexture(assetTextureId);
    }

    void SetTexture(std::string assetTextureId) {
        texture = Game::assetManager->GetTexture(assetTextureId);
    }

    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void Update(float deltaTime) override {
        destRect.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
        destRect.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }

    void Render() override {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

   private:
    std::shared_ptr<TransformComponent> transform;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    bool isFixed;
};
#endif