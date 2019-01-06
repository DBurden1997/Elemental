//
//  IAbility.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-26.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "IAbility.hpp"
#include "global.hpp"


IAbility::IAbility( std::string name, std::vector< std::string > classTags, std::vector< Cost > abilityCosts, Target* abilityTarget, std::vector< IAction > actionList ) : name( name ), classTags( classTags ), abilityCosts( abilityCosts ), abilityTarget( abilityTarget ), actionList( actionList ) {}

void IAbility::activate() {
    entManager->createEntity( name, "targetEntityInfo" );
    for( int i = 0; i < actionList.size(); i++ ) {
        actionList[i].performAction();
    }
}
