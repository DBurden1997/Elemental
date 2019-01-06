//
//  KnockBackComponent.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-08.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "KnockBackComponent.hpp"
#include "ComponentTypeEnum.hpp"
#include "ModifierHandler.hpp"

KnockBackComponent::KnockBackComponent() : StatusEffect( 0, KNOCK_BACK_COMP, "KnockBack", {} ), moveMod( nullptr ) {}

KnockBackComponent::KnockBackComponent( unsigned long ownerId, std::vector< float > direction, int initialVelocity, int slowDownFrame, double percentage ) : StatusEffect( ownerId, KNOCK_BACK_COMP, "KnockBack", { "Deteriorating", "Modifier", "Movement", "First" } ), direction( direction ), initialVelocity( initialVelocity ), currentVelocity( initialVelocity ), slowDownFrame( slowDownFrame ), percentage( percentage )
{
    moveMod = new MovementModifier( ownerId, "blank", direction, currentVelocity );
    ModifierHandler::addModifier( ownerId, "Movement", moveMod );
}

KnockBackComponent::~KnockBackComponent() {
    if( moveMod != nullptr ) {
        ModifierHandler::removeModifier( getOwnerId(), "Movement", moveMod->getPlacement() );
    }
    delete moveMod;
}

void KnockBackComponent::updateMod() {
    moveMod->updateModifier( direction, currentVelocity );
}

void KnockBackComponent::expandComponent( IComponent *otherComponent ) {
    //Cast other component as this component
    KnockBackComponent* other = dynamic_cast<KnockBackComponent*>( otherComponent );
    direction = other->direction;
    initialVelocity = other->initialVelocity;
    currentVelocity = initialVelocity;
    slowDownFrame = other->slowDownFrame;
    percentage = other->percentage;
    updateMod();
}

void KnockBackComponent::updateStatus() {
    const int TICKS_PER_FRAME = 1000 / 60;
    if( statusTimer.getTicks() >= TICKS_PER_FRAME * slowDownFrame ) {
        currentVelocity *= percentage / 100;
        updateMod();
        statusTimer.start();
    }
    
    printf( " XDir: %f, YDir: %f, Vel: %i\n", direction[0], direction[1], currentVelocity );
}
