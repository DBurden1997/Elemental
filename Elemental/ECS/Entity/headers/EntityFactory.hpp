//
//  EntityFactory.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef EntityFactory_hpp
#define EntityFactory_hpp

#include "ComponentFactory.hpp"
#include "IEntity.hpp"
#include "MessageInterface.hpp"
#include <string>

class EntityFactory {
public:
    //Constructor
    EntityFactory();
    
    //Destructor
    ~EntityFactory();

    //Create an entity of the given type
    static IEntity* getEntity( std::string entityType, std::string fileName );
};


#endif /* EntityFactory_hpp */
