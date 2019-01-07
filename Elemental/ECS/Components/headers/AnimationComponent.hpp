#ifndef ANIMATIONCOMPONENT_HPP_INCLUDED
#define ANIMATIONCOMPONENT_HPP_INCLUDED

#include "IComponent.hpp"
#include "Animation.hpp"
#include <SDL2/SDL.h>
#include <string>

class AnimationComponent : public IComponent {
public:
    //Constructors
    AnimationComponent();
    AnimationComponent( unsigned long ownerId, std::string animationSet, std::string animationState );
    
    //Getters and setters
    std::string getAnimationSet() { return animationSet; }
    void setAnimationSet( std::string newSet ) { animationSet = newSet; }
    
    int getCurrentFrame() { return currentFrame; }
    void nextFrame() { currentFrame++; }
    void setCurrentFrame( int frameNum ) { currentFrame = frameNum; }
    
    int getTimeSpent() { return timeSpent; }
    void increaseTimeSpent() { timeSpent++; }
    void resetTimeSpent() { timeSpent = 0; }
    
    int getTimesLooped() { return numTimesLooped; }
    void increaseTimesLooped() { numTimesLooped++; }
    void resetTimesLooped() { numTimesLooped = 0; }
    
    std::string getAnimationName() { return animationName; }
    void setAnimationName( std::string newName ) { animationName = newName; }
    
    std::string getAnimationState() { return animationState; }
    void setAnimationState( std::string newState ) { animationState = newState; }
    
    bool isValidEdge( std::string edge );
    
    //Get animation information
    std::string getAnimationId() { return currentAnimation->id; }
    SDL_Rect getClip() { return currentAnimation->frameList[currentFrame]->clip; }
    std::vector< int > getCollisionInfo();
    std::vector< int > getAnchor();
    int getFrameLength() { return currentAnimation->frameList[currentFrame]->length; }
    int getNumFrames() { return currentAnimation->numFrames; }
    std::string getEdge() { return currentAnimation->edge; }
    bool isLooping() { return currentAnimation->replay; }
    
    bool hasDirection() { return isDirected; }
    
    //Change the animation
    void setAnimation( Animation* newAnimation ) { currentAnimation = newAnimation; }

private:
    //The name of the set of animations being used
    std::string animationSet;
    
    //The current frame number
    int currentFrame;
    
    //The amount of game frames spent on current animation frame
    int timeSpent;
    
    //Number of times current animation has looped
    int numTimesLooped;

    //The current animation name
    std::string animationName;
    
    //The current animation state
    std::string animationState;
    
    //Pointer to the current animation
    Animation* currentAnimation;
    
    //Whether the current animation can be interrupted
    bool interruptable;
    
    //Whether the current animation has a direction
    bool isDirected;
};

#endif // ANIMATIONCOMPONENT_HPP_INCLUDED
