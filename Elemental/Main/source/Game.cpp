//
//  Game.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-10.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Game.hpp"
#include "global.hpp"
#include "IEntity.hpp"
#include "RenderSystem.hpp"
#include "Timer.hpp"

EntityManager* entManager = new EntityManager();

Game::Game():aWindow( nullptr ), aRenderer( nullptr ), quit( false ), textureManager{ nullptr } {}

void Game::run() {
    //Initialize the SDL subsystems
    initialize();

    //Start the game loop
    gameLoop();

    //Shut down subsystems and free objects
    shutDown();
}

bool Game::initialize() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO  ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        //Create window
        aWindow = SDL_CreateWindow( "Elementals Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN );
        if( aWindow == nullptr ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            //Set texture filtering to linear
            if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) ) {
                printf( "Warning: Nearest neighbour filtering not enabled!\n" );
            }
            //Create renderer for window
            aRenderer = SDL_CreateRenderer( aWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( aRenderer == nullptr ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else {
                //Set logical size to 640 ny 380
                SDL_RenderSetLogicalSize( aRenderer, 640, 360 );
                //Initialize renderer color
                SDL_SetRenderDrawColor( aRenderer, 0x00, 0x00, 0x00, 0xff );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    ///////To be relocated///////
    return success;
}

void Game::gameLoop() {
    //Create managers
    textureManager = new TextureManager( aRenderer );
    mapManager = new MapManager( 32, 32 );
    stateManager = new StateManager();

    //Set up systems
    ISystem::initEntityList( entManager->getAllEntities() );
    renderSystem = new RenderSystem( entManager->getAllEntities(), aRenderer );
    movementSystem = new MovementSystem();
    playerControlSystem = new PlayerControlSystem();
    collisionSystem = new CollisionSystem( mapManager );
    animationSystem = new AnimationSystem();
    collisionHandler = new CollisionHandlerSystem();
    directionSystem = new DirectionSystem();
    statusHandler = new StatusEffectHandler();

    //Load textures **RELOCATE**
    textureManager->loadTexture("CharacterSpriteSheet");
    textureManager->loadTexture("plantPlayerSword");
    textureManager->loadTexture("ProtoMap");

    //Load the level data
    mapManager->loadMap( "ProtoMap" );

    //Create a player entity
    entManager->createEntity( "playerEntity", "entityInfo" );
    entManager->createEntity( "enemyEntity", "entityInfo" );
    
    //Create the timer
    const int FPS = 60;
    const int TICKS_PER_FRAME = 1000 / FPS;
    Timer fpsTimer;
    fpsTimer.start();

    //While the game is running
    while( !quit ) {
        //If the frame has completed
        if( fpsTimer.getTicks() >= TICKS_PER_FRAME ) {
            //Handle event on queue
            quit = handleEvents( e );
            //Perform required game logic
            performLogic();
            //Render the resulting scene
            renderScene();
            //Restart the timer
            fpsTimer.start();
        }
    }
}

void Game::shutDown() {
    //Free loaded textures
    textureManager->freeTextures();
    
    //Delete all managers and systems
    delete entManager;
    delete textureManager;
    delete mapManager;
    delete renderSystem;
    delete movementSystem;
    delete collisionSystem;
    delete playerControlSystem;
    delete animationSystem;
    delete collisionHandler;
    delete directionSystem;

    //Destroy window
    SDL_DestroyRenderer( aRenderer );
    SDL_DestroyWindow( aWindow );
    aWindow = nullptr;
    aRenderer = nullptr;

    //Exit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

bool Game::handleEvents( SDL_Event e ) {
    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ){
        //If the user requests exit
        if( e.type == SDL_QUIT ) {
            return true;
        }
        //If the user presses a key send the required message
        else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
            switch ( e.key.keysym.sym ) {
                case SDLK_UP:
                    send( BUTTON_PRESSED, nullptr, "UP" );
                    break;
                case SDLK_DOWN:
                    send( BUTTON_PRESSED, nullptr,  "DOWN" );
                    break;
                case SDLK_LEFT:
                    send( BUTTON_PRESSED, nullptr,  "LEFT" );
                    break;
                case SDLK_RIGHT:
                    send( BUTTON_PRESSED, nullptr,  "RIGHT" );
                default:
                    break;
            }
        }
        else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
            switch ( e.key.keysym.sym ) {
                case SDLK_UP:
                    send( BUTTON_RELEASED, nullptr, "UP");
                    break;
                case SDLK_DOWN:
                    send( BUTTON_RELEASED, nullptr, "DOWN" );
                    break;
                case SDLK_LEFT:
                    send( BUTTON_RELEASED, nullptr, "LEFT" );
                    break;
                case SDLK_RIGHT:
                    send( BUTTON_RELEASED, nullptr, "RIGHT" );
                default:
                    break;
            }
        }
    }
    return false;
}

void Game::performLogic() {
    movementSystem->handleMovement();
    collisionSystem->checkCollisions();
    animationSystem->updateAnimations();
    statusHandler->updateStatuses();
}

void Game::renderScene() {
    //Clear the screen
    SDL_SetRenderDrawColor( aRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear( aRenderer );

    //Render the scene
    mapManager->renderMap( aRenderer );
    renderSystem->render();

    //Update screen
    SDL_RenderPresent( aRenderer );
}

