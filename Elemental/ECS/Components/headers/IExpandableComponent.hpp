//
//  IExpandableComponent.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-10.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef IExpandableComponent_hpp
#define IExpandableComponent_hpp

#include <string>
#include <vector>
#include "IComponent.hpp"

class IExpandableComponent : public IComponent {
public:
    //Constructor
    IExpandableComponent( unsigned long ownerId, unsigned long typeId, std::string type, std::vector< std::string > tags = {} );
    
    virtual ~IExpandableComponent() {};
    
    //Expand component if another component of this type is added
    virtual void expandComponent( IComponent* otherComponent ) override = 0;
    
    //If this component is expandable
    virtual bool isExpanding() override { return true; };
    
    //If this component is a status effect
    virtual bool isStatus() override { return false; }
    
};

#endif /* IExpandableComponent_hpp */
