
#include "Collision.hpp"
#include <stdio.h>
#include <cmath>

//Namespace holding various collision checking functions
namespace Collision {
    //Check if there is a collision between two collider rects
    bool isCollision( SDL_Rect* colliderOne, SDL_Rect* colliderTwo ) {
        //Positions of the sides of the collision rects
        //First collision rect
        int left1 = colliderOne->x;
        int right1 = colliderOne->x + colliderOne->w;
        int top1 = colliderOne->y;
        int bottom1 = colliderOne->y + colliderOne->h;
        //Second collision rect
        int left2 = colliderTwo->x;
        int right2 = colliderTwo->x + colliderTwo->w;
        int top2 = colliderTwo->y;
        int bottom2 = colliderTwo->y+ colliderTwo->h;
        //Collision flag
        bool collided = true;

        if( right1 <= left2 ) {
            collided = false;
        }
        else if( left1 >= right2 ) {
            collided = false;
        }
        else if( bottom1 <= top2 ) {
            collided = false;
        }
        else if( top1 >= bottom2 ) {
            collided = false;
        }

        return collided;
    }

    //Get the collision vector between two collider rects
    std::vector< int > getCollisionVector( SDL_Rect* colliderOne, SDL_Rect* colliderTwo ) {
        //Variables to hold the penetration depths
        int xPenetration = 0;
        int yPenetration = 0;
        //Positions of the sides of the collision rects
        //First collision rect
        int left1 = colliderOne->x;
        int right1 = colliderOne->x + colliderOne->w;
        int top1 = colliderOne->y;
        int bottom1 = colliderOne->y + colliderOne->h;
        //Second collision rect
        int left2 = colliderTwo->x;
        int right2 = colliderTwo->x + colliderTwo->w;
        int top2 = colliderTwo->y;
        int bottom2 = colliderTwo->y+ colliderTwo->h;

        //Get x penetration
        //Collided from the left
        xPenetration = left2 - right1;

        //Collided from the right
        if( abs( xPenetration ) > ( right2 - left1 ) ) {
            xPenetration = right2 - left1;
        }

        //Get y penetration
        //Collided from the top
        yPenetration = top2 - bottom1;

        //Collided from the bottom
        if( abs( yPenetration ) > abs( bottom2 - top1 ) ) {
            yPenetration = bottom2 - top1;
        }

        if( abs(xPenetration) <= abs(yPenetration) ) {
            yPenetration = 0;
        }
        else if( abs(xPenetration) > abs(yPenetration) ) {
            xPenetration = 0;
        }
        return {xPenetration, yPenetration};
    }
    
    //Get the normalized vector between two points
    std::vector< float > getNormalizedVector( int x1, int y1, int x2, int y2 ) {
        //Get the vector from point 1 to point 2
        float x = x2 - x1;
        float y = y2 - y1;
        
        //Calculate the length of the vector
        float length = sqrt( (x * x) + (y * y) );
        
        //Get the normalized components
        x /= length;
        y /= length;
        
        std::vector< float > normalVector = { x, y };
        
        return normalVector;
    }
 }
