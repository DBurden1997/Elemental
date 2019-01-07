//
//  ComponentFactory.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#include "ComponentFactory.hpp"
#include "tinyxml2.h"
#include <string>
#include "IEntity.hpp"
#include "IComponent.hpp"
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "PhysicsComponent.hpp"
#include "ControlComponent.hpp"
#include "CollisionComponent.hpp"
#include "AnimationComponent.hpp"
#include "HealthComponent.hpp"
#include "DirectionComponent.hpp"
#include "ContactDamageComponent.hpp"

ComponentFactory::ComponentFactory(){};

IComponent* ComponentFactory::getComponent( tinyxml2::XMLElement *component, IEntity* owner) {
    std::string type( component->Name() );
    //Create a Position Component
    if( type.compare( "positionComponent" ) == 0 ) {
        int xPos = component->IntAttribute( "xPos" );
        int yPos = component->IntAttribute( "yPos" );
        int anchorX = component->IntAttribute( "anchorX" );
        int anchorY = component->IntAttribute( "anchorY" );
        return new PositionComponent( owner->getId(), xPos, yPos, anchorX, anchorY );
    }
    //Create a Graphic Component
    else if( type.compare( "graphicComponent" ) == 0 ) {
        std::string spriteSheet( component->Attribute( "spriteSheet" ) );
        int spriteXPos = component->IntAttribute( "x" );
        int spriteYPos = component->IntAttribute( "y" );
        int spriteWidth = component ->IntAttribute( "w" );
        int spriteHeight = component->IntAttribute( "h" );
        return new GraphicComponent( owner->getId(), spriteSheet, spriteXPos, spriteYPos, spriteWidth, spriteHeight );
    }
    //Create a Physics Component
    else if ( type.compare( "physicsComponent" ) == 0 ) {
        return new PhysicsComponent( owner->getId() );
    }
    //Create a Control Component
    else if( type.compare( "controlComponent" ) == 0 ) {
        return  new ControlComponent( owner->getId() );
    }
    //Create a Collision Component
    else if( type.compare( "collisionComponent" ) == 0 ) {
        PositionComponent* position = owner->getComponentType< PositionComponent >();
        int colWidth = component->IntAttribute( "colWidth" );
        int colHeight = component->IntAttribute( "colHeight" );
        std::string type( component->Attribute( "type" ) );
        return new CollisionComponent( owner->getId(), type, position->getXPos(), position->getYPos(), colWidth, colHeight );
    }
    //Create an Animation Component
    else if( type.compare( "animationComponent" ) == 0 ) {
        std::string animationSet( component->Attribute( "animationSet" ) );
        std::string animationState( component->Attribute( "animationState" ) );
        printf( "Animation Set: %s State: %s\n", animationSet.c_str(), animationState.c_str() );
        return new AnimationComponent( owner->getId(), animationSet, animationState );
    }
    else if( type.compare( "healthComponent" ) == 0 ) {
        int maxHealth = component->IntAttribute( "max" );
        return new HealthComponent( owner->getId(), maxHealth );
    }
    else if( type.compare( "contactDamageComponent" ) == 0 ){
        int damageAmount = component->IntAttribute( "damageAmount" );
        bool damageEnemy = component->IntAttribute( "damageEnemy" );
        bool damageAlly = component->IntAttribute( "damageAlly" );
        return new ContactDamageComponent( owner->getId(), damageAmount, damageEnemy, damageAlly );
    }
    else if( type.compare( "directionComponent" ) == 0 ) {
        return new DirectionComponent( owner->getId() );
    }
    //If there is no matching identifier return nullptr
    else {
        printf( "No matching component found!\n" );
        return nullptr;
    }
}

IComponent* ComponentFactory::getComponent( IEntity *owner, std::string componentType ) {
    //Create a document
    tinyxml2::XMLDocument entityData;
    
    //Load the file and check for success
    tinyxml2::XMLError eResult = entityData.LoadFile( "Data/entityInfo.xml" );
    if( eResult != 0 ) {
        printf( "Unable to load file: %s\nError: %s\n", "Data/entityInfo.xml", entityData.ErrorStr() );
        return nullptr;
    }
    
    //Get root document node
    tinyxml2::XMLNode* root = entityData.FirstChildElement( "entityInfo" );
    if( root == nullptr ) {
        printf( "Document not named: %s!\n", "entityInfo" );
        return nullptr;
    }
    
    //Get pointer to correct entity
    tinyxml2::XMLNode* entity = root->FirstChildElement( owner->getType().c_str() );
    if( entity == nullptr ) {
        printf( "Unable to find playerEntity data!\n" );
        return nullptr;
    }
    
    //Get the component details for the component
    tinyxml2::XMLElement* component = entity->FirstChildElement( componentType.c_str() );
    
    //Get the component variables
    IComponent* returnComponent = getComponent( component, owner );
    
    //Return the component
    return returnComponent;
}
