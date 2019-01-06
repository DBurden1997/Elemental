//
//  MovementSystem.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-13.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "MovementSystem.hpp"
#include "IEntity.hpp"
#include <vector>
#include <stdio.h>
#include <math.h>
#include "ComponentTypeEnum.hpp"
#include "SystemTypeEnum.hpp"
#include "PositionComponent.hpp"
#include "PhysicsComponent.hpp"
#include "DirectionComponent.hpp"
#include "CollisionComponent.hpp"
#include "ModifierHandler.hpp"

MovementSystem::MovementSystem() : ISystem( MOVEMENT_SYS, {ENTITY_CREATED, START_MOVING, STOP_MOVING, STOP_MOVEMENT } ) {}

void MovementSystem::handleMessage( Message message ) {
    //Handle the message
    IEntity* movingEntity = message.getEntity();
    if( movingEntity == nullptr ) {
        return;
    }
    //Variable holding the base movement speed
    const int moveSpeed = 3;
    
    //Verify there is a physics component
    PhysicsComponent* physics = movingEntity->getComponentType< PhysicsComponent >();
    
    //Verify there is a physics component
    if( physics == nullptr ) {
        return;
    }
    //Now handle the message
    switch ( message.getType() ) {
        //If the intent is to start moving
        case START_MOVING:
        {
            if( message.getString().compare( "UP" ) == 0 ) {
                alterDirection( physics, { 0, -1 } );
            }
            else if( message.getString().compare( "DOWN" ) == 0 ) {
                alterDirection( physics, { 0, 1 } );
            }
            else if( message.getString().compare( "LEFT" ) == 0 ) {
                alterDirection( physics, { -1, 0 } );
            }
            else if( message.getString().compare( "RIGHT" ) == 0 ) {
                alterDirection( physics, { 1, 0 } );
            }
            physics->setVel( moveSpeed );
            break;
        }
        //If the intent is to stop moving
        case STOP_MOVING:
        {
            if( message.getString().compare( "X" ) == 0 ) {
                alterDirection( physics, { 1, 0 }, true );
            }
            else if( message.getString().compare( "Y" ) == 0 ) {
                alterDirection( physics, { 0, 1 }, true );
            }
            if( physics->getDirection()[0] == 0 && physics->getDirection()[1] == 0 ) {
                physics->setVel( 0 );
            }
            else {
                physics->setVel( moveSpeed );
            }
            break;
        }
        //Stop all movement
        case STOP_MOVEMENT:
        {
            physics->changeDirection( { 0, 0 } );
            physics->setVel( 0 );
            break;
        }
        default:
            break;
    }
    send( CHANGE_DIRECTION, movingEntity, "checkVelocity" );
}

void MovementSystem::alterDirection( PhysicsComponent *physicsComp, std::vector<float> dirVector, bool stop ) {
    //The eight directions and no direction
    std::vector< std::vector< int > >directions = { { 4, 3, 2 },
                                                    { 5, 0, 1 },
                                                    { 6, 7, 8 } };
    
    //The current direction
    std::vector<float> currentDirection = physicsComp->getDirection();
    //Get the current row and column
    std::vector< int > rowColumn = getMovingDirection( currentDirection[0], currentDirection[1] );
    //Check if movement is to be stopped
    if( stop ) {
        //Check which directions the velocity is to be stopped in
        if( dirVector[0] ) {
            //Stop x direction
            rowColumn[1] = 1;
        }
        if( dirVector[1] ) {
            //Stop y direction
            rowColumn[0] = 1;
        }
    }
    //Reassign the other directions
    else {
        if( dirVector[0] != 0 ) {
            rowColumn[1] = dirVector[0] + 1;
        }
        if( dirVector[1] != 0 ) {
            rowColumn[0] = dirVector[1] + 1;
        }
    }
    //Get the new directional vector
    physicsComp->changeDirection( getDirectionalVector( directions[ rowColumn[0] ][ rowColumn[1] ] ) );
}

