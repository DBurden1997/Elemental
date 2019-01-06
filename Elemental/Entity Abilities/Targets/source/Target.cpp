//
//  Target.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-27.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "Target.hpp"
#include "EntityManager.hpp"

Target::Target( std::string targetType ) : targetType( targetType ), targetedEntities( {} ), mouseCoordinates( {} ) {}

bool Target::isReady() {
    bool ready = true;
    if( mouseCoordinates.size() != 2 ) {
        ready = false;
    }
    
    return ready;
}

void Target::readyFunction() {
    getTargetLocation();
}
