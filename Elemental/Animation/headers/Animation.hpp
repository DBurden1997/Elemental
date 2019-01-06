//
//  Animation.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-28.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Animation_hpp
#define Animation_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Frame.hpp"

struct Animation {
    //Identifying name
    std::string id;
    
    //Edge to trigger upon completion if not repeating
    std::string edge;
    
    //A list of valid edges from this animation
    std::vector< std::string > validEdges;
    
    //If this should replay when finished
    bool replay;
    
    //Number of frames in animation
    int numFrames;
    
    //Vector of frames
    std::vector<Frame*> frameList;
}; 

#endif /* Animation_hpp */
