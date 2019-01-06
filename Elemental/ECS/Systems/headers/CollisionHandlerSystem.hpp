//
//  CollisionHandlerSystem.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-31.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef CollisionHandlerSystem_hpp
#define CollisionHandlerSystem_hpp

#include <stdio.h>
#include "ISystem.hpp"
#include "Message.hpp"

class CollisionHandlerSystem  : public ISystem {
public:
    //Constructor
    CollisionHandlerSystem();
    
    //Handle message
    virtual void handleMessage( Message message ) override;
    
private:
};

#endif /* CollisionHandlerSystem_hpp */
