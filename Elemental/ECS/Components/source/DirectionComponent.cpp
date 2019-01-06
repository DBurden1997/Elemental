//
//  DirectionComponent.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "DirectionComponent.hpp"
#include "ComponentTypeEnum.hpp"

DirectionComponent::DirectionComponent() : IComponent( 0, DIRECTION_COMP, "Direction" ) {};

DirectionComponent::DirectionComponent( unsigned long ownerId ) : IComponent( ownerId, DIRECTION_COMP, "Direction" ), direction( "Down" ), opposite( false ) {};

void DirectionComponent::setOpposite( std::string isOpposite ) {
    if( isOpposite.compare( "true" ) == 0 ) {
        opposite = true;
    }
    else {
        opposite = false;
    }
}
