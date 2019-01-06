//
//  GetState.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include <sstream>
#include "GetState.hpp"
#include "HitStunState.hpp"
#include "IdleState.hpp"
#include "WalkingState.hpp"
#include "PositionComponent.hpp"
#include "Collision.hpp"

bool isValidInfo( State_Type stateType, std::string info ) {
    //Validity flag
    bool isValid = false;
    
    switch ( stateType ) {
        case HIT_STUN_STATE:
        {
            if( info.compare( "directionFromOther" ) == 0 ) {
                isValid = true;
            }
            else {
                float xDir;
                float yDir;
                char c;
                std::stringstream stream( info );
                stream >> xDir;
                stream.get( c );
                if( c != '|' ) {
                    printf( "Invalid info!!!\n" );
                }
                else{
                    stream >> yDir;
                    isValid = true;
                }
            }
            break;
        }
        default:
            break;
    }
    
    return isValid;
}

IState* getState( IEntity* entity, State_Type stateType, IEntity* other, std::string info ) {
    std::string entityType = entity->getType();
    //First check for the entity type
    if( entityType.compare( "playerEntity" ) == 0 ){
        //Now return the state according to state type
        switch ( stateType ) {
            case IDLE_STATE: {
                return new IdleState( entity );
                break;
            }
            case WALKING_STATE: {
                return new WalkingState( entity );
                break;
            }
            case HIT_STUN_STATE:{
                if( other != nullptr && isValidInfo( stateType, info ) ) {
                    PositionComponent* entityPosition = entity->getComponentType<PositionComponent>();
                    PositionComponent* otherPosition = other->getComponentType<PositionComponent>();
                    int entityX = entityPosition->getXPos();
                    int entityY = entityPosition->getYPos();
                    int otherX = otherPosition->getXPos();
                    int otherY = otherPosition->getYPos();
                    return new HitStunState( entity, Collision::getNormalizedVector( otherX, otherY, entityX, entityY ) );
                }
                break;
            }
            default:
                break;
        }
    }
    return nullptr;
}
