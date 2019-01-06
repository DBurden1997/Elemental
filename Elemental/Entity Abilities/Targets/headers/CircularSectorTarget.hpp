//
//  CircularSectorTarget.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-09-12.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef CircularSectorTarget_hpp
#define CircularSectorTarget_hpp

#include "Target.hpp"

class CircularSectorTarget : public Target {
public:
    //Constructor
    CircularSectorTarget( std::string targetType, int radius, int angle, std::vector< int >* origin );
    
    //Get the target direction
    virtual void getTargetLocation() override;
    
    //Check the target area for entities
    virtual void getTargets() override;
    
    //If a target is selected
    virtual bool hasTarget() override;
    
private:
    //The radius of the circular sector
    int radius;
    
    //The angle of the circulat sector
    int angle;
    
    //The position of the center of the "Circle"
    std::vector< int >* origin;
    
    //The direction vector of the circular sector
    std::vector< float > direction;
    
    //Check whether an entity is a valid target
    bool isValidTarget( IEntity* entity );
    
};

#endif /* CircularSectorTarget_hpp */
