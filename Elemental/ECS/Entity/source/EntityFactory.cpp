//
//  EntityFactory.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "EntityFactory.hpp"
#include "IEntity.hpp"
#include "string"
#include "tinyxml2.h"
#include "MessageTypeEnum.hpp"
#include "ComponentFactory.hpp"
#include "StateManager.hpp"

EntityFactory::EntityFactory() {};

IEntity* EntityFactory::getEntity( std::string entityType, std::string fileName ) {
    //Create a document
    tinyxml2::XMLDocument entityData;
    
    //Get the file name
    std::string file = "Data/";
    file += fileName;
    file += ".xml";
    
    //Load the file and check for success
    tinyxml2::XMLError eResult = entityData.LoadFile( file.c_str() );
    if( eResult != 0 ) {
        printf( "Unable to load file: %s\nError: %s\n", file.c_str(), entityData.ErrorStr() );
        return nullptr;
    }
    
    //Get root document node
    tinyxml2::XMLNode* root = entityData.FirstChildElement( "entityInfo" );
    if( root == nullptr ) {
        printf( "Document not named: %s!\n", "entityInfo" );
        return nullptr;
    }
    
    //Get pointer to correct entity
    tinyxml2::XMLElement* entity = root->FirstChildElement( entityType.c_str() );
    if( entity == nullptr ) {
        printf( "Unable to find playerEntity data!\n" );
        return nullptr;
    }
    
    IEntity* newEntity = new IEntity( entityType );
    
    //Pass entity node to Component Factory
    for( tinyxml2::XMLElement* component = entity->FirstChildElement(); component != nullptr; component = component->NextSiblingElement() ) {
        printf( "Component name: %s\n", component->Name() );
        newEntity->addComponent( ComponentFactory::getComponent( component, newEntity ) );
    }
    
    //Set the initial state
    std::string initialState( entity->Attribute( "state" ) );
    
    StateManager::addState( newEntity, initialState );
    
    //Return a new entity
    return newEntity;
}
