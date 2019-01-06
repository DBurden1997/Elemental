//
//  StateManager.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-04.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include<map>
#include "StateManager.hpp"
#include "MessageTypeEnum.hpp"
#include "StateTypeEnum.hpp"
#include "GetState.hpp"
#include "Collision.hpp"

std::vector<IState*> StateManager::stateList = {};

std::map< std::string, State_Type > StateManager::stateMap = {
    { "idle", IDLE_STATE }, { "walking", WALKING_STATE }, { "attacking", ATTACKING_STATE }, { "hitStun", HIT_STUN_STATE }
};

StateManager::StateManager() : ReceiverInterface( { CHANGE_STATE } ) {}

void StateManager::handleMessage( Message message ) {
    switch ( message.getType() ) {
        case CHANGE_STATE:
        {
            changeState( message );
            break;
        }
        default:
            break;
    }
}

void StateManager::addState( IEntity* entity, std::string stateName ) {
    //Check if the size of the vector is larger than the id
    if( stateList.size() > entity->getId() ) {
        //Check if there is already a state for this id
        if( stateList[entity->getId()] != nullptr ) {
            ///Delete the remaining state and add the newState
            delete stateList[entity->getId()];
        }
        if( stateName.compare( "none" ) != 0 ) {
            stateList[entity->getId()] = getState( entity, stateMap[stateName] );
        }
        else {
            stateList[entity->getId()] = nullptr;
        }
    }
    else {
        if( stateName.compare( "none" ) != 0 ) {
            //printf("Added state %s\n", stateName.c_str() );
            stateList.push_back( getState(entity, stateMap[ stateName ] ) );
        }
        else {
           // printf("Added nullptr\n" );
            stateList.push_back( nullptr );
        }
    }
    printf("Size %i\n", stateList.size());
}

void StateManager::changeState( Message message ) {
    //Get the entity and state name
    IEntity* entity = message.getEntity();
    std::string state = message.getString();
    stateList[entity->getId()];
    //Delete the previous state
    delete stateList[ entity->getId() ];
    //Set the state of that entity's id to the state returned by get state
    stateList[entity->getId()] = getState( entity, stateMap[state], message.getEntity2(), message.getString2() );
}

