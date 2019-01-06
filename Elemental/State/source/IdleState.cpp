//
//  IdleState.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "IdleState.hpp"
#include "IEntity.hpp"
#include "ControlComponent.hpp"
#include "MessageTypeEnum.hpp"

IdleState::IdleState( IEntity* owner ) : IState( owner, "idle" ) {
    startState();
}

IdleState::~IdleState() {
    endState();
}

void IdleState::startState() {
    //Add a control component if one is not already there
    addComponent<ControlComponent>( new ControlComponent( owner->getId() ) );
}

void IdleState::endState() {
    //Remove player control
    removeComponent<ControlComponent>();
}
