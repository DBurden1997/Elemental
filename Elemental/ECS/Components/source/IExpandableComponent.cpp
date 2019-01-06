//
//  IExpandableComponent.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-10.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "IExpandableComponent.hpp"

IExpandableComponent::IExpandableComponent( unsigned long ownerId, unsigned long typeId, std::string type, std::vector< std::string > tags ): IComponent( ownerId, typeId, type, tags ) {};
