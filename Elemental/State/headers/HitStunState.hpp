//
//  HitStunState.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-06.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef HitStunState_hpp
#define HitStunState_hpp

#include <stdio.h>
#include "IState.hpp"

class HitStunState : public IState {
public:
    //Constructor
    HitStunState( IEntity* owner, std::vector< float > direction );
    
    //Destructor
    ~HitStunState();
    
    //Add components on start of state
    virtual void startState() override;
    
    //Remove components on end of state
    virtual void endState() override;
    
private:
    //Direction to pass to knock back component
    std::vector< float > direction;
};

#endif /* HitStunState_hpp */
