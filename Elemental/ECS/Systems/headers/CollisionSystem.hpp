//
//  CollisionSystem.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-17.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef CollisionSystem_hpp
#define CollisionSystem_hpp

#include "ISystem.hpp"
#include "CollisionComponent.hpp"
#include "MapManager.hpp"
#include <vector>

class CollisionSystem : public ISystem {
public:
    //Constructor
    CollisionSystem( MapManager* mapManager );

    //Handle events for all entities
    virtual void handleMessage( Message message ) override;

    //Check for any collisions
    void checkCollisions();

    //Handle the collisions that have occured
    void handleCollisions();

    //Add a new controlled entity
    void addCollisionEntity( IEntity* newCollisionEntity );

private:
    //Pointer to the MapManager
    MapManager* mapManager;

    //List of collision components
    static std::vector< IEntity* > collisionEntities;

    //Check collision of background and other entities
    void checkBackgroundCollisions( IEntity* entity );
    void checkEntityCollisions( IEntity* entity );
};

#endif /* CollisionSystem_hpp */
