//
//  StatusEffectHandler.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-12.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef StatusEffectHandler_hpp
#define StatusEffectHandler_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include "IEntity.hpp"
#include "ReceiverInterface.hpp"
#include "Message.hpp"
#include "IStatusEffect.hpp"

class StatusEffectHandler : public ReceiverInterface {
public:
    //Constructor
    StatusEffectHandler();
    
    //Handle messages
    virtual void handleMessage( Message message );
    
    //Update each status
    void updateStatuses();
    
private:
    //List of entities with statuses
    std::vector< IEntity* > statusEntities;
    
    //List of all statuses for each entity id
    std::map< unsigned long, std::vector< StatusEffect* > > statusEffects;
    
    //If an entity is in status entities
    bool isStatusEntity( IEntity* entity );
    
    //Remove an entity from status entities
    void removeStatusEntity( IEntity* entity );
    
    //Remove a specific status from an entity
    void removeStatus( unsigned long ownerId, std::string type );
};

#endif /* StatusEffectHandler_hpp */
