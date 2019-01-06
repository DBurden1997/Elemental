//
//  ContactDamageComponent.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-31.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "ContactDamageComponent.hpp"
#include "ComponentTypeEnum.hpp"

ContactDamageComponent::ContactDamageComponent() : IExpandableComponent( 0, CONTACT_DAMAGE_COMP, "ContactDamage" ) {};

ContactDamageComponent::ContactDamageComponent( unsigned long ownerId, int damageOnContact, bool damageToEnemy, bool damageToAlly ) :
IExpandableComponent( ownerId, CONTACT_DAMAGE_COMP, "ContactDamage" ), damageOnContact( damageOnContact ), damageToEnemy( damageToEnemy ), damageToAlly( damageToAlly ) {}

void ContactDamageComponent::expandComponent( IComponent *otherComponent ) {
    //Cast as this component
    ContactDamageComponent* other = dynamic_cast<ContactDamageComponent*>( otherComponent );
    
    damageToAlly = damageToAlly || other->damagesAllies();
    damageToEnemy = damageToEnemy || other ->damagesEnemies();
    damageOnContact += other->getContactDamage();
}
