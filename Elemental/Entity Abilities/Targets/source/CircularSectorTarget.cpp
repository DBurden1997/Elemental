//
//  CircularSectorTarget.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-09-12.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include <cmath>
#include "CircularSectorTarget.hpp"
#include "MessageTypeEnum.hpp"
#include "global.hpp"
#include "PositionComponent.hpp"
#include "CollisionComponent.hpp"

CircularSectorTarget::CircularSectorTarget( std::string targetType, int radius, int angle, std::vector< int >*  origin ) : Target( targetType ), radius( radius ), angle( angle ), origin( origin ), direction( {} ) {}

void CircularSectorTarget::getTargetLocation() {
    //If the mouse coordinates are set
    if( mouseCoordinates.size() == 2 ) {
        //Get the vector from the origin of the circular sector to the mouse position
        std::vector< int > directionVector = { mouseCoordinates[0] - (*(origin))[0], mouseCoordinates[1] - (*(origin))[1] };
        //Calculate the angle
        float angle = atan2( directionVector[1], directionVector[0] );
        angle = ( angle * 180 ) / M_PI;
        //Dependant on the angle set the direction of the attack
        //Up
        if( angle > 45 && angle <= 135 ) {
            direction.push_back( 0 );
            direction.push_back( 1 );
        }
        //Left
        else if( angle > 135 && angle <= 225 ) {
            direction.push_back( -1 );
            direction.push_back( 0 );
        }
        //Down
        else if( angle > 225 && angle <= 315 ){
            direction.push_back( 0 );
            direction.push_back( -1 );
        }
        //Right
        else {
            direction.push_back( 1 );
            direction.push_back( 0 );
        }
    }
}

bool CircularSectorTarget::isValidTarget( IEntity* entity ) {
    //Get the entity's collision component
    CollisionComponent* collider = entity->getComponentType<CollisionComponent>();
    
    //Get the corners of the bounding box
    return true;
}

void CircularSectorTarget::getTargets() {
    //Get a list of all entities
    std::vector< IEntity* >* entities = entManager->getAllEntities();
    //Check if each entity is within the attack range
    for( int i  = 0; i < entities->size(); i++ ) {
        //Get the entity
        IEntity* entity = (*entities)[i];
        //Get vector from origin of circular sector to origin of entity
        std::vector< int> vectorToEntity = { entity->getComponentType<PositionComponent>()->getAnchorX() - (*origin)[0],
                                             entity->getComponentType<PositionComponent>()->getAnchorY() - (*origin)[1] };
        
    }
}

bool CircularSectorTarget::hasTarget() {
    bool success = false;
    if( direction.size() == 2 ) {
        success = true;
    }
    
    return success;
}
