//
//  PositionComponent.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef PositionComponent_hpp
#define PositionComponent_hpp

#include "IComponent.hpp"
#include <vector>

//Contains the position of the object on the screen
class PositionComponent : public IComponent {
public:
    //Constructors
    PositionComponent();
    PositionComponent( unsigned long ownerId, int xPos, int yPos, int anchorX, int anchorY );

    //Getters and setters
    int getXPos() { return xPos; }
    void setXPos( int newXPos ) { xPos = newXPos; }
    void adjustXPos( int adjustment ) { xPos += adjustment; }
    int getYPos() { return yPos; }
    void setYPos( int newYPos ) { yPos = newYPos; }
    void adjustYPos( int adjustment ) { yPos += adjustment; }
    int getAnchorX() { return xPos + anchorX; }
    void setAnchorX( int newX ) { anchorX = newX; }
    int getAnchorY() { return yPos + anchorY; }
    void setAnchorY( int newY ) { anchorY = newY; }
    
    //Get a pointer to the x and y positions
    int* getXPointer() { return &xPos; }
    int* getYPointer() { return &yPos; }

    //Previous X and Y coordinates
    int prevX;
    int prevY;
private:
    //X and Y coordinates
    int xPos;
    int yPos;
    
    //Anchor point offsets
    int anchorX;
    int anchorY;
};

#endif /* PositionComponent_hpp */
