//
//  ISystem.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef ISystem_hpp
#define ISystem_hpp

#include "Message.hpp"
#include "IEntity.hpp"
#include <vector>
#include "SystemTypeEnum.hpp"
#include "ReceiverInterface.hpp"

class ISystem : public ReceiverInterface {
public:
    //Constructor
    ISystem( System_Type_Id typeId, std::vector< Message_Type > subscriptions );
    
    //Initiaize entity list
    static void initEntityList( std::vector< IEntity* >* entities );

    //Get type
    System_Type_Id getType() { return typeId; };

    //Check system type
    template < typename T >
    bool isSystemType();

    //Get list of all entities
    static std::vector< IEntity* >* getAllEntities() { return allEntities; };

    //Handle messages if the system takes them
    virtual void handleMessage( Message message ) override {};

private:
    //The id belonging to the type of system
    const System_Type_Id typeId;

    //A pointer to all entities
    static std::vector< IEntity* >* allEntities;
};

template < typename T >
bool ISystem::isSystemType() {
    //Check if a system is of the given type, then return true or false
    if( getType() == T().getType() ) {
        return true;
    }
    return false;
}

#endif /* ISystem_hpp */
