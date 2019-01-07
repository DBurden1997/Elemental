//
//  Message.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp

#include <string>
#include "MessageTypeEnum.hpp"
#include "IEntity.hpp"
#include <SDL2/SDL.h>

class Message {
public:
    //Constructor
    Message( Message_Type messageType, IEntity* entity = nullptr, std::string str = "", IEntity* entity2 = nullptr, std::string str2 = "" );

    //Getters
    Message_Type getType();
    IEntity* getEntity();
    IEntity* getEntity2();
    std::string getString();
    std::string getString2();

private:
    IEntity* entity;
    IEntity* entity2;
    Message_Type messageType;
    std::string str;
    std::string str2;
};

#endif /* Message_hpp */
