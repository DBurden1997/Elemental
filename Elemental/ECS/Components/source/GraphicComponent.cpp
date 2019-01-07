//
//  GraphicComponent.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "GraphicComponent.hpp"
#include "EntityTypeEnum.hpp"
#include "ComponentTypeEnum.hpp"
#include <vector>
#include <string>

GraphicComponent::GraphicComponent() : IComponent( 0, GRAPHIC_COMP, "Graphic" ), spriteClip( nullptr ) {}

GraphicComponent::~GraphicComponent() {
    //Delete the clip
    delete spriteClip;
}

GraphicComponent::GraphicComponent( unsigned long ownerId, std::string spriteSheet, int spriteXPos, int spriteYPos, int spriteWidth, int spriteHeight )
                                    : IComponent( ownerId, GRAPHIC_COMP, "Graphic" ), sheetName( spriteSheet ), spriteClip( new SDL_Rect )
{
    spriteClip->x = spriteXPos;
    spriteClip->y = spriteYPos;
    spriteClip->w = spriteWidth;
    spriteClip->h = spriteHeight;
}
