//
//  EntityManager.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-11.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "IEntity.hpp"
#include "EntityManager.hpp"
#include "EntityFactory.hpp"

EntityManager::EntityManager() : allEntities( {} ) {}

EntityManager::~EntityManager() {
    //Go through all entities and delete them
    for ( int i = 0; i < allEntities.size(); i++ ) {
        delete allEntities[i];
    }
}

IEntity* EntityManager::createEntity( std::string entityType, std::string fileName )  {
    //Call the factory function to get the new entity and add it to all entities
    IEntity* newEntity = EntityFactory::getEntity( entityType, fileName );
    allEntities.push_back( newEntity );
    
    //Send creation message
    send( ENTITY_CREATED, newEntity );

    return newEntity;
}

IEntity* EntityManager::getEntity( unsigned long entityId ) {
    //Look through the list of all entities for the entityId if it is not empty
    if( !allEntities.empty() ) {
        for( int i = 0; i < allEntities.size(); i++ ) {
            if( allEntities[i]->getId() == entityId ) {
                return allEntities[i];
            }
        }
    }
    //If the entityId is not found return a null pointer
    return nullptr;
}

void EntityManager::deleteEntity( unsigned long entityId ) {
    //Look through the list of all entities for the entityId if it is not empty
    if( !allEntities.empty() ) {
        for( int i = 0; i < allEntities.size(); i++ ) {
            //If the id is found
            if( allEntities[i]->getId() == entityId ) {
                //Delete the entity
                delete allEntities[i];
                //Set the location to NULL
                allEntities[i] = nullptr;
            }
        }
    }
    //If the ID is not found just return
}