std::vector< float > MovementSystem::getDirectionalVector( int direction ) {
    printf( "Direction: %i\n", direction);
    //Normalized for diagonal movement
    const float DIAGONAL = 1 / sqrt(2);
    
    //The vector to return
    std::vector< float > returnVector = {};
    
    //Check the integer and return the correct direction
    switch ( direction ) {
        case 0:
        {
            returnVector = { 0, 0 };
            break;
        }
        case 1:
        {
            returnVector = { 1, 0 };
            break;
        }
        case 2:
        {
            returnVector = { DIAGONAL, -DIAGONAL };
            break;
        }
        case 3:
        {
            returnVector = { 0, -1 };
            break;
        }
        case 4:
        {
            returnVector = { -DIAGONAL, -DIAGONAL };
            break;
        }
        case 5:
        {
            returnVector = { -1, 0 };
            break;
        }
        case 6:
        {
            returnVector = { -DIAGONAL, DIAGONAL };
            break;
        }
        case 7:
        {
            returnVector = { 0, 1 };
            break;
        }
        case 8:
        {
            returnVector = { DIAGONAL, DIAGONAL };
            break;
        }
        default:
            break;
    }
    return returnVector;
}

std::vector<int> MovementSystem::getMovingDirection( float xDir, float yDir ) {
    //Column and row of the direction vector
    int col;
    int row;
    
    //Set the column
    if( xDir < 0 ) {
        col = 0;
    }
    else if( xDir == 0 ) {
        col = 1;
    }
    else {
        col = 2;
    }
    //Set the row
    if( yDir < 0 ) {
        row = 0;
    }
    else if( yDir == 0 ) {
        row = 1;
    }
    else {
        row = 2;
    }
    
    return { row, col };
}

std::vector< int > MovementSystem::applyModifiers( int baseXVel, int baseYVel, std::vector< Modifier* > modifiers ) {
    //Vector to return
    std::vector< int > finalVelocities = { baseXVel, baseYVel };
    //Apply each modifer
    for( int i = 0; i < modifiers.size(); i++ ) {
        //Cast the modifer as a movement modifier
        MovementModifier* moveMod = static_cast<MovementModifier*>( modifiers[i] );
        //Apply the modifier
        finalVelocities = moveMod->applyModifier( finalVelocities[0], finalVelocities[1] );
    }
    
    return  finalVelocities;
}

std::vector< int > MovementSystem::getDisplacement( unsigned long ownerId, int baseXVel, int baseYVel ) {
    //Get the modifier list
    std::vector< Modifier* > modifiers = ModifierHandler::getModifierList(ownerId, "Movement" );
    //Apply the modifiers
    std::vector< int > velocities = applyModifiers( baseXVel, baseYVel, modifiers );
    //Return the resulting velocities
    return velocities;
}

void MovementSystem::handleMovement() {
    //Velocities
    int xVel = 0;
    int yVel = 0;

    std::vector< IComponent* > entityComponents;
    for( int i = 0; i < getAllEntities()->size(); i++ ) {

        //The current entity
        IEntity* entity = getAllEntities()->at(i);

        //Check components for the correct types
        PositionComponent* position = entity->getComponentType< PositionComponent >();
        PhysicsComponent* physics = entity->getComponentType< PhysicsComponent >();
        CollisionComponent* collision = entity->getComponentType<CollisionComponent>();
        
        if( physics != nullptr ) {
            //Get the velocities
            std::vector< int > displacement = getDisplacement( physics->getOwnerId(), physics->getXVel(), physics->getYVel() );
            xVel = displacement[0];
            yVel = displacement[1];
            
            //If the velcocity is equal to 0 and the entity was moving set moving to false
            if( xVel == 0 && yVel == 0 && physics->isMoving() ) {
                physics->stopMoving();
            }
                
            //If the required components are avaiable change the position
            if( ( position != nullptr ) && ( xVel != 0 || yVel != 0 ) ) {
                //Set moving to true if entity was not moving before
                if( !physics->isMoving() ) {
                    physics->startMoving();
                }
                position->prevX = position->getXPos();
                position->prevY = position->getYPos();
                position->adjustXPos( xVel );
                position->adjustYPos( yVel );
                //If there is a collision component then update the positions of the collision boxes
                if( collision != nullptr ) {
                    collision->resetPosition( position->getXPos(), position->getYPos() );
                }
                //Send a message informing movement has occured
                send(HAS_MOVED, entity );
            }
        }
    }
}
