//
//  Game.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-10.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "GameTexture.hpp"
#include "EntityManager.hpp"
#include "IEntity.hpp"
#include <vector>
#include "RenderSystem.hpp"
#include "MovementSystem.hpp"
#include "PlayerControlSystem.hpp"
#include "CollisionSystem.hpp"
#include "CollisionHandlerSystem.hpp"
#include "AnimationSystem.hpp"
#include "MessageInterface.hpp"
#include "TextureManager.hpp"
#include "MapManager.hpp"
#include "StateManager.hpp"
#include "DirectionSystem.hpp"
#include "StatusEffectHandler.hpp"

class Game : public MessageInterface {
public:
    //Initialize the game object
    Game();

    //Run the game
    void run();

private:
    //Initialize SDL subsystems
    bool initialize();

    //Run the game loop
    void gameLoop();

    //Game loop funstions
    //Handle events
    bool handleEvents( SDL_Event e );

    //Perform logic based on changes
    void performLogic();

    //Render the current state of the game
    void renderScene();

    //Shut down SDL subsystems
    void shutDown();

    //The window the Game will play in
    SDL_Window* aWindow;
    //The Game's renderer
    SDL_Renderer* aRenderer;

    //A texture manager
    TextureManager* textureManager;

    //Map manager
    MapManager* mapManager;
    
    //State manager
    StateManager* stateManager;

    //List of systems
    RenderSystem* renderSystem;
    MovementSystem* movementSystem;
    PlayerControlSystem* playerControlSystem;
    CollisionSystem* collisionSystem;
    AnimationSystem* animationSystem;
    CollisionHandlerSystem* collisionHandler;
    DirectionSystem* directionSystem;
    StatusEffectHandler* statusHandler;
    

    //The game's Event Handler
    SDL_Event e;
    //Quit flag
    bool quit;
};

#endif /* Game_hpp */
