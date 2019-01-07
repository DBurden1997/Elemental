//
//  MessageInterface.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef MessageInterface_hpp
#define MessageInterface_hpp

#include "MessageTypeEnum.hpp"
#include "Message.hpp"
#include <SDL2/SDL.h>
#include <vector>

class MessageInterface {
public:
    //Constructor
    MessageInterface() {}

    //Send a message to all receivers
    void send( Message_Type mesType, IEntity* entity = nullptr, std::string str = "", IEntity* entity2 = nullptr, std::string str2 = "" );

    //Allows receivers to receive a message
    virtual void receive( Message message ) {};

    //Add a receiver
    void addReceiver( MessageInterface* newReceiver ) { receivers.push_back( newReceiver ); }

    //Get list of receivers
    std::vector< MessageInterface* > getReceivers() { return receivers; }

private:
    //List of objects that will receive messages
    static std::vector< MessageInterface* > receivers;
};

#endif /* MessageInterface_hpp */
