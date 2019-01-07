//
//  PhysicsComponent.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-13.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef PhysicsComponent_hpp
#define PhysicsComponent_hpp

#include "IComponent.hpp"
#include <vector>
#include <string>

class PhysicsComponent : public IComponent {
public:
    //Constructors
    PhysicsComponent();
    PhysicsComponent( unsigned long ownerId, int xVel = 0, int yVel = 0, int vel = 0, std::vector< float > direction = { 0, 0 } );

    //Getters and setters for velocity
    int getXVel() { return xVel; };
    void setXVel( int newXVel ) { xVel = newXVel; }
    void adjustXVel( int adjustment ) { xVel += adjustment; }
    int getYVel() { return yVel; };
    void setYVel( int newYVel ) { yVel = newYVel; }
    void adjustYVel( int adjustment ) { yVel += adjustment; }
    int getVel() { return vel; }
    void setVel( int newVel ) { vel = newVel; resetVelocities(); }
    void adjustVel( int adjustment ) { vel += adjustment; resetVelocities(); }
    
    std::vector< float > getDirection() { return direction; }
    void changeDirection( std::vector< float > newDirection ) { direction = newDirection; resetVelocities(); }
    
    //Getter and setters for moving
    bool isMoving() { return moving; }
    void startMoving() { moving = true; }
    void stopMoving() { moving = false; }

private:
    //Velocity
    int xVel;
    int yVel;
    int vel;
    
    //Normalized direction vector
    std::vector< float > direction;
    
    //Change x y components of velocity
    void resetVelocities();
    
    //Whether or not the entity is moving
    bool moving;
};

#endif /* PhysicsComponent_hpp */
