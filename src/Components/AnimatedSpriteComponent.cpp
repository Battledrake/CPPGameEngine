#include "./AnimatedSpriteComponent.h"
#include "../ResourceManagers/AssetManager.h"
#include "../ResourceManagers/TextureManager.h"
#include "./TransformComponent.h"

AnimatedSpriteComponent::AnimatedSpriteComponent() {}

void AnimatedSpriteComponent::Initialize() {
    texture = Game::assetManager->GetTexture("def-image");
    transform = owner->GetComponent<TransformComponent>();
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;
    currentIndex = 0;
    animSpeed = 60;
    SetAnimationFrames();
}

void AnimatedSpriteComponent::SetAnimatedTexture(std::string assetTextureId, bool playOnStart, bool isFixed) {
    texture = Game::assetManager->GetTexture(assetTextureId);
    SetAnimationFrames();
    isPlaying = playOnStart;
    this->isFixed = isFixed;
}

void AnimatedSpriteComponent::SetAnimationFrames() {
    animations.clear();

    int texW;
    int texH;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    for (int i = 0; i < texH / srcRect.h; i++) {
        Animation animData = Animation(i, texW / srcRect.w);
        animations.emplace(i, animData);
    }
}

void AnimatedSpriteComponent::SetAnimationSpeed(int animSpeed) {
    this->animSpeed = animSpeed;
}

void AnimatedSpriteComponent::Play(unsigned int animIndex, int animSpeed) {
    currentIndex = animIndex;
    this->animSpeed = animSpeed;
    isPlaying = true;
}

void AnimatedSpriteComponent::Pause() {
    isPlaying = false;
}

void AnimatedSpriteComponent::Resume() {
    if (!isPlaying)
        isPlaying = true;
}

void AnimatedSpriteComponent::Stop() {
    isPlaying = false;
    animTimer = 0;
}

void AnimatedSpriteComponent::Update(float deltaTime) {
    if (isPlaying) {
        animTimer += deltaTime * 1000;
        srcRect.x = srcRect.w * static_cast<int>((static_cast<int>(animTimer) / animSpeed) % animations.at(currentIndex).numFrames);
    }
    srcRect.y = currentIndex * transform->height;
    destRect.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
    destRect.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
}

void AnimatedSpriteComponent::Render() {
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
}