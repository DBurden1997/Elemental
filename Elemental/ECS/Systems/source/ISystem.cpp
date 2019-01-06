//
//  ISystem.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "ISystem.hpp"
#include "SystemTypeEnum.hpp"
#include "MessageTypeEnum.hpp"
#include <vector>


std::vector< IEntity* >* ISystem::allEntities = nullptr;

void ISystem::initEntityList( std::vector< IEntity* >* entities ) {
    //If all entities is not initialized, initialized it with the given list
    if(  allEntities == nullptr ) {
        allEntities = entities;
    }
}

ISystem::ISystem( System_Type_Id typeId, std::vector< Message_Type > subscriptions ) : ReceiverInterface( subscriptions ), typeId( typeId ) {}
