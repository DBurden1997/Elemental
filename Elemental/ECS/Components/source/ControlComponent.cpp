//
//  ControlComponent.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "ControlComponent.hpp"
#include "IComponent.hpp"
#include "ComponentTypeEnum.hpp"
#include "EntityTypeEnum.hpp"

ControlComponent::ControlComponent() : IComponent( 0, CONTROL_COMP, "Control" ) {}

ControlComponent::ControlComponent( unsigned long ownerId ) : IComponent( ownerId, CONTROL_COMP, "Control" ) {}

