//
//  ModifierHandler.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-22.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "ModifierHandler.hpp"

std::map< unsigned long, std::map< std::string, std::vector< Modifier* > > > ModifierHandler::modifiers = {};

ModifierHandler::ModifierHandler() : ReceiverInterface( {} ) {}

void ModifierHandler::handleMessage( Message message ) {
    switch ( message.getType() ) {
        default:
            break;
    }
}

void ModifierHandler::addModifier( unsigned long ownerId, std::string stat, Modifier *modifier ) {
    //The placement of the modifier
    int placement = -1;
    
    //Check if the entity is already in the map
    if( modifiers.count( ownerId ) != 0 ) {
        //Check if the stat already has some modifiers
        if( modifiers[ownerId].count( stat ) != 0 ) {
            //Add the modifier to this list
            modifiers[ownerId][stat].push_back( modifier );
            //Placement is at the end of the vector, so its length subtract one
            placement = modifiers[ownerId][stat].size() - 1;
        }
        //If the entity has no modifiers already for this stat
        else {
            //Create a new list for this stat and place it into the map
            modifiers[ownerId].insert( std::pair< std::string, std::vector< Modifier* > >( stat, { modifier } ) );
            //New vector so at beginning
            placement = 0;
        }
    }
    //If the entity does not yet have a modifiers list
    else {
        //Create a new map
        std::map< std::string, std::vector< Modifier* > > newEntityMap;
        //Insert the stat value pair
        newEntityMap.insert( std::pair< std::string, std::vector< Modifier* > >( stat, { modifier } ) );
        //Insert the new map into the modifiers map
        modifiers.insert( std::pair< unsigned long , std::map< std::string, std::vector< Modifier* > > >( ownerId, newEntityMap ) );
        //New vector so at beginning
        placement = 0;
    }
    
    modifier->setPlacement( placement );
}

void ModifierHandler::removeModifier( unsigned long ownerId, std::string stat, int placement ) {
    //Check the modifier exists and then remove it if it does
    if( modifiers.count( ownerId ) != 0 ) {
        if( modifiers[ownerId].count( stat ) != 0 ) {
            if( modifiers[ownerId][stat].size() > placement ) {
                modifiers[ownerId][stat].erase( modifiers[ownerId][stat].begin() + placement );
            }
        }
    }
}

std::vector< Modifier* > ModifierHandler::getModifierList( unsigned long ownerId, std::string stat ) {
    std::vector< Modifier* > modifierList = {};
    //Verify that there is a modifier list for this entity
    if( modifiers.count( ownerId ) != 0 ) {
        //Verify there is a modifier list for the stat
        if( modifiers[ownerId].count( stat ) != 0 ) {
            //Get the modifier list
            modifierList = modifiers[ownerId][stat];
        }
    }
    
    //Return the list
    return modifierList;
}
