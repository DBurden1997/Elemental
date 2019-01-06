//
//  RenderSystem.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef RenderSystem_hpp
#define RenderSystem_hpp

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "ISystem.hpp"
#include "GameTexture.hpp"
#include "IEntity.hpp"
#include "TextureManager.hpp"

class RenderSystem : public ISystem {
public:
    //Constructors
    RenderSystem();
    RenderSystem( std::vector< IEntity* >* allEntities, SDL_Renderer* renderer );
    
    //Destructor
    ~RenderSystem();

    //Call other render functions
    void render();
private:
    //Render the level background
    void renderBackground();

    //Render the entities with correct components
    void renderEntities();

    //Texture manager object
    TextureManager* textureManager;

    //Renderer for rendering images
    SDL_Renderer* renderer;
};

#endif /* RenderSystem_hpp */
