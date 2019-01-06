//
//  MovementSystem.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-13.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef MovementSystem_hpp
#define MovementSystem_hpp

#include "ISystem.hpp"
#include "IEntity.hpp"
#include "Message.hpp"
#include "PhysicsComponent.hpp"
#include <vector>
#include <string>
#include "MovementModifier.hpp"

class MovementSystem : public ISystem {
public:
    //Constructors
    MovementSystem();

    //Handle incoming messages
    virtual void handleMessage( Message message ) override;

    //Handles entity movement
    void handleMovement();
    
private:
    //Change the direction vector of an entity
    void alterDirection( PhysicsComponent* physicsComp, std::vector< float > dirVector, bool stop = false );
    
    //Apply all movement modifications
    std::vector< int > applyModifiers( int baseXVel, int baseYVel, std::vector< Modifier* > modifiers );
    
    //Get the final displacements, including modifiers
    std::vector< int > getDisplacement( unsigned long ownerId, int baseXVel, int baseYVel );
    
    //Get the movement direction given x and y velocity components
    std::vector< int > getMovingDirection( float xVel, float yVel );
    
    //Get the directional vector given a direction number
    std::vector< float > getDirectionalVector( int direction );
};

#endif /* MovementSystem_hpp */
