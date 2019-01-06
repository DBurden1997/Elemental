//
//  GameTexture.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-10.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "GameTexture.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

//Definition of GameTexture functions

GameTexture::GameTexture( std::string name ) : aTexture( nullptr ), aWidth( 0 ), aHeight(  0 ), textureName( name ) {}

GameTexture::~GameTexture() {
    //Deallocate the texture
    free();
}

bool GameTexture::loadFromFile( SDL_Renderer* renderer, std::string path ) {
    //Free previous texture
    free();

    //The final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else {
            //Get image dimensions
            aWidth = loadedSurface->w;
            aHeight = loadedSurface->h;
        }

        //Remove the temporary surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    aTexture = newTexture;
    return aTexture != nullptr;
}

void GameTexture::free() {
    //Free texture if it exists
    if( aTexture != nullptr ) {
        SDL_DestroyTexture( aTexture );
        aTexture = nullptr;
        aWidth = 0;
        aHeight = 0;
    }
}

void GameTexture::render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip ){
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, aWidth, aHeight };

    //Set clip rendering dimensions
    if( clip != NULL ) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render the texture
    SDL_RenderCopy( renderer, aTexture, clip, &renderQuad );
}

int GameTexture::getWidth() {
    return aWidth;
}

int GameTexture::getHeight() {
    return aHeight;
}



