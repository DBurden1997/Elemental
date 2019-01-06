//
//  StatusEffectHandler.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-12.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "StatusEffectHandler.hpp"
#include "SystemTypeEnum.hpp"
#include "MessageTypeEnum.hpp"

StatusEffectHandler::StatusEffectHandler() : ReceiverInterface( { ENTITY_REMOVED, COMPONENT_CREATED, COMPONENT_REMOVED } ), statusEntities( {} ) {}

void StatusEffectHandler::handleMessage( Message message ) {
    //Check the message type
    switch ( message.getType() ) {
        case ENTITY_REMOVED:
        {
            //If an entity is deleted remove it from the status entity list
            removeStatusEntity( message.getEntity() );
            break;
        }
        case COMPONENT_CREATED:
        {
            //Check the components for any status effects and place them in the associated list
            std::vector< IComponent* > components = message.getEntity()->getComponents();
            for( int i = 0; i < components.size(); i++ ) {
                if( components[i]->isStatus() ) {
                    //If the owner is a status entity add the status
                    if( isStatusEntity( message.getEntity() ) ){
                        printf( "Id: %i\n", message.getEntity()->getId() );
                        statusEffects.at( message.getEntity()->getId() ).push_back( dynamic_cast<StatusEffect*>( components[i] ) );
                    }
                    //If the owner isn't yet a status entity
                    else {
                        printf("SUCCESSS\n\n\n");
                        //Add the owner to the status entity list
                        statusEntities.push_back( message.getEntity() );
                        //Then add the status
                        statusEffects.insert( std::pair< unsigned long, std::vector< StatusEffect* > >
                                             ( message.getEntity()->getId(), { dynamic_cast<StatusEffect*>( components[i] ) } )
                                             );
                    }
                }
            }
            break;
        }
        case COMPONENT_REMOVED:
        {
            if( isStatusEntity( message.getEntity() ) ){
                removeStatus( message.getEntity()->getId(), message.getString() );
            }
            break;
        }
        default:
            break;
    }
}

void StatusEffectHandler::updateStatuses() {
    //For each entity with status effects
    for( int i = 0; i < statusEntities.size(); i++ ) {
        //Get the id to use as a key
        unsigned long ownerId = statusEntities[i]->getId();
        
        //Get the list of status effects for the key
        std::vector<StatusEffect*> statuses = statusEffects.at( ownerId );
        
        //Loop through and update all status effects
        for( int j = 0; j < statuses.size(); j++ ) {
            statuses[j]->updateStatus();
        }
    }
}

bool StatusEffectHandler::isStatusEntity( IEntity *entity ) {
    //Success flag
    bool success = false;
    
    //Check the entities with status effects for the entity and return true if found or false if not found
    for (int i = 0; i < statusEntities.size(); i++ ) {
        printf( "i: %i, size: %i\n\n\n", i, statusEntities.size() );
        if( entity->getId() == statusEntities[i]->getId() ) {
            printf( "%s\n\n", statusEntities[i]->getType().c_str());
            success = true;
        }
    }
    return success;
}

void StatusEffectHandler::removeStatusEntity( IEntity *entity ) {
    //Check the entities with status effects for the entity and remove it from the list
    for (int i = 0; i < statusEntities.size(); i++ ) {
        if( entity->getId() == statusEntities[i]->getId() ) {
            statusEntities.erase( statusEntities.begin() + i );
        }
    }
}

void StatusEffectHandler::removeStatus( unsigned long ownerId, std::string type ) {
    if( statusEffects.count( ownerId ) != 0 ) {
        //Get the list of status effects for the key
        std::vector<StatusEffect*> statuses = statusEffects.at( ownerId );
    
        //Look for the status of the same type
        for( int i = 0; i < statuses.size(); i++ ) {
            if( statusEffects.at( ownerId )[i]->getName().compare( type ) == 0 ) {
                statusEffects.at( ownerId ).erase( statusEffects.at( ownerId ).begin() + i );
            }
        }
    }
}
