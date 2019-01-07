#ifndef COLLISION_HPP_INCLUDED
#define COLLISION_HPP_INCLUDED

#include <vector>
#include <SDL2_image/SDL_image.h>

namespace Collision {
    //Get collision vector to change position after a collision
    std::vector<int> getCollisionVector( SDL_Rect* colliderOne, SDL_Rect* colliderTwo );

    //Check if there is a collision
    bool isCollision( SDL_Rect* colliderOne, SDL_Rect* colliderTwo );
    
    std::vector< float > getNormalizedVector( int x1, int y1, int x2, int y2 );
}

#endif // COLLISION_HPP_INCLUDED
