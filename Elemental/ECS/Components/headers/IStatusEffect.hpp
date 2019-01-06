//
//  IStatusEffect.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-20.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef IStatusEffect_hpp
#define IStatusEffect_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "IExpandableComponent.hpp"
#include "Timer.hpp"

class StatusEffect : public IExpandableComponent {
public:
    //Constructor
    StatusEffect( unsigned long ownerId, unsigned long typeId, std::string type, std::vector< std::string > tags );
    
    virtual ~StatusEffect() {};
    
    virtual void expandComponent(IComponent* otherComponent ) override = 0;
    
    virtual void updateStatus() = 0;
    
    //If this component is expandable
    virtual bool isExpanding() override { return true; };
    
    //If this component is a status effect
    virtual bool isStatus() override { return true; }
    
    //A timer to handle effects of the status
    Timer statusTimer;
};
#endif /* IStatusEffect_hpp */
