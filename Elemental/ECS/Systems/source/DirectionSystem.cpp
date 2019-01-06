//
//  DirectionManager.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-10.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "DirectionSystem.hpp"
#include "DirectionComponent.hpp"
#include "PhysicsComponent.hpp"
#include "SystemTypeEnum.hpp"
#include "Message.hpp"
#include "MessageTypeEnum.hpp"

DirectionSystem::DirectionSystem() : ISystem( DIRECTION_SYS, { CHANGE_DIRECTION, SET_OPPOSITE_DIRECTION } ){}

void DirectionSystem::handleMessage( Message message ) {
    //Verify the entity has a direction component
    DirectionComponent* directionComp = message.getEntity()->getComponentType<DirectionComponent>();
    if( directionComp != nullptr ) {
        switch ( message.getType() ) {
            case CHANGE_DIRECTION:
            {
                printf( "String: %s\n\n", message.getString().c_str());
                //If the direction is given
                if( message.getString().compare( "checkVelocity" ) != 0 ) {
                    //Change the direction to the one given
                    directionComp->setDirection( message.getString() );
                }
                else {
                    //Check for the physics component of the entity
                    PhysicsComponent* physicsComp = message.getEntity()->getComponentType<PhysicsComponent>();
                    if( physicsComp != nullptr ) {
                        //If the component exists get a new direction based on the velocity
                        std::string newDirection = getNewDirection( physicsComp->getXVel(), physicsComp->getYVel() );
                        //If the direction is different set the ew direction
                        if( newDirection.compare( "" ) != 0 && newDirection.compare( directionComp->getDirection() ) != 0 ) {
                            directionComp->setDirection( newDirection );
                        }
                    }
                }
                break;
            }
            case SET_OPPOSITE_DIRECTION:
            {
                //Change the direction to the opposite of the current direction
                directionComp->setOpposite( message.getString() );
                break;
            }
            default:
                break;
        }
    }
}

std::string DirectionSystem::getCurrentDirection( IEntity *owner ) {
    //The direction to return
    std::string direction = "";
    
    //Get the direction component and verify it exists
    DirectionComponent* directionComp = owner->getComponentType<DirectionComponent>();
    if( directionComp != nullptr ) {
        //If the opposite flag is false
        if( !( directionComp->returnsOpposite() ) ) {
            //Get the direction stored
             direction = directionComp->getDirection();
        }
        else {
            //Get the opposite direction
            direction = getOppositeDirection( directionComp->getDirection() );
        }
    }
    
    return direction;
}

std::string DirectionSystem::getNewDirection( int xVel, int yVel ) {
    //Vector holding the various directions
    std::vector< std::vector< int > >directions = { { 4, 3, 2 },
                                                    { 5, 0, 1 },
                                                    { 6, 7, 8 } };
    //Column and row of the direction vector
    int col;
    int row;
    
    //Set the column
    if( xVel < 0 ) {
        col = 0;
        return "Left";
    }
    else if( xVel == 0 ) {
        col = 1;
    }
    else {
        col = 2;
        return "Right";
    }
    //Set the row
    if( yVel < 0 ) {
        row = 0;
        return "Up";
    }
    else if( yVel == 0 ) {
        row = 1;
    }
    else {
        row = 2;
        return "Down";
    }
    
    return "";
}

std::string DirectionSystem::getOppositeDirection( std::string direction ) {
    //Return the opposite of the current direction
    std::string opposite = "";
    
    if( direction.compare( "Up" ) == 0 ){
        opposite = "Down";
    }
    else if ( direction.compare( "Down" ) == 0 ) {
        opposite = "Up";
    }
    else if( direction.compare( "Left" ) == 0 ) {
        opposite = "Right";
    }
    else if( direction.compare( "Right" ) == 0 ) {
        opposite = "Left";
    }
    
    return opposite;
}
