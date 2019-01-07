//
//  EntityManager.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-11.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef EntityManager_hpp
#define EntityManager_hpp

#include "IEntity.hpp"
#include "EntityFactory.hpp"
#include <vector>

class EntityManager : MessageInterface{
public:
    //Initialize values of the manager
    EntityManager();

    //Delete the manager
    ~EntityManager();

    //Create a new entity
    IEntity* createEntity( std::string entityType, std::string fileName );

    //Get an entity
    IEntity* getEntity( unsigned long entityId );

    //Get entity list for all entities
    std::vector< IEntity* >* getAllEntities() { return &allEntities; };

    //Add an entity to the list of all entities
    void addToAllEntities( IEntity* newEntity ) { allEntities.push_back( newEntity ); }

    //Delete an entity
    void deleteEntity( unsigned long entityId );

private:
    //List of all entities
    std::vector< IEntity* > allEntities;
};

#endif /* EntityManager_hpp */

