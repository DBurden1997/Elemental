//
//  WalkingState.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef WalkingState_hpp
#define WalkingState_hpp

#include <stdio.h>
#include "IEntity.hpp"
#include "IState.hpp"

class WalkingState : public IState {
public:
    //Constructor
    WalkingState( IEntity* owner );
    
    //Destructor
    ~WalkingState();
    
    //Add components required for the state
    virtual void startState() override;
    
    //Remove components upon end of state
    virtual void endState() override;
};

#endif /* WalkingState_hpp */
