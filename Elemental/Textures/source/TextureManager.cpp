
#include "GameTexture.hpp"
#include "TextureManager.hpp"
#include <string>
#include <vector>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

std::vector< GameTexture* > TextureManager::loadedTextures = {};

SDL_Renderer* TextureManager::renderer = nullptr;

TextureManager::TextureManager() {}

TextureManager::TextureManager( SDL_Renderer* renderPointer ) {
    //If there has been no renderer assigned, assign one
    if( renderer == nullptr ) {
        renderer = renderPointer;
    }
}

GameTexture* TextureManager::loadTexture( std::string textureName ) {
    //Create the file name
    std::string file = "Sprites/";
    file.append( textureName );
    file.append(".png");

    //Load the texture
    GameTexture* newTexture = new GameTexture( textureName );
    if( !( newTexture->loadFromFile( renderer, file ) ) ){
        printf( "Unable to load texture: %s\n", file.c_str() );
    }

    //Add the loaded texture to the list
    loadedTextures.push_back( newTexture );

    //Return the laoded texture
    return newTexture;
}

bool TextureManager::isTexture( std::string searchName ) {
    //Search through the loaded textures for the name
    for( int i = 0; i < loadedTextures.size(); i++ ) {
        if( loadedTextures[i]->getName() == searchName ) {
            return true;
        }
    }

    //If the name isn't found return false
    return false;
}

GameTexture* TextureManager::getTexture( std::string searchName ) {
    //Search through the loaded textures for the name
    for( int i = 0; i < loadedTextures.size(); i++ ) {
        if( loadedTextures[i]->getName() == searchName ) {
            return loadedTextures[i];
        }
    }

    //If the name isn't found load the texture
    return loadTexture( searchName );
}

void TextureManager::freeTextures() {
    //Loop through loaded textures and free them
    for( int i = 0; i < loadedTextures.size(); i++ ) {
        loadedTextures[i]->free();
    }
}
