//
//  IStatusEffect.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-20.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "IStatusEffect.hpp"

StatusEffect::StatusEffect( unsigned long ownerId, unsigned long typeId, std::string type, std::vector< std::string > tags ) :
IExpandableComponent( ownerId, typeId, type, tags ) {
    //Start the timer
    statusTimer.start();
}
