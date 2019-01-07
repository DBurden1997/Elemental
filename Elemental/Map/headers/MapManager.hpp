#ifndef MAPMANAGER_HPP_INCLUDED
#define MAPMANAGER_HPP_INCLUDED

#include <vector>
#include <string>
#include <SDL2_image/SDL_image.h>
#include "CollisionComponent.hpp"
#include "GameTexture.hpp"
#include "MapReader.hpp"
#include "TextureManager.hpp"

class MapManager {
public:
    //Constructor
    MapManager( int tileWidth, int tileHeight );
    
    //Destructor
    ~MapManager();

    //Load map with specified name into curretn data
    void loadMap( std::string mapName );

    //Render the background
    void renderMap( SDL_Renderer* aRenderer );

    //Check collisions with the background
    std::vector< int > checkMapCollision( SDL_Rect* collider );

private:
    //Tile dimensions
    int tileHeight;
    int tileWidth;

    //Vectors containing tiles to use
    std::vector< std::vector< std::vector< int > > > mapData = {};

    //Name of the currently loaded map
    std::string mapName;

    //Pointer to the tileset for the current map
    GameTexture* mapTileset = nullptr;

    //Pointer to a MapReader object
    MapReader* mapReader = nullptr;

    //Texture manager
    TextureManager* textureManager = nullptr;
};

#endif // MAPMANAGER_HPP_INCLUDED
