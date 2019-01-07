

#include "MapManager.hpp"
#include "MapReader.hpp"
#include <stdio.h>
#include "Collision.hpp"

MapManager::MapManager( int tileWidth, int tileHeight ) : mapData( {} ), mapTileset( nullptr ), mapName( "" ), mapReader( new MapReader ),
                        tileWidth( tileWidth ), tileHeight( tileHeight ), textureManager( new TextureManager ) {}

MapManager::~MapManager() {
    //Free all textures
    textureManager->freeTextures();

    //Delete the texture manager
    delete textureManager;
    
    //Delete the map reader
    delete mapReader;
}

void MapManager::loadMap( std::string mapName ) {
    //Set the map name
    this->mapName = mapName;

    //Get the file name
    std::string fileName = "Maps/";
    fileName.append( mapName );
    fileName.append( ".lvl" );

    //Load the level map
    mapData = mapReader->readMapFile( fileName );

    //If the map tileset is not loaded
    if( textureManager->isTexture( mapName ) ) {
        mapTileset = textureManager->getTexture( mapName );
    }
    else {
        mapTileset = textureManager->loadTexture( mapName );
    }
}

void MapManager::renderMap( SDL_Renderer* aRenderer ) {
     //Create a clip for rendering the correct tile
    SDL_Rect clip = { 0, 0, tileWidth, tileHeight };
    int xPos = 0;
    int yPos = 0;

    //Iterate through the level map rendering the correct tile
    for( int row = 0; row < mapData.size(); row++ ) {
        for( int col = 0; col < mapData[0].size(); col++ ){
            xPos = col * tileWidth;
            yPos = row * tileHeight;
            clip.x = mapData[row][col][0] * tileWidth;

            //Render the tile
            mapTileset->render( aRenderer, xPos, yPos, &clip );
        }
    }
}

std::vector<int> MapManager::checkMapCollision( SDL_Rect* collider ) {
    //Vector to hold resulting collision vector
    std::vector< int > collisionVector = {};
    //Vector to hold temporary collision vector
    std::vector< std::vector< int > > collidedTiles = {};

    //For each row of tiles
    for( int row = 0; row < mapData.size(); row++ ) {
        //For each column of tiles
        for( int col = 0; col < mapData[0].size(); col++) {
            //If the tile is collidable
            if( mapData[row][col][1] ) {
                //Create two SDL rects to hold all connected collidable tiles as a single colliding box
                SDL_Rect tileColliderHorizontal = { col * tileWidth, row * tileHeight, tileWidth, tileHeight };
                SDL_Rect tileColliderVertical = { col * tileWidth, row * tileHeight, tileWidth, tileHeight };

                //While there is a collidable tile to the left move the left of the Rect further away and increase the width
                for( int left = col - 1; left >= 0 && mapData[row][left][1]; left-- ) {
                    tileColliderHorizontal.x -= tileWidth;
                    tileColliderHorizontal.w += tileWidth;
                }
                //While there is a collidable tile to the right of the collidable tile increase the width of the rect
                for( int right = col + 1; right < mapData[0].size() && mapData[row][right][1]; right++ ) {
                    tileColliderHorizontal.w += tileWidth;
                }
                //While there is a collidable tile above the current tile move the starting position of the tile up and increase the height of the rect
                for( int top = row - 1; top < mapData.size() && mapData[top][col][1]; top-- ) {
                    tileColliderVertical.y -= tileHeight;
                    tileColliderVertical.h += tileHeight;
                }
                //While there is a collidable tile below the collidable tile increase the height of the rect
                for( int bot = row + 1; bot < mapData.size() && mapData[bot][col][1]; bot++ ) {
                    tileColliderVertical.h += tileHeight;
                }

                //If there is a collision with the horizontal rect
                if( Collision::isCollision( collider, &tileColliderHorizontal ) ){
                    //Get the collision vector and update the x and y position of the collider rect
                    collisionVector = Collision::getCollisionVector( collider, &tileColliderHorizontal );
                    collider->x += collisionVector[0];
                    collider->y += collisionVector[1];
                    //Check if there is still a collision with the vertical rect
                    if( Collision::isCollision( collider, &tileColliderVertical ) ){
                        //If there is a collision get the collision vector again and set the collision vector to the sum of both vectors
                        std::vector<int> otherVector = Collision::getCollisionVector( collider, &tileColliderVertical );
                        collisionVector[0] += otherVector[0];
                        collisionVector[1] += otherVector[1];
                    }
                }
            }
        }
    }
    //Return the collision vector
    return collisionVector;
}
