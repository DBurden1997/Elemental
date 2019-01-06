//
//  IState.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-05.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "IState.hpp"
#include "IEntity.hpp"

IState::IState( IEntity* owner, std::string type ) : owner( owner ), type( type ){  printf("State %s created\n", getType().c_str()); }
