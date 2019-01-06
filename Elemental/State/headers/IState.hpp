//
//  IState.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-05.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef IState_hpp
#define IState_hpp

#include <string>
#include "IEntity.hpp"
#include "MessageInterface.hpp"

class IState : public MessageInterface{
public:
    //Constructor
    IState( IEntity* owner, std::string type );
    
    //Destructor
    virtual ~IState() {}
    
    //Function to add required components upon being added
    virtual void startState() = 0;
    
    //Function to remove required components upone being added
    virtual void endState() = 0;
    
    //Add component to owner
    template< typename T >
    void addComponent( T* newT);
    
    //Remove component from owner
    template< typename T >
    void removeComponent();
    
    //Pointer to the owner of the state
    IEntity* owner;
    
    //Getter
    std::string getType() { return type; }
    
private:
    std::string type;
};

template< typename T >
void IState::addComponent( T* newT ) {
    if( !( owner->hasComponentType< T >() ) ) {
        owner->addComponent( newT );
        send( COMPONENT_CREATED, owner, newT->getName() );
    }
    else {
        printf( "IS EXPANING: %i\n", newT->isExpanding());
        if( newT->isExpanding() ) {
            T* oldT = owner->getComponentType< T >();
            oldT->expandComponent( newT );
            send( COMPONENT_EXPANDED, owner, newT->getName() );
        }
    }
}

template< typename T >
void IState::removeComponent() {
    send( COMPONENT_REMOVED, owner, (new T)->getName() );
    owner->removeComponent< T >();
}

#endif /* IState_hpp */
