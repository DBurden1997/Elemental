//
//  HealthComponent.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-30.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "HealthComponent.hpp"
#include "ComponentTypeEnum.hpp"

HealthComponent::HealthComponent() : IComponent( 0, HEALTH_COMP, "Health" ) {}

HealthComponent::HealthComponent( unsigned long ownerId, int max ) : IComponent( ownerId, HEALTH_COMP, "Health" ), maxHealth( max ), currentHealth( max ) {}
