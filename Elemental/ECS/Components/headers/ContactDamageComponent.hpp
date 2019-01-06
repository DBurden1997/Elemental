//
//  ContactDamageComponent.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-31.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef ContactDamageComponent_hpp
#define ContactDamageComponent_hpp

#include <stdio.h>
#include <vector>
#include "IExpandableComponent.hpp"

class ContactDamageComponent : public IExpandableComponent {
public:
    //Constructor
    ContactDamageComponent();
    ContactDamageComponent( unsigned long ownerId, int damageOnContact, bool damageToEnemy, bool damageToAlly );
    
    //If another component of this type is added
    virtual void expandComponent( IComponent* otherComponent ) override;
    
    //Getters and setters
    int getContactDamage() { return damageOnContact; }
    void setDamageOnContact( int newDamage ) { damageOnContact = newDamage; }
    
    bool damagesEnemies() { return damageToEnemy; }
    bool damagesAllies() { return damageToAlly; }
    
private:
    //Amount of damage done to enemy entities on contact
    int damageOnContact;
    
    //Damages this entity's enemy on contact
    bool damageToEnemy;
    
    //Damages allies on contact
    bool damageToAlly;
};

#endif /* ContactDamageComponent_hpp */
