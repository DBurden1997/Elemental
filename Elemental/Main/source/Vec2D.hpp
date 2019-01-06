//
//  Vec2D.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-09-18.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Vec2D_hpp
#define Vec2D_hpp

#include <type_traits>

template < typename T, typename = typename std::enable_if< std::is_arithmetic< T >::value, T >::type >
class Vec2D {
    //The two members of the vector
    T m_first, m_second;
    
public:
    //Constructor
    Vec2D( T first, T second ) : m_first( first ), m_second( second ) {}
    
    //Get members
    const T first() const;
    const T second() const;
    
    //Operator overrides
    //Override addition
    Vec2D< T > operator+( const Vec2D< T >& ) const;
    
    //Override subtraction
    Vec2D< T > operator-( const Vec2D< T >& ) const;
    
    //Override multiplication
    Vec2D< T > operator*( const int ) const;
    Vec2D< T > operator*( const float ) const;
    //Component-wise multiplication
    float operator*( const Vec2D< T >& ) const;
    
    //Dot product
    float dot( const Vec2D< T >& ) const;
    float getLength();
    float getAngle();
    float getAngleBetween( const Vec2D< T > & ) const;
};


#endif /* Vec2D_hpp */
