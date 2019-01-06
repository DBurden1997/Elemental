//
//  PlayerControlSystem.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-13.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include <SDL2/SDL.h>
#include "PlayerControlSystem.hpp"
#include "Message.hpp"
#include "MessageTypeEnum.hpp"
#include "ComponentTypeEnum.hpp"
#include "ControlComponent.hpp"

PlayerControlSystem::PlayerControlSystem() : ISystem( PLAYER_CONTROL_SYS, {ENTITY_CREATED, COMPONENT_REMOVED, COMPONENT_CREATED, BUTTON_PRESSED, BUTTON_RELEASED} ) {}

void PlayerControlSystem::addControlledEntity( IEntity* newEntity ) {
    bool inVector = false;
    for( int i = 0; i < controlledEntities.size(); i++ ) {
        if( controlledEntities[i]->getId() == newEntity->getId() ){
            inVector = true;
        }
    }
    if( !inVector ) {
        controlledEntities.push_back( newEntity );
    }
}

void PlayerControlSystem::handleMessage( Message message ) {
    //Handle the message
    switch ( message.getType() ) {
        //If a button was pressed check which button and send a message signifying its intentnt
        case BUTTON_PRESSED:
        {
            holdButton( message.getString() );
            std::string moveDirection;
            for( int i = 0; i < controlledEntities.size(); i++ ) {
                send( START_MOVING, controlledEntities[i], message.getString() );
                send( CHANGE_STATE, controlledEntities[i], "walking" );
            }
            break;
        }
        //If a button was released, check which button and send a message signifying its intent
        case BUTTON_RELEASED:
        {
            //Whether movement will be stopped
            bool stopMovement;
            releaseButton( message.getString() );
            std::string moveDirection;
            if( message.getString().compare( "UP" ) == 0 ){
                //If the down button is still held set Y movement to down
                if( isButtonHeld( "DOWN" ) ) {
                    moveDirection = "DOWN";
                    stopMovement = false;
                }
                //If not stop Y movement
                else {
                    moveDirection = "Y";
                    stopMovement = true;
                }
            }
            else if( message.getString().compare( "DOWN" ) == 0 ){
                //If the up button is still held set Y movement to up
                if( isButtonHeld( "UP" ) ) {
                    moveDirection = "UP";
                    stopMovement = false;
                }
                //If not stop Y movement
                else {
                    moveDirection = "Y";
                    stopMovement = true;
                }
            }
            else if ( message.getString().compare( "LEFT" ) == 0 ){
                //If the right button is still held set X movement to right
                if( isButtonHeld( "RIGHT" ) ) {
                    moveDirection = "RIGHT";
                    stopMovement = false;
                }
                //If not stop X movement
                else {
                    moveDirection = "X";
                    stopMovement = true;
                }
            }
            else if( message.getString().compare( "RIGHT" ) == 0 ){
                //If the left button is still held set X movement to left
                if( isButtonHeld( "LEFT" ) ) {
                    moveDirection = "LEFT";
                    stopMovement = false;
                }
                //If not stop X movement
                else {
                    moveDirection = "X";
                    stopMovement = true;
                }
            }
            for( int i = 0; i < controlledEntities.size(); i++ ) {
                //Adjust the movement of the entity
                if( stopMovement ) {
                    send( STOP_MOVING, controlledEntities[i], moveDirection );
                }
                else {
                    send( START_MOVING, controlledEntities[i], moveDirection );
                }
                
                //Adjust the state of the entity
                //Now check if there is still movement and if not change to idle
                if( heldButtons.empty() ) {
                    send( CHANGE_STATE, controlledEntities[i], "idle" );
                }
                //Otherwise change the state to walking
                else {
                    send( START_MOVING, controlledEntities[i], getLatestHorizontal() );
                    send( START_MOVING, controlledEntities[i], getLatestVertical() );
                    send( CHANGE_STATE, controlledEntities[i], "walking" );
                }
            }
            break;
        }
        //If an entity was created
        case ENTITY_CREATED:
        {
            IEntity* entity = message.getEntity();
            if( entity->hasComponentType<ControlComponent>() ) {
                addControlledEntity( entity );
            }
            break;
        }
        case COMPONENT_CREATED:
        {
            //printf( "Entity with ID %i added a component of type %s\n", message.getEntity()->getId(), message.getString().c_str() );
            if( message.getEntity()->hasComponentType<ControlComponent>() ){
                addControlledEntity( message.getEntity() );
            }
            break;
        }
        case COMPONENT_REMOVED:
        {
           // printf( "Entity with ID %i removed a component of type %s\n", message.getEntity()->getId(), message.getString().c_str() );
            //If the component is a control component remove the entity from controlled entities
            if( message.getString().compare( "Control" ) == 0 ) {
                for( int i = 0; i < controlledEntities.size(); i++ ){
                    if( controlledEntities[i]->getId() == message.getEntity()->getId() ) {
                        controlledEntities.erase( controlledEntities.begin() + i );
                    }
                }
            }
            break;
        }
        default:
            break;
    }
}


void PlayerControlSystem::holdButton( std::string button ) {
    heldButtons.push_back( button );
}

bool PlayerControlSystem::isButtonHeld( std::string button ) {
    for( int i = 0; i < heldButtons.size(); i++ ) {
        if( button.compare( heldButtons[i] ) == 0 ) {
            return true;
        }
    }
    return false;
}

void PlayerControlSystem::releaseButton( std::string button ) {
    for( int i = 0; i < heldButtons.size(); i++ ) {
        if( button.compare( heldButtons[i] ) == 0 ) {
            heldButtons.erase( heldButtons.begin() + i );
        }
    }
}

std::string PlayerControlSystem::getLatestVertical() {
    int upIndex = -1;
    int downIndex = -1;
    
    for( int i = 0; i < heldButtons.size(); i++ ) {
        if( heldButtons[i].compare( "UP" ) == 0 ) {
            upIndex = i;
        }
        else if( heldButtons[i].compare( "DOWN" ) == 0 ) {
            downIndex = i;
        }
    }
    
    if( upIndex < downIndex ) {
        return "DOWN";
    }
    else if( downIndex < upIndex ) {
        return "UP";
    }
    else {
        return "none";
    }
}

std::string PlayerControlSystem::getLatestHorizontal() {
    int leftIndex = -1;
    int rightIndex = -1;
    
    for( int i = 0; i < heldButtons.size(); i++ ) {
        if( heldButtons[i].compare( "LEFT" ) == 0 ) {
            leftIndex = i;
        }
        else if( heldButtons[i].compare( "RIGHT" ) == 0 ) {
            rightIndex = i;
        }
    }
    
    if( leftIndex < rightIndex ) {
        return "RIGHT";
    }
    else if( rightIndex < leftIndex ) {
        return "LEFT";
    }
    else {
        return "none";
    }
}
