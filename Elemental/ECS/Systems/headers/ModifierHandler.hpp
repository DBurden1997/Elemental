//
//  ModifierHandler.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-22.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef ModifierHandler_hpp
#define ModifierHandler_hpp

#include <string>
#include <vector>
#include <map>
#include "ReceiverInterface.hpp"
#include "Message.hpp"
#include "Modifier.hpp"

class ModifierHandler : public ReceiverInterface {
public:
    //Constructor
    ModifierHandler();
    
    //Handle messages
    virtual void handleMessage( Message message ) override;
    
    //Add a new modifier
    static void addModifier( unsigned long ownerId, std::string stat, Modifier* modifier );
    
    //Remove a modifier
    static void removeModifier( unsigned long ownerId, std::string stat, int placement );
    
    //Get modifiers for given entity for a given stat
    static std::vector< Modifier* > getModifierList( unsigned long ownerId, std::string stat );
private:
    //List of all modifiers
    static std::map< unsigned long, std::map< std::string, std::vector< Modifier* > > > modifiers;
};
#endif /* ModifierHandler_hpp */
