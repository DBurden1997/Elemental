//
//  StateManager.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-04.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef StateManager_hpp
#define StateManager_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include "IEntity.hpp"
#include "Message.hpp"
#include "ReceiverInterface.hpp"
#include "IState.hpp"
#include "StateTypeEnum.hpp"

class StateManager : public ReceiverInterface {
public:
    //Constructor
    StateManager();
    
    //Handle incoming messages
    virtual void handleMessage( Message message ) override;
    
    //Add state to the list of states
    static void addState( IEntity* entity, std::string stateName);
    
    //Change the state of an entity
    static void changeState( Message message );
    
    //Map from state names to state ids
    static std::map< std::string, State_Type > stateMap;
    
private:
    //List of states, the entity id is used to access its state
    static std::vector< IState* > stateList;
};

#endif /* StateManager_hpp */
