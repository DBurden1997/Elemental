//
//  ComponentFactory.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef ComponentFactory_hpp
#define ComponentFactory_hpp

#include "IComponent.hpp"
#include "tinyxml2.h"
#include "IEntity.hpp"
#include <string>

class ComponentFactory {
public:
    //Constructor
    ComponentFactory();
    
    //Create component given a tinyxml element and its owner
    static IComponent* getComponent( tinyxml2::XMLElement* component, IEntity* owner );
    
    //Create a component given an entity and component type
    static IComponent* getComponent( IEntity* owner, std::string componentType );
};

#endif /* ComponentFactory_hpp */
