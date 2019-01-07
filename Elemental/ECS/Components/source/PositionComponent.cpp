//
//  PositionComponent.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "PositionComponent.hpp"
#include "EntityTypeEnum.hpp"
#include "ComponentTypeEnum.hpp"
#include <vector>
#include <SDL2/SDL.h>


PositionComponent::PositionComponent() : IComponent( 0, POSITION_COMP, "Position" ) {}

PositionComponent::PositionComponent( unsigned long ownerId, int xPos, int yPos, int anchorX, int anchorY ) : IComponent( ownerId, POSITION_COMP, "Position" ), xPos( xPos ), yPos( yPos ), anchorX( anchorX ), anchorY( anchorY ) {}


