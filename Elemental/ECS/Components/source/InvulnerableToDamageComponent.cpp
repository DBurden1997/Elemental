//
//  InvulnerableToDamageComponent.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "InvulnerableToDamageComponent.hpp"
#include "ComponentTypeEnum.hpp"

InvulnerableToDamageComponent::InvulnerableToDamageComponent() : IExpandableComponent( 0, INVULNERABLE_TO_DAMAGE_COMP, "InvulnerableToDamage" ) {};

InvulnerableToDamageComponent::InvulnerableToDamageComponent( unsigned long ownerId, bool permanent, int duration ) :
IExpandableComponent( ownerId, INVULNERABLE_TO_DAMAGE_COMP, "InvulnerableToDamage" ), permanent( permanent ), duration( duration ), timeLeft( duration ) {};

void InvulnerableToDamageComponent::expandComponent( IComponent *otherComponent ) {
    //Cast as this component
    InvulnerableToDamageComponent* other = dynamic_cast<InvulnerableToDamageComponent*>( otherComponent );
    
    //Expand the component
    //If either component is permanent make this permanent and set duration to zero
    permanent = permanent || other->isPermanent();
    duration = 0;
    timeLeft = 0;
    //If the component is not permanent
    if( !permanent ) {
        //If the new duration is longer change the duration
        if( other->getDuration() > duration ) {
            duration = other->getDuration();
        }
        //Set the remaining time to the sum of times
        extendTime( other->getTimeLeft() );
    }
    
}
