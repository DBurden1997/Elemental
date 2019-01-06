//
//  AnimationManager.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-29.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "tinyxml2.h"
#include "AnimationManager.hpp"
#include "Animation.hpp"
#include <vector>
#include <string>
#include <stdio.h>

std::vector< std::vector< Animation* > > AnimationManager::loadedAnimations = {};

std::vector< std::string > AnimationManager::setNames = {};

AnimationManager::AnimationManager() {};

AnimationManager::~AnimationManager() {
    //Delete all allocated animation objects
    freeAnimations();
}

Frame* AnimationManager::loadFrame( tinyxml2::XMLElement* frame ) {
    //Frame to return
    Frame* newFrame = new Frame;
    
    //Get the frame length
    newFrame->length = frame->IntAttribute( "length" );
    
    //Get the frames clip rect details
    tinyxml2::XMLElement* clip = frame->FirstChildElement( "clip" );
    newFrame->clip.x = clip->IntAttribute( "x" );
    newFrame->clip.y = clip->IntAttribute( "y" );
    newFrame->clip.w = clip->IntAttribute( "w" );
    newFrame->clip.h = clip->IntAttribute( "h" );
    
    //Get the anchor details
    tinyxml2::XMLElement* anchor = frame->FirstChildElement( "anchor" );
    newFrame->anchorX = anchor->IntAttribute( "x" );
    newFrame->anchorY = anchor->IntAttribute( "y" );
    
    //Get the collision details
    tinyxml2::XMLElement* collider = frame->FirstChildElement( "collision" );
    newFrame->xOffset = collider->IntAttribute( "x" );
    newFrame->yOffset = collider->IntAttribute( "y" );
    newFrame->colWidth = collider->IntAttribute( "w" );
    newFrame->colHeight = collider->IntAttribute( "h" );
    
    //Return the frame
    return newFrame;
}

std::vector< std::string > AnimationManager::getEdges( tinyxml2::XMLElement *edges ) {
    //Vector to return
    std::vector< std::string > validEdges;
    
    //For each edge push back its text
    for( tinyxml2::XMLElement* edge = edges->FirstChildElement("edge"); edge != nullptr; edge = edge->NextSiblingElement( "edge" ) ) {
        std::string edgeName( edge->GetText() );
        validEdges.push_back( edgeName );
    }
    
    //Return the vector of edge names
    return validEdges;
}

Animation* AnimationManager::loadAnimation( tinyxml2::XMLElement* animation ) {
    //Animation to return
    Animation* anim = new Animation;
    
    //Get data on the animation
    std::string name( animation->Attribute( "id" ) );
    anim->id = name;
    std::string anEdge( animation->Attribute( "edge" ) );
    anim->edge = anEdge;
    anim->replay = animation->IntAttribute( "replay" );
    anim->numFrames = animation->IntAttribute( "numFrames" );
    anim ->validEdges = getEdges( animation->FirstChildElement( "validEdges") );
    
    printf( "Valid edges of %s: ", name.c_str() );
    for( int i = 0; i < anim->validEdges.size(); i++ ) {
        printf( "%s ", anim->validEdges[i].c_str() );
    }
    printf( "\n" );
    
    //Get the frames of the animation
    for( tinyxml2::XMLElement* frame = animation->FirstChildElement("frame"); frame != nullptr; frame = frame->NextSiblingElement( "frame" ) ) {
        Frame* newFrame = loadFrame( frame );
        anim->frameList.push_back( newFrame );
    }
    
    //Return the animation
    return anim;
}

void AnimationManager::freeAnimations() {
    //Call delete on every animation
    for( int i = 0; i < loadedAnimations.size(); i++ ) {
        for (int j = 0; j < loadedAnimations[0].size(); j++ ) {
            //Free all Frame objects
            freeFrames( loadedAnimations[i][j]->frameList );
            //Delete the animation
            delete loadedAnimations[i][j];
        }
    }
}

void AnimationManager::freeFrames( std::vector<Frame *> frameList ) {
    for( int i = 0; i < frameList.size(); i++ ) {
        //Delete the frame
        delete frameList[i];
    }
}

std::vector< Animation* > AnimationManager::loadAnimationSet( std::string animationSetName ) {
    //The animation set to be returned
    std::vector< Animation* > animationSet = {};
    
    //Create a document
    tinyxml2::XMLDocument animationSetData;
    
    //Get the file name
    std::string fileName = "Data/";
    fileName += animationSetName;
    fileName += ".xml";
    
    //Load the file and check for success
    tinyxml2::XMLError eResult = animationSetData.LoadFile( fileName.c_str() );
    if( eResult != 0 ) {
        printf( "Unable to load file: %s\nError: %s\n", fileName.c_str(), animationSetData.ErrorStr() );
        return {};
    }
    
    //Get root document node
    tinyxml2::XMLNode* root = animationSetData.FirstChildElement( animationSetName.c_str() );
    if( root == nullptr ) {
        printf( "Document not named: %s!\n", animationSetName.c_str() );
        return {};
    }
    
    //Pointer to an animation
    Animation pointAnimation;
    
    //Load animations and add them to the animation set
    for( tinyxml2::XMLElement* animation = root->FirstChildElement("animation"); animation != nullptr; animation =  animation->NextSiblingElement("animation") ) {
        animationSet.push_back( loadAnimation( animation ) );
    }
    //Add the set name to the vector
    setNames.push_back( animationSetName );
    //Add the animation set to its vector
    loadedAnimations.push_back( animationSet );
    
    //Return the animation set
    return animationSet;
}

bool AnimationManager::isAnimation( std::string animationSetName, std::string animationName ) {
    //List number for the animation set
    int setId = -1;
    
    //Search through set names to get set ID
    for( int i = 0; i < setNames.size(); i++ ) {
        if( setNames[i] == animationSetName ) {
            setId = i;
        }
    }
    
    //Return false if the set doesnt exist
    if( setId == -1 ) {
        return false;
    }
    
    //Set the animation set
    std::vector< Animation* > animationSet = loadedAnimations[setId];
    
    //Check if the required animation is within the animation set
    for( int i = 0; i < animationSet.size(); i++ ) {
        if( animationSet[i]->id.compare(animationName) == 0 ) {
            return true;
        }
    }
    //If the animation was not found return false
    return false;
}

Animation* AnimationManager::getAnimation( std::string animationSetName, std::string animationName ) {
    //List number for the animation set
    int setId = -1;
    
    //printf("Set Name: %s, Anim Name: %s\n", animationSetName.c_str(), animationName.c_str());
    //Search through set names to get set ID
    for( int i = 0; i < setNames.size(); i++ ) {
        if( setNames[i].compare( animationSetName ) == 0 ) {
            setId = i;
        }
    }
    
    //Return false if the set doesnt exist
    if( setId == -1 ) {
        return nullptr;
    }
    
    //Set the animation set
    std::vector< Animation* > animationSet = loadedAnimations[setId];
    
    //Check if the required animation is within the animation set
    for( int i = 0; i < animationSet.size(); i++ ) {
        if( animationSet[i]->id.compare( animationName ) == 0 ) {
            return animationSet[i];
        }
    }
    //If the animation was not found return false
    return nullptr;
}



