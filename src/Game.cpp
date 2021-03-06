#include "./Game.h"
#include <iostream>
#include <memory>
#include "./Map.h"
#include "./Constants.h"
#include "../lib/glm/glm.hpp"
#include "./Components/SpriteComponent.h"
#include "./Components/TransformComponent.h"
#include "./Components/AnimatedSpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./ResourceManagers/AssetManager.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

Game::Game() { this->isRunning = false; }

Game::~Game() {}

bool Game::IsRunning() const { return this->isRunning; }

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window =
        SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         width, height, SDL_WINDOW_BORDERLESS);
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
#include "./Components/TransformComponent.h"
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

Entity& player(manager.AddEntity("Chopper", PLAYER_LAYER));

void Game::LoadLevel(int levelNumber) {
    /* Start including new assets to the assetmanager list */
    assetManager->AddTexture("def-image", std::string("./assets/images/collision-texture.png").c_str());
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());

    map = new Map("jungle-tiletexture", 2.0f, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

    Entity& tankEntity(manager.AddEntity("Tank", ENEMY_LAYER));
    tankEntity.AddComponent<TransformComponent>(0, 0, 0, 0, 32, 32, 1.0f);
    tankEntity.AddComponent<SpriteComponent>("tank-image");

    player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1.0f);
    std::shared_ptr<AnimatedSpriteComponent> chopAnim = player.AddComponent<AnimatedSpriteComponent>();
    chopAnim->SetAnimatedTexture("chopper-image", true);
    player.AddComponent<KeyboardControlComponent>("w", "d", "s", "a", "space");

    Entity& radarEntity(manager.AddEntity("Radar", UI_LAYER));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    std::shared_ptr<AnimatedSpriteComponent> radarAnim = radarEntity.AddComponent<AnimatedSpriteComponent>();
    radarAnim->SetAnimatedTexture("radar-image", true, true);
    radarAnim->SetAnimationSpeed(150);
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
            break;
        default:
            break;
    }
}

void Game::Update() {
    // Wait until fps designated ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

    // Delta time is the difference in ticks from the last frame converted to
    // seconds;
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a max value
    deltaTime = (deltaTime > 0.05f) ? 0.0f : deltaTime;

    // Total amount of ticks occurred since SDL_Init was called set to be used in
    // next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);

    HandleCameraMovement();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
    std::shared_ptr<TransformComponent> mainPlayerTransform = player.GetComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}