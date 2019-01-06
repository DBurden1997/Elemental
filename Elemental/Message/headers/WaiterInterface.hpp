//
//  WaiterInterface.hpp
//  Elemental
//
//  Created by Dylan Burden on 2018-09-12.
//  Copyright © 2018 Elemental. All rights reserved.
//

#ifndef WaiterInterface_hpp
#define WaiterInterface_hpp

#include <vector>

class WaiterInterface {
public:
    //Constructor
    WaiterInterface() : waiting(false), pos( -1 ) {};
    
    //Check all waiting functions
    static void checkReady();
    
    //Set to wait
    void wait();
    
    //Function to succeed and what to do upon success
    virtual bool isReady() = 0;
    virtual void readyFunction() = 0;
    
    //Check if this is currently waiting
    bool isWaiting() { return waiting; };
    
    static std::vector< WaiterInterface* > waiters;
    
private:
    bool waiting;
    int pos;
};

#endif /* WaiterInterface_hpp */
