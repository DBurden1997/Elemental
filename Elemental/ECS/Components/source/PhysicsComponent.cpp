//
//  PhysicsComponent.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-13.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "PhysicsComponent.hpp"
#include <vector>
#include "ComponentTypeEnum.hpp"
#include "EntityTypeEnum.hpp"

PhysicsComponent::PhysicsComponent() : IComponent( 0, PHYSICS_COMP, "Physics" ) {}

PhysicsComponent::PhysicsComponent( unsigned long ownerId, int xVel, int yVel, int vel, std::vector< float > direction ) : IComponent( ownerId, PHYSICS_COMP, "Physics" ), xVel( xVel ), yVel( yVel ), vel( vel ), direction( direction )
{
    resetVelocities();
}

void PhysicsComponent::resetVelocities() {
    //Reset the x and y components of the velocity based on the direction and base velocity
    xVel = direction[0] * vel;
    yVel = direction[1] * vel;
}
