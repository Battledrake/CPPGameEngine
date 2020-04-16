#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_events.h>

class SDL_Renderer;
class SDL_Window;
class AssetManager;

class Game {
   public:
    Game();
    ~Game();
    bool IsRunning() const;
    static SDL_Renderer *renderer;
    static AssetManager *assetManager;
    static SDL_Event event;
    static SDL_Rect camera;
    void LoadLevel(int levelNumber);
    void HandleCameraMovement();
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
 
   private:
    int ticksLastFrame;
    bool isRunning;
    SDL_Window *window;
};

#endif