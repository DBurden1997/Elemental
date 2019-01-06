//
//  Modifier.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-22.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "Modifier.hpp"


Modifier::Modifier( unsigned long ownerId, std::string stat, std::string precedence ) : ownerId( ownerId ), stat( stat ), precedence( precedence ), vectorPlacement( -1 ) {}
