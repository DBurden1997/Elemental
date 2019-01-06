//
//  MovementModifier.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-24.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "MovementModifier.hpp"

MovementModifier::MovementModifier( unsigned long ownerId, std::string precedence, std::vector< float > direction, int velocity ) :
Modifier( ownerId, "Movement", precedence ), direction( direction ), velocity( velocity )
{
    calculateXYComponents();
}

std::vector< int > MovementModifier::applyModifier( int oldX, int oldY ) {
    //The velocity to return
    std::vector< int > returnVelocity = { oldX + xVel, oldY + yVel };
    
    return returnVelocity;
}

void MovementModifier::updateModifier( std::vector<float> newDirection, int newVelocity ) {
    //Update the modifier with the new values
    direction = newDirection;
    velocity = newVelocity;
    calculateXYComponents();
}

void MovementModifier::calculateXYComponents() {
    xVel = direction[0] * velocity;
    yVel = direction[1] * velocity;
}
