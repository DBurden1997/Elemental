//
//  IComponent.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-11.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "IComponent.hpp"

IComponent::IComponent( unsigned long ownerId, unsigned long typeId, std::string type, std::vector< std::string > tags )
                        : ownerId( ownerId ), typeId( typeId ), type( type ), tags( tags ) {};

IComponent::~IComponent() {};

