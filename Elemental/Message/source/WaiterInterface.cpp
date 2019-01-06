//
//  WaitReceiverInterface.cpp
//  Elemental
//
//  Created by Dylan Burden on 2018-09-12.
//  Copyright © 2018 Elemental. All rights reserved.
//

#include "WaiterInterface.hpp"

std::vector< WaiterInterface* > WaiterInterface::waiters = {};

void WaiterInterface::checkReady() {
    for( int i = 0; i < waiters.size(); i++ ) {
        dynamic_cast<WaiterInterface*>( waiters[i] )->wait();
    }
}

void WaiterInterface::wait() {
    if( !waiting ) {
        waiters.push_back( this );
        pos = waiters.size() - 1;
    }
    else {
        if( isReady() ) {
            waiters.erase( waiters.begin() + pos );
            readyFunction();
        }
    }
}
