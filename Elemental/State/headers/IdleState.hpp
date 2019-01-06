//
//  IdleState.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef IdleState_hpp
#define IdleState_hpp

#include <stdio.h>
#include "IEntity.hpp"
#include "IState.hpp"

class IdleState : public IState {
public:
    //Constructor
    IdleState( IEntity* owner );
    
    //Destructor
    virtual ~IdleState();
    
    //Add components on start of state
    virtual void startState() override;
    
    //Remove components on end of state
    virtual void endState() override;
};

#endif /* IdleState_hpp */
