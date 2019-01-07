//
//  MessageInterface.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "MessageInterface.hpp"
#include "Message.hpp"
#include <stdio.h>

std::vector< MessageInterface* > MessageInterface::receivers;

void MessageInterface::send( Message_Type mesType, IEntity* entity, std::string str, IEntity* entity2, std::string str2 ) {
    //Create a new message with the required information
    Message newMessage( mesType, entity, str, entity2, str2 );

    //Send the message to all receivers
    for (int i = 0; i < receivers.size(); i++) {
        receivers[i]->receive( newMessage );
    }
}
