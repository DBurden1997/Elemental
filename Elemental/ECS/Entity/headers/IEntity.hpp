//
//  IEntity.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-11.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef IEntity_hpp
#define IEntity_hpp

#include "IComponent.hpp"
#include <vector>
#include <string>

class IEntity {
public:
    //Constructor
    IEntity( std::string type );

    //Destructor
    virtual ~IEntity();

    //Check if an entity has a component of a type
    template <typename T >
    bool hasComponentType();

    //Get the entity's component of a certain type
    template< typename T >
    T* getComponentType( bool remove = false );

    //Get entity id
    unsigned long getId();
    
    //Get the entity type
    std::string getType() { return type; }

    //Add a new associated component
    void addComponent( IComponent* newComponent );
    
    //Remove a component of a specified type
    template< typename T >
    void removeComponent();

    //Get list of components
    std::vector< IComponent* > getComponents();

private:
    //Increasing ID to assign to new entities
    static unsigned long nextEntityId;

    //The unique entity id for each instance
    unsigned long entityId;
    
    //The type of entity
    std::string type;

    //A list of all associated components
    std::vector< IComponent* > myComponents;
    
    //List of entity ids that have been deleted and are now free
    std::vector< unsigned long > freeEntityIds;
};

template < typename T >
bool IEntity::hasComponentType() {
    //For each component check if it is the given type then return true if it is
    for( int i = 0; i < myComponents.size(); i++ ) {
        if( myComponents[i]->isComponentType< T >() ) {
            return true;
        }
    }
    //If there is no component of the given type return false
    return false;
}

template < typename T >
T* IEntity::getComponentType( bool remove ) {
    //The component to remove
    T* returnComponent = nullptr;
    //For each component check if it is of the given type and then return a pointer to it if it is
    for( int i = 0; i < myComponents.size(); i++ ) {
        if( myComponents[i]->isComponentType< T >() ) {
            returnComponent = dynamic_cast< T* >( myComponents[i] );
            if( remove == true ) {
                myComponents.erase( myComponents.begin() + i );
            }
            return returnComponent;
        }
    }
    //Otherwise return a null pointer if there is no component of the given type
    return returnComponent;
}

template< typename T >
void IEntity::removeComponent() {
    //Get the component of the appropriate type
    T* toRemove = getComponentType< T >( true );
    
    //Delete it if it exists
    if( toRemove != nullptr ) {
        delete toRemove;
    }
}

#endif /* IEntity_hpp */
