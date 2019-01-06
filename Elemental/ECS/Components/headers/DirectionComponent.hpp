//
//  DirectionComponent.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef DirectionComponent_hpp
#define DirectionComponent_hpp

#include <stdio.h>
#include <string>
#include "IComponent.hpp"

class DirectionComponent : public IComponent {
public:
    //Consructor
    DirectionComponent();
    DirectionComponent( unsigned long ownerId );
    
    //Getter and setter
    std::string getDirection() { return direction; }
    bool returnsOpposite() { return opposite; }
    void setOpposite( std::string isOpposite );
    void setDirection( std::string newDirection ) { direction = newDirection; }
    
private:
    //The current direction the entity is facing
    std::string direction;
    //Flag for returning opposite
    bool opposite;
};

#endif /* DirectionComponent_hpp */
