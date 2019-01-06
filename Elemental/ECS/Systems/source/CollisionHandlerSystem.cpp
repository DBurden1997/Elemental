//
//  CollisionHandlerSystem.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-31.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "CollisionHandlerSystem.hpp"
#include "MessageTypeEnum.hpp"
#include "IEntity.hpp"
#include "HealthComponent.hpp"
#include "ContactDamageComponent.hpp"
#include <string>

CollisionHandlerSystem::CollisionHandlerSystem() : ISystem( COLLISION_HANDLER_SYS, { COLLISION_OCCURED } ) {}

void CollisionHandlerSystem::handleMessage( Message message ) {
    //Set the collider types
    std::string one = message.getString();
    std::string two = message.getString2();
    
    //Check the types of the colliders
    //If the first collider is the player
    if( one.compare( "player" ) == 0 ) {
        //If the second collider is the enemy
        if( two.compare( "enemy" ) == 0 ) {
            //Get the health and contact damage components of the entities
            HealthComponent* playerHealth = message.getEntity()->getComponentType<HealthComponent>();
            HealthComponent* enemyHealth = message.getEntity2()->getComponentType<HealthComponent>();
            ContactDamageComponent* playerContactDamage = message.getEntity()->getComponentType<ContactDamageComponent>();
            ContactDamageComponent* enemyContactDamage = message.getEntity2()->getComponentType<ContactDamageComponent>();
            
            //If the player has a health component and the enemy has a contact damage component
            if( playerHealth != nullptr && enemyContactDamage != nullptr ) {
                //If the enemy damages its enemies on contact
                if( enemyContactDamage->damagesEnemies() ) {
                    //Apply damage to the player
                    playerHealth->damage( enemyContactDamage->getContactDamage() );
                    printf( "Enemy dealt %i damage to player!\n Player has %i health remaining!\n",
                           enemyContactDamage->getContactDamage(), playerHealth->getCurrentHealth() );
                }
            }
            //If the enemy has a health component and the player has a contact damage component
            if( enemyHealth != nullptr && playerContactDamage != nullptr ) {
                //If the player damages enemies on contact
                if( playerContactDamage->damagesEnemies() ) {
                    //Apply damage to the enemy
                    enemyHealth->damage( playerContactDamage->getContactDamage() );
                    printf( "Player dealt %i damage to enemy!\n Enemy has %i health remaining!\n",
                           playerContactDamage->getContactDamage(), enemyHealth->getCurrentHealth() );
                }
            }
            
            send( CHANGE_STATE, message.getEntity(), "hitStun", message.getEntity2(), "directionFromOther" );
        }
    }
}
