#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

#include <string>
#include <vector>
#include "GameTexture.hpp"
#include <SDL2_image/SDL_image.h>

class TextureManager {
public:
    //Constructor
    TextureManager();
    TextureManager( SDL_Renderer* renderer );

    //Load a texture
    GameTexture* loadTexture( std::string textureName );

    //Check if the requested name is located in loadedTextures
    bool isTexture( std::string searchName );

    //Return a pointer to a texture based on its name
    GameTexture* getTexture( std::string searchName );

    //Free all current textures
    void freeTextures();

private:
    //List of all currently loaded textures
    static std::vector< GameTexture* > loadedTextures;

    //Pointer to a renderer that will render textures
    static SDL_Renderer* renderer;
};

#endif // TEXTUREMANAGER_HPP_INCLUDED
