//
//  Frame.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-07-28.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Frame_hpp
#define Frame_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

struct Frame {
    //Length of the animation frame
    int length;
    
    //Clip of the spritesheet
    SDL_Rect clip;
    
    //Offset of the anchor point
    int anchorX;
    int anchorY;
    
    //Offsets of the collision rect
    int xOffset;
    int yOffset;
    
    //Dimensions of the collision rect
    int colWidth;
    int colHeight;
};

#endif /* Frame_hpp */
