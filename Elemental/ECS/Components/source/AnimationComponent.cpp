
#include "AnimationComponent.hpp"
#include "IComponent.hpp"
#include "ComponentTypeEnum.hpp"

AnimationComponent::AnimationComponent() : IComponent( 0, ANIMATION_COMP, "Animation" ) {}

AnimationComponent::AnimationComponent( unsigned long ownerId, std::string animationSet, std::string animationState ):
    IComponent( ownerId, ANIMATION_COMP, "Animation" ), animationSet( animationSet ), animationState( animationState ),
    currentFrame( 0 ), timeSpent( 0 ), numTimesLooped( 0 ), currentAnimation( nullptr ) {}

std::vector<int> AnimationComponent::getCollisionInfo() {
    //Vector to return
    std::vector<int> info;
    //Get the x and y offsets
    info.push_back( currentAnimation->frameList[currentFrame]->xOffset );
    info.push_back( currentAnimation->frameList[currentFrame]->yOffset );
    //Get the width and height
    info.push_back( currentAnimation->frameList[currentFrame]->colWidth );
    info.push_back( currentAnimation->frameList[currentFrame]->colHeight );
    //return the vector
    return info;
}

std::vector< int > AnimationComponent::getAnchor() {
    //Vector to return
    std::vector< int > info;
    //Get the x and y coordinates of the anchor
    info.push_back( currentAnimation->frameList[currentFrame]->anchorX );
    info.push_back( currentAnimation->frameList[currentFrame]->anchorY );
    
    //Return the vector
    return info;
}

bool AnimationComponent::isValidEdge( std::string edge ) {
    //Check if edge is within valid edges and if so return true
    for( int i = 0; i < currentAnimation->validEdges.size(); i++ ) {
        if( edge.compare( currentAnimation->validEdges[i] ) == 0 ) {
            return true;
        }
    }
    //If the edge is not found return false
    return false;
}
