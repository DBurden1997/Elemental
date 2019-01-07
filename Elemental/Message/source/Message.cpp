//
//  Message.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "Message.hpp"

Message::Message( Message_Type messageType, IEntity* entity, std::string str, IEntity* entity2, std::string str2 ) : messageType( messageType ), entity( entity ), str( str ), entity2( entity2 ), str2( str2 ) {}

Message_Type Message::getType() { return messageType; };

IEntity* Message::getEntity() { return entity; };

std::string Message::getString() { return str; };

IEntity* Message::getEntity2() { return entity2; };

std::string Message::getString2() { return str2; };
