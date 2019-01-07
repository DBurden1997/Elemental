//
//  ControlComponent.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef ControlComponent_hpp
#define ControlComponent_hpp

#include "IComponent.hpp"
#include <vector>

class ControlComponent : public IComponent {
public:
    //Constructors
    ControlComponent();
    ControlComponent( unsigned long ownerId );
};

#endif /* ControlComponent_hpp */
