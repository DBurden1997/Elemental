//
//  CollisionComponent.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-17.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "CollisionComponent.hpp"
#include "ComponentTypeEnum.hpp"
#include <string>

CollisionComponent::CollisionComponent() : IComponent( 0, COLLISION_COMP, "Collision" ), collisionRect( nullptr ) {};

CollisionComponent::~CollisionComponent() {
    //Delete the collision rect
    delete collisionRect;
}

CollisionComponent::CollisionComponent( unsigned long ownerId, std::string colliderType, int xPos, int yPos, int colWidth, int colHeight, int xOffset, int yOffset ) : IComponent( ownerId, COLLISION_COMP, "Collision" ), colliderType( colliderType ), xOffset( xOffset ), yOffset( yOffset ), collisionRect( new SDL_Rect( {xPos + xOffset, yPos + yOffset, colWidth, colHeight} ) ) {}
