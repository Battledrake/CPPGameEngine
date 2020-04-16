#ifndef ANIMATEDSPRITECOMPONENT
#define ANIMATEDSPRITECOMPONENT

#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include "./Component.h"

class TransformComponent;

struct Animation {
    unsigned int startIndex;
    unsigned int numFrames;
    Animation(unsigned int startIndex, unsigned int numFrames) {
        this->startIndex = startIndex;
        this->numFrames = numFrames;
    }
};

class AnimatedSpriteComponent : public Component {
   public:
    AnimatedSpriteComponent();

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    void Initialize() override;
    void SetAnimatedTexture(std::string assetTextureId, bool playOnStart = false, bool isFixed = false);
    void SetAnimationSpeed(int animSpeed);
    void Play(unsigned int animIndex, int animSpeed = 60);
    void Pause();
    void Resume();
    void Stop();
    void Update(float deltaTime) override;
    void Render() override;

   private:
    void SetAnimationFrames();

    std::shared_ptr<TransformComponent> transform;
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    bool isPlaying;
    unsigned int currentIndex;
    int animSpeed;
    float animTimer;
    bool isFixed;
    std::map<unsigned int, Animation> animations;
};

#endif