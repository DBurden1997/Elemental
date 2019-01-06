//
//  RenderSystem.cpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-12.
//  Copyright � 2018 DarkBlaze. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "RenderSystem.hpp"
#include "IEntity.hpp"
#include "IComponent.hpp"
#include "PositionComponent.hpp"
#include "GraphicComponent.hpp"
#include "GameTexture.hpp"
#include "ComponentTypeEnum.hpp"
#include <vector>
#include "SystemTypeEnum.hpp"
#include "TextureManager.hpp"


RenderSystem::RenderSystem(): ISystem( RENDER_SYS, {} ) {}

RenderSystem::RenderSystem( std::vector< IEntity* >* allEntities, SDL_Renderer* renderer )
: ISystem( RENDER_SYS, {ENTITY_CREATED} ), renderer( renderer ), textureManager( new TextureManager ) {}

RenderSystem::~RenderSystem() {
    //Delete the texture manager
    delete textureManager;
}


void RenderSystem::render() {

    int xPos = 0;
    int yPos = 0;
    SDL_Rect* clip = nullptr;
    std::string sheetName;

    std::vector< IComponent* > entityComponents;
    for( int i = 0; i < getAllEntities()->size(); i++ ) {
        //Get the current component
        IEntity* entity = getAllEntities()->at(i);

        //Check components for the correct types
        PositionComponent* position = entity->getComponentType< PositionComponent >();
        GraphicComponent* graphic = entity->getComponentType< GraphicComponent >();

        //If the entity has a position component get relevant info
        if( position != nullptr ){
            xPos = position->getXPos();
            yPos = position->getYPos();
        }

        //If the component has a graphic component get the relevant info
        if( graphic != nullptr ){
            clip = graphic->getSpriteClip();
            sheetName = graphic->getSpriteSheet();
        }
        //If the entity has the correct components
        if( ( position != nullptr ) && ( graphic != nullptr ) ) {
            //Render the sprite
            textureManager->getTexture( sheetName )->render( renderer, xPos, yPos, clip );
        }
    }
}
