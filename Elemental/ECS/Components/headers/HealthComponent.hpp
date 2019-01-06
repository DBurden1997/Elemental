//
//  HealthComponent.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-30.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef HealthComponent_hpp
#define HealthComponent_hpp

#include <stdio.h>
#include "IComponent.hpp"
#include <vector>

class HealthComponent : public IComponent {
public:
    //Constructors
    HealthComponent();
    HealthComponent( unsigned long ownerId, int maxHealth );
    
    //Getters and setters
    int getMaxHealth() { return maxHealth; }
    void adjustMaxHealth( int adjustment ) { maxHealth += adjustment; }
    
    //Getters and setters
    int getCurrentHealth() { return currentHealth; }
    void damage( int damageDealt ) { currentHealth -= damageDealt; }
    void heal( int healthHealed ) { currentHealth += healthHealed; }
    
private:
    //Maximum amount of health
    int maxHealth;
    
    //Current heath points
    int currentHealth;
};

#endif /* HealthComponent_hpp */
