//
//  AnimationManager.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-29.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef AnimationManager_hpp
#define AnimationManager_hpp

#include "tinyxml2.h"
#include <stdio.h>
#include <string>
#include <vector>
#include "Frame.hpp"
#include "Animation.hpp"
#include <SDL2/SDL.h>

class AnimationManager {
public:
    //Constructor
    AnimationManager();
    
    //Destructor
    virtual ~AnimationManager();
    
    //Load a set of animations
    std::vector<Animation*> loadAnimationSet( std::string animationSetName );
    
    //Check if the requested animation is loaded
    bool isAnimation( std::string animationSetName, std::string animationName );
    
    //Return a pointer to an animation based on its name
    Animation* getAnimation( std::string animationSetName, std::string animationName );
    
private:
    //Load an animation from xml
    Animation* loadAnimation( tinyxml2::XMLElement* animation );
    //Delete all loaded animations
    void freeAnimations();
    //Delete all loaded frames of an animation
    void freeFrames( std::vector< Frame* > frameList );
    
    //Load a frame from xml
    Frame* loadFrame( tinyxml2::XMLElement* frame );
    
    //Get an animation's valid edges
    std::vector< std::string > getEdges( tinyxml2::XMLElement* edges );
    
    //List of all currently loaded textures
    static std::vector< std::vector< Animation* > > loadedAnimations;
    
    //List of animation set names
    static std::vector<std::string> setNames;
};

#endif /* AnimationManager_hpp */
