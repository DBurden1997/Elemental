//
//  WalkingState.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "WalkingState.hpp"
#include "IEntity.hpp"
#include "ControlComponent.hpp"

WalkingState::WalkingState( IEntity* owner ) : IState( owner, "walking" ) {
    startState();
}

WalkingState::~WalkingState() {
    endState();
}

void WalkingState::startState() {
    //Add a control component if one is not already attached
    addComponent<ControlComponent>(new ControlComponent( owner->getId() ) );
}

void WalkingState::endState() {
    //Remove control component
    removeComponent<ControlComponent>();
}
