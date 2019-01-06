//
//  PlayerControlSystem.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-13.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef PlayerControlSystem_hpp
#define PlayerControlSystem_hpp

#include <SDL2/SDL.h>
#include "ISystem.hpp"
#include "IEntity.hpp"
#include "Message.hpp"
#include <vector>

class PlayerControlSystem : public ISystem {
public:
    //Constructor
    PlayerControlSystem();

    //Handle events for all entities
    virtual void handleMessage( Message message ) override;

    //Add a new controlled entity
    void addControlledEntity( IEntity* newEntity );

private:
    //Add a held button
    void holdButton( std::string button );
    //Check if button is held
    bool isButtonHeld( std::string button );
    //Release a held button
    void releaseButton( std::string button );
    
    //Get latest vertical movement button
    std::string getLatestVertical();
    //Get latest horizontal
    std::string getLatestHorizontal();
    
    //Reset movement after control is returned
    void resetMovement();
    
    //List of player controlled entities
    std::vector< IEntity* > controlledEntities;
    
    //List of held buttons
    std::vector< std::string > heldButtons;
};

#endif /* PlayerControlSystem_hpp */
