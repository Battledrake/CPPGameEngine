#ifndef TEXTUREMANAGER
#define TEXTUREMANAGER

#include <SDL2/SDL.h>
#include "../Game.h"

class SDL_Texture;
class SDL_Rect;

class TextureManager {
   public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip);
};

#endif