//
//  MovementModifier.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-24.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef MovementModifier_hpp
#define MovementModifier_hpp

#include <string>
#include <vector>
#include "Modifier.hpp"

class MovementModifier : public Modifier {
public:
    //Constructor
    MovementModifier( unsigned long ownerId, std::string precedence, std::vector< float > direction, int velocity );
    
    //Apply this modifier and return the resulting velocities
    std::vector< int > applyModifier( int oldX, int oldY );
    
    //Update the modifier
    void updateModifier( std::vector< float > newDirection, int newVelocity );
private:
    //The velocity to be added to the base velocity
    int velocity;
    
    //X and Y components of the velocity
    int xVel;
    int yVel;
    
    //The direction of the velocity
    std::vector< float > direction;
    
    //Calculate x and y velocities
    void calculateXYComponents();
};

#endif /* MovementModifier_hpp */
