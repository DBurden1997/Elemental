//
//  main.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-09.
//  Copyright � 2018 DarkBlaze. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Game.hpp"

int main(int argv, char** args) {
    //Initialize a game object and run it
    Game game;
    game.run();

    return 0;
}
