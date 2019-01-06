//
//  DirectionManager.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-10.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef DirectionSystem_hpp
#define DirectionSystem_hpp

#include <stdio.h>
#include <string>
#include "IEntity.hpp"
#include "ISystem.hpp"

class DirectionSystem : public ISystem {
public:
    //Constructor
    DirectionSystem();
    
    //Handle messages
    virtual void handleMessage( Message message ) override;
    
    //Get the current direction of an entity
    static std::string getCurrentDirection( IEntity* owner );
    
    //Get a new direction given velocities
    static std::string getNewDirection( int xVel, int yVel );
    
private:
    //Get the opposite direction
    static std::string getOppositeDirection( std::string direction );
};

#endif /* DirectionSystem_hpp */
