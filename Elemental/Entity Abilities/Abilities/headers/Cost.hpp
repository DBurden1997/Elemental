//
//  Cost.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-08-27.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef Cost_hpp
#define Cost_hpp

#include <string>
#include <map>

struct Cost{
    //Type of resource
    std::string resourceType;
    
    //Amount required
    int costAmount;
    
    //When the cost is paid
    std::string timing;
};

#endif /* Cost_hpp */
