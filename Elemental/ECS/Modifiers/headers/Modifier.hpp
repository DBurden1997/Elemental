//
//  Modifier.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-22.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Modifier_hpp
#define Modifier_hpp

#include <string>


class Modifier {
public:
    //Constructor
    Modifier( unsigned long ownerId, std::string stat, std::string precedence );
    
    //Getters and setters
    unsigned long getOwnerId() { return ownerId; }
    std::string getStat() { return stat; }
    std::string getPrecedence() { return precedence; }
    void setPlacement( int placement ) { vectorPlacement = placement; }
    int getPlacement() { return vectorPlacement; }
    
private:
    //The id of the owner entity
    unsigned long ownerId;
    
    //The stat this modifier affects
    std::string stat;
    
    //The precedence of the modifier ( order in which it is applied )
    std::string precedence;
    
    //The space within the vector it is in
    int vectorPlacement;
};

#endif /* Modifier_hpp */
