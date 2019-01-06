//
//  IAbility.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-26.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef IAbility_hpp
#define IAbility_hpp

#include <string>
#include <vector>
#include "Cost.hpp"
#include "Target.hpp"
#include "IAction.hpp"

class IAbility{
public:
    //Constructor
    IAbility( std::string name, std::vector< std::string > classTags, std::vector< Cost > abilityCosts, Target* abilityTarget, std::vector< IAction > actionList );
    
    //Activate the ability
    virtual void activate();
    
    //Perform an action
    void performAction( IAction action );
    
private:
    //Name of the ability
    std::string name;
    
    //Class of the ability
    std::vector< std::string > classTags;
    
    //Any costs the ability requires
    std::vector< Cost > abilityCosts;
    
    //The target for the ability
    Target* abilityTarget;
    
    //List of actions to perform
    std::vector< IAction > actionList;
};

#endif /* IAbility_hpp */
