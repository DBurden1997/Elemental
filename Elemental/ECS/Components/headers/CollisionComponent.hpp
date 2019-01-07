//
//  CollisionComponent.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-17.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef CollisionComponent_hpp
#define CollisionComponent_hpp

#include "IComponent.hpp"
#include <SDL2_image/SDL_image.h>
#include <vector>
#include <string>

class CollisionComponent : public IComponent {
public:
    //Constructore
    CollisionComponent();
    CollisionComponent( unsigned long ownerId, std::string colliderType, int xPos, int yPos, int colWidth, int colHeight, int xOffset = 0, int yOffset = 0 );

    //Destructor
    virtual ~CollisionComponent();
    
    //Getters and setters
    SDL_Rect* getCollisionRect() { return collisionRect; }
    void setCollisionRect( SDL_Rect* newCollider ) { collisionRect = nullptr; collisionRect = newCollider; }
    void setRectWidth( int width ) { collisionRect->w = width; }
    void setRectHeight( int height ) { collisionRect->h = height; }
    void setXOffset( int newOffset ) { xOffset = newOffset; }
    void setYOffset( int newOffset ) { yOffset = newOffset; }
    
    std::string getColliderType() { return colliderType; }

    //Reset x positions of collision rects
    void resetPosition( int xPos, int yPos ) { collisionRect->x = xPos + xOffset; collisionRect->y = yPos + yOffset; }

private:
    //Pointer to the collision box
    SDL_Rect* collisionRect;
    
    //Offset of collision rect from the position
    int xOffset;
    int yOffset;
    
    //Type identifier
    std::string colliderType;
};

#endif /* CollisionComponent_hpp */
