//
//  AnimationSystem.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-28.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "AnimationSystem.hpp"
#include "Message.hpp"
#include "AnimationManager.hpp"
#include "Animation.hpp"
#include "AnimationComponent.hpp"
#include "GraphicComponent.hpp"
#include "PositionComponent.hpp"
#include "CollisionComponent.hpp"
#include "DirectionComponent.hpp"
#include <SDL2/SDL.h>
#include <stdio.h>

AnimationSystem::AnimationSystem() : ISystem( ANIMATION_SYS, { ENTITY_CREATED, CHANGE_STATE } ), animatedEntities( {} ) {}

void AnimationSystem::handleMessage( Message message ) {
    switch ( message.getType() ) {
        //Check if created entity has required components
        case ENTITY_CREATED: {
            if( message.getEntity()->hasComponentType<GraphicComponent>() && message.getEntity()->hasComponentType<AnimationComponent>() ) {
                //Add it to the list of animated entities
                animatedEntities.push_back( message.getEntity() );
                //Get the animation component
                AnimationComponent* animComp = message.getEntity()->getComponentType<AnimationComponent>();
                //Load the animation set
                animManager->loadAnimationSet( animComp->getAnimationSet() );
                //Set its current animation
                animComp->setAnimation( animManager->getAnimation( animComp->getAnimationSet(), animComp->getAnimationState() ) );
            }
            break;
        }
        case CHANGE_STATE:{
            changeEntityState( message.getEntity(), message.getString() );
            break;
        }
        default:
            break;
    }
}

void AnimationSystem::changeEntityState( IEntity *entity, std::string edgeName ) {
    //Verify entity has an animation component
    AnimationComponent* animComp = entity->getComponentType< AnimationComponent >();
    if( animComp != nullptr ) {
        std::string animName = edgeName;
        //If the entity has a direction component
        DirectionComponent* directionComp = entity->getComponentType<DirectionComponent>();
        if( directionComp != nullptr ) {
            animName += directionComp->getDirection();
            //printf("Animation Name: %s\n\n\n\n", animName.c_str());
        }
        //Verify the edge is valid
        if( animComp->isValidEdge( animName ) ) {
            //If the state is not the same
            if( edgeName.compare( animComp->getAnimationState() ) != 0 ) {
                animComp->setAnimationName( animName );
                animComp->setAnimationState( edgeName );
                animComp->resetTimeSpent();
                animComp->resetTimesLooped();
                animComp->setCurrentFrame( 0 );
                animComp->setAnimation( animManager->getAnimation( animComp->getAnimationSet(), animName ) );
            }
            //If the state remains the same( a change in direction or somehow changing to same animation )
            else {
                animComp->setAnimationName( animName );
                animComp->setAnimation( animManager->getAnimation( animComp->getAnimationSet(), animName ) );
            }
        }
    }
    else {
        printf( "Entity does not have an animation component!\n" );
    }
}

void AnimationSystem::updateAnimations() {
    //For each animated entity
    for( int i = 0; i < animatedEntities.size(); i++ ) {
        //Get the animation and grapic component
        AnimationComponent* animComp = animatedEntities[i]->getComponentType< AnimationComponent >();
        GraphicComponent* graphicComp = animatedEntities[i]->getComponentType< GraphicComponent >();
        
        //Increase the time spent on the frame
        animComp->increaseTimeSpent();
        
        //If the frame is complete increase the frame
        if( animComp->getTimeSpent() >= animComp->getFrameLength() ) {
            animComp->resetTimeSpent();
            animComp->nextFrame();
            //If the animation has passed the end
            if( animComp->getCurrentFrame() >= animComp->getNumFrames() ) {
                //If the animation loops set it to zero
                if( animComp->isLooping() ) {
                    animComp->increaseTimesLooped();
                    animComp->setCurrentFrame( 0 );
                }
                //If the animation has an edge then change the state
                if( animComp->getEdge().compare( "none" ) != 0 ) {
                    send( CHANGE_STATE, animatedEntities[i], animComp->getEdge() );
                }
            }
        }
        
        //Set the graphic component rendering clip
        graphicComp->setSpriteClip( animComp->getClip() );
        
        //Set the anchor point if there is one
        PositionComponent* posComp = animatedEntities[i]->getComponentType<PositionComponent>();
        if( posComp != nullptr ) {
            std::vector< int > anchor = animComp->getAnchor();
            posComp->setAnchorX( anchor[0] );
            posComp->setAnchorY( anchor[1] );
        }
        
        //Set the collision offset if there's a collision component
        CollisionComponent* colComp = animatedEntities[i]->getComponentType<CollisionComponent>();
        if( colComp != nullptr ) {
            //Get collision info (xOffset, yOffset, width, height)
            std::vector< int > collideInfo = animComp->getCollisionInfo();
            colComp->setXOffset( collideInfo[0] );
            colComp->setYOffset( collideInfo[1] );
            colComp->setRectWidth( collideInfo[2] );
            colComp->setRectHeight( collideInfo[3] );
        }
    }
}
