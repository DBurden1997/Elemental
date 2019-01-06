//
//  KnockBackComponent.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef KnockBackComponent_hpp
#define KnockBackComponent_hpp

#include <stdio.h>
#include <vector>
#include "IStatusEffect.hpp"
#include "MovementModifier.hpp"

class KnockBackComponent : public StatusEffect {
public:
    //Constructor
    KnockBackComponent();
    KnockBackComponent( unsigned long ownerId, std::vector< float > direction, int initialVelocity, int slowDownFrame, double percentage );
    
    //Destructor
    ~KnockBackComponent();
    
    //Override expand
    void expandComponent( IComponent* otherComponent ) override;
    
    //Override update
    void updateStatus() override;
    
    //Get modifications
    int getVelocity() { return currentVelocity; }
    std::vector< float > getDirection() { return direction; }
    
private:
    //Direction of the knockback
    std::vector< float > direction;
    
    //Velocity at start of knockback
    int initialVelocity;
    
    //The current velocity
    int currentVelocity;
    
    //Frames to wait to decrease velocity
    int slowDownFrame;
    
    //Percentage of previous velocity to use after decreasing
    double percentage;
    
    //Modifer applied to movement while knockbakc is in effect
    MovementModifier* moveMod;
    
    //Update the modifier with any changes to knockback velocity
    void updateMod();
};

#endif /* KnockBackComponent_hpp */
