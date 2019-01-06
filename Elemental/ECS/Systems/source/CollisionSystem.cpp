//
//  CollisionSystem.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-17.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "CollisionSystem.hpp"
#include "PositionComponent.hpp"
#include "PhysicsComponent.hpp"
#include "SystemTypeEnum.hpp"
#include "MessageTypeEnum.hpp"
#include <stdio.h>
#include <string>
#include <SDL2_image/SDL_image.h>
#include "Collision.hpp"

std::vector< IEntity* > CollisionSystem::collisionEntities = {};

CollisionSystem::CollisionSystem( MapManager* mapManager ) : ISystem( COLLISION_SYS, { ENTITY_CREATED } ), mapManager( mapManager) {}

void CollisionSystem::addCollisionEntity( IEntity* newCollisionEntity) {
    collisionEntities.push_back( newCollisionEntity );
}

void CollisionSystem::handleMessage( Message message ) {
    switch ( message.getType() ) {
        //If an entity is created check for required components and add to list if it has them
        case ENTITY_CREATED:
            if( (message.getEntity()->hasComponentType<CollisionComponent>()) && (message.getEntity()->hasComponentType<PhysicsComponent>()) && (message.getEntity()->hasComponentType<PositionComponent>()) ) {
                printf("Collision entity added!\n");
                collisionEntities.push_back( message.getEntity() );
            }
            break;
        default:
            break;
    }
}

void CollisionSystem::checkCollisions() {
    //For each collision entity check for background and entity collisions
    for( int i = 0; i < collisionEntities.size(); i++ ) {
        if( collisionEntities[i]->getComponentType<PhysicsComponent>()->isMoving() ) {
            checkBackgroundCollisions( collisionEntities[i] );
            checkEntityCollisions( collisionEntities[i] );
        }
    }
}


void CollisionSystem::checkBackgroundCollisions( IEntity* entity ) {
    //Get the collision and position component of the entity we are checking collisions for
    CollisionComponent* collider = entity->getComponentType< CollisionComponent >();
    PositionComponent* position = entity->getComponentType< PositionComponent >();

    //Get the collision vector from the Map Manager's collision function
    std::vector< int > collisionVector = mapManager->checkMapCollision( collider->getCollisionRect() );

    //While there are still collisions keep updating positions
    while( !collisionVector.empty() ) {
        //Update position of the position component and collision rects
        position->adjustXPos( collisionVector[0] );
        position->adjustYPos( collisionVector[1] );
        collider->resetPosition( position->getXPos(), position->getYPos() );

        //Check collisions again to verify there are no more
        collisionVector = mapManager->checkMapCollision( collider->getCollisionRect() );
    }
}

void CollisionSystem::checkEntityCollisions( IEntity* entity) {
    //For each collision entity
    for( int i = 0; i < collisionEntities.size(); i++ ) {
        //Flag signalling a collision took place
        bool wasCollision = false;
        //If it isn't the entity we are currently checking collisions for
        if( collisionEntities[i]->getId() != entity->getId() ) {
            //Get the Collision components of the two collision components
            CollisionComponent* colliderOne = entity->getComponentType<CollisionComponent>();
            CollisionComponent* colliderTwo = collisionEntities[i]->getComponentType<CollisionComponent>();

            //Get the position component of the entity we are checking collisions for
            PositionComponent* positionOne = entity->getComponentType<PositionComponent>();

            //While there are collisions
            while( Collision::isCollision( colliderOne->getCollisionRect(), colliderTwo->getCollisionRect() ) ) {
                //Set flag to true
                wasCollision = true;
                //Get the collision vector and update positions
                std::vector< int > collisionVector = Collision::getCollisionVector( colliderOne->getCollisionRect(), colliderTwo->getCollisionRect() );
                positionOne->adjustXPos( collisionVector[0] );
                positionOne->adjustYPos( collisionVector[1] );
                colliderOne->resetPosition( positionOne->getXPos(), positionOne->getYPos() );
            }
            //If there was a collision send a message with the information
            if( wasCollision ) {
                send( COLLISION_OCCURED, entity, colliderOne->getColliderType(), collisionEntities[i], colliderTwo->getColliderType() );
            }
        }
    }
}




