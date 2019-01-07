//
//  GraphicComponent.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef GraphicComponent_hpp
#define GraphicComponent_hpp

#include "IComponent.hpp"
#include "GameTexture.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <string>

//Contains the information on the current image to be rendered by the rendering system
class GraphicComponent : public IComponent {
public:
    //Constructors
    GraphicComponent();
    GraphicComponent( unsigned long ownerId, std::string sheetName, int spriteXPos, int spriteYPos, int spriteWidth, int spriteHeight );

    //Destructor
    virtual ~GraphicComponent();
    
    //Getters
    std::string getSpriteSheet() { return sheetName; }
    
    SDL_Rect* getSpriteClip() { return spriteClip; }
    void setSpriteClip( SDL_Rect newClip ) { spriteClip->x = newClip.x; spriteClip->y = newClip.y; spriteClip->w = newClip.w; spriteClip->w = newClip.w; }
    
    int getSpriteXPos() { return spriteClip->x; }
    int getSpriteYPos() {return spriteClip->y; }
    int getSpriteWidth() { return spriteClip->w; }
    int getSpriteHeight() { return spriteClip->h; }

private:
    //Filename containing the sprite sheet
    std::string sheetName;

    //Current clip of sprite sheet
    SDL_Rect* spriteClip;
};

#endif /* GraphicComponent_hpp */
