//
//  IComponent.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-11.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef IComponent_hpp
#define IComponent_hpp

#include <string>
#include <vector>

class IComponent {
public:
    //Constructor
    IComponent( unsigned long ownerId, unsigned long typeId, std::string type, std::vector< std::string > tags = {} );

    //Virtual Destructor
    virtual ~IComponent();

    //Check component type
    template < typename T >
    bool isComponentType();
    
    //Virtual function to override in subclass
    virtual void expandComponent( IComponent* otherComponent ) {};
    
    //If it is an expanding component, by default is false
    virtual bool isExpanding() { return false; }
    
    //If this component is a status effect
    virtual bool isStatus() { return false; }

    //Getters
    unsigned long getType() { return typeId; };
    unsigned long getOwnerId() { return ownerId; };
    std::string getName() { return type; }
    
    //Get the tags
    std::vector< std::string > getTags() { return tags; }
    bool hasTag( std::string tag );

private:
    //The EntityId of the owner of the component
    unsigned long ownerId;

    //The typeId of the component
    const unsigned long typeId;
    
    //The type name of the component
    const std::string type;
    
    //Tags for this component
    std::vector< std::string > tags;
};

template < typename T >
bool IComponent::isComponentType() {
    //If the component is of the given type return true
    if( getType() == T().getType() ) {
        return true;
    }
    //Otherwise return false
    return false;
}

#endif /* IComponent_hpp */
