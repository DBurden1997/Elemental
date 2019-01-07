//
//  IEntity.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-11.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "IEntity.hpp"
#include <string>

unsigned long IEntity::nextEntityId = 0;

IEntity::IEntity( std::string type ) : type( type ) {
    //If there are no free ids use the next id number
    if( freeEntityIds.empty() ) {
        entityId = nextEntityId;
        nextEntityId++;
    }
    //Otherwise use the first free id and remove it from the list
    else {
        entityId = freeEntityIds[0];
        freeEntityIds.erase( freeEntityIds.begin() );
    }
}

IEntity::~IEntity() {
    //Delete all components of the entity
    for( int i = 0; i < myComponents.size(); i++ ) {
        delete myComponents[i];
    }
}

void IEntity::addComponent( IComponent* newComponent ) {
    myComponents.push_back( newComponent );
}

std::vector< IComponent* > IEntity::getComponents(){
    return myComponents;
}

unsigned long IEntity::getId() {
    return entityId;
}

