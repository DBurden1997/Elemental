//
//  ReceiverInterface.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-17.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef ReceiverInterface_hpp
#define ReceiverInterface_hpp

#include "MessageInterface.hpp"
#include "MessageTypeEnum.hpp"
#include <vector>

class ReceiverInterface : public MessageInterface {
public:
    //Constructor
    ReceiverInterface( std::vector< Message_Type > subscriptions );
    
    //Receive message types that are subscribed to
    virtual void receive( Message message ) override;
    
    //Handle a message
    virtual void handleMessage( Message message ) = 0;
    
    //Set subscriptions
    void setSubscriptions( std::vector< Message_Type > subscriptions );
private:
    //List of all message types subscribed to
    std::vector< Message_Type > subscriptions;
};

#endif /* ReceiverInterface_hpp */
