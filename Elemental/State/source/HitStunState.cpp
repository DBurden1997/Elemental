//
//  HitStunState.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-06.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "IEntity.hpp"
#include "HitStunState.hpp"
#include "InvulnerableToDamageComponent.hpp"
#include "KnockBackComponent.hpp"
#include "ControlComponent.hpp"

HitStunState::HitStunState( IEntity* owner, std::vector< float > direction ) : IState( owner, "hitStun" ), direction( direction ){
    startState();
}

HitStunState::~HitStunState() {
    endState();
}

void HitStunState::startState() {
    //Add the correct components to the entity
    send( STOP_MOVEMENT, owner );
    send( SET_OPPOSITE_DIRECTION, owner, "true" );
    addComponent<InvulnerableToDamageComponent>( new InvulnerableToDamageComponent( owner->getId(), false, 30 ) );
    addComponent<KnockBackComponent>( new KnockBackComponent( owner->getId(), direction, 4, 6, 50  ) );
}

void HitStunState::endState() {
    //Remove components that aren't required
    send( SET_OPPOSITE_DIRECTION, owner, "false" );
    removeComponent<KnockBackComponent>();
}
