//
//  IAction.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-27.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef IAction_hpp
#define IAction_hpp

#include <string>
#include "WaiterInterface.hpp"

class IAction {
public:
    //Constructor
    IAction();

    //Perform the action
    virtual void performAction() {};
    
private:
    //Type of action
    std::string actionType;
    
    //Action value
    std::string actionValue;
    
    //Actions to perform on completion
    std::vector< IAction* > nextActions;
};

#endif /* IAction_hpp */
