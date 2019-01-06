//
//  GetState.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef GetState_hpp
#define GetState_hpp

#include <stdio.h>
#include <string>
#include "StateTypeEnum.hpp"
#include "IEntity.hpp"
#include "IState.hpp"

IState* getState( IEntity* entity, State_Type stateType, IEntity* other = nullptr, std::string info = "" );

#endif /* GetState_hpp */
