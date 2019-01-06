//
//  GameTexture.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-10.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef GameTexture_hpp
#define GameTexture_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

//Wrapper class for textures and related functions
class GameTexture {
public:
    //Initializes variables
    GameTexture( std:: string name );

    //Deallocate memory
    ~GameTexture();

    //Load image from specified path
    bool loadFromFile( SDL_Renderer* renderer, std::string path );

    //Deallocate texture
    void free();

    //Render texture at given point
    void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr );

    //Get image dimensions
    int getWidth();
    int getHeight();

    //Get the texture name
    std::string getName() { return textureName; }

private:
    //The SDL texture
    SDL_Texture* aTexture;

    //The texture name
    std::string textureName;

    //The texture dimensions
    int aWidth;
    int aHeight;
};

#endif /* GameTexture_hpp */
