//
//  InvulnerableToDamageComponent.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef InvulnerableToDamageComponent_hpp
#define InvulnerableToDamageComponent_hpp

#include <stdio.h>
#include "IExpandableComponent.hpp"

class InvulnerableToDamageComponent : public IExpandableComponent {
public:
    //Constructor
    InvulnerableToDamageComponent();
    InvulnerableToDamageComponent( unsigned long ownerId, bool permanent, int duration = 0 );
    
    //Override expand component
    virtual void expandComponent( IComponent* otherComponent ) override;
    
    //Getters and setters
    bool isPermanent() { return permanent; }
    int getDuration() { return duration; }
    int getTimeLeft() { return timeLeft; }
    void ResetDuration() { timeLeft = duration; }
    void extendTime( int extension = 1 ) { timeLeft += extension; }
    void decreaseTime() { timeLeft--; }
    
private:
    //Boolean of whether the invulnerability is permanent
    bool permanent;
    
    //Duration of the invulnerability
    int duration;
    
    //Time left of invulnerability
    int timeLeft;
};

#endif /* InvulnerableToDamageComponent_hpp */
