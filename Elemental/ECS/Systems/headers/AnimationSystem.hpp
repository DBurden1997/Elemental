//
//  AnimationSystem.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-28.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef AnimationSystem_hpp
#define AnimationSystem_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "IEntity.hpp"
#include "ISystem.hpp"
#include "Message.hpp"
#include "AnimationManager.hpp"
#include "Animation.hpp"

class AnimationSystem : public ISystem {
public:
    //Constructor
    AnimationSystem();
    
    //Destructor
    
    //Handle messages
    virtual void handleMessage( Message message ) override;
    
    //Change the animation state of entities
    void changeEntityState( IEntity* entity, std::string edgeName );
    
    //Update all animated entities' graphics
    void updateAnimations();
private:
    //List of all animated entities
    std::vector< IEntity* > animatedEntities;
    
    //Animation manager
    AnimationManager* animManager;
};

#endif /* AnimationSystem_hpp */
