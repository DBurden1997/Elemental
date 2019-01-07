//
//  ReceiverInterface.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-17.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "ReceiverInterface.hpp"
#include "MessageTypeEnum.hpp"
#include "Message.hpp"
#include <vector>

ReceiverInterface::ReceiverInterface( std::vector< Message_Type > subscriptions ) : subscriptions( subscriptions ) {
    //Add to the list of receivers
    addReceiver( this );
}

void ReceiverInterface::receive( Message message ) {
    //Check the subscription list for the message type
    for( int i = 0; i < subscriptions.size(); i++ ) {
        if( subscriptions[i] == message.getType() ) {
            //If subscribed to the message type, handle the message
            handleMessage( message );
        }
    }
}
