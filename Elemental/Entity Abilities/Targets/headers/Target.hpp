//
//  Target.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-27.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Target_hpp
#define Target_hpp

#include <string>
#include <vector>
#include "WaiterInterface.hpp"
#include "IEntity.hpp"

class Target : public WaiterInterface {
public:
    //Constructor
    Target( std::string targetType );
    
    //Wait Receiver methods
    virtual bool isReady() override;
    virtual void readyFunction() override;
    
    //Get target location
    virtual void getTargetLocation() = 0;
    
    //Get the targeted entities within the target area
    virtual void getTargets() = 0;
    
    //If the target is selected
    virtual bool hasTarget() = 0;
    
    //Getters and setters
    std::string getTargetType() { return  targetType; }
    std::vector< IEntity* > getTargetedEntities() { return targetedEntities; }
    
    //Vector containing mouse x and y coordinates
    std::vector< int > mouseCoordinates;
    
private:
    //Category of the target
    std::string targetType;
    
    //List of currenty targeted entities
    std::vector< IEntity* > targetedEntities;
};

#endif /* Target_hpp */
