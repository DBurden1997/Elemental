//
//  MessageTypeEnum.hpp
//  Elements
//
//  Created by Dylan Burden on 2018-07-14.
//  Copyright © 2018 DarkBlaze. All rights reserved.
//

#ifndef MessageTypeEnum_h
#define MessageTypeEnum_h

enum Message_Type {
    ENTITY_CREATED,
    ENTITY_REMOVED,
    COMPONENT_CREATED,
    COMPONENT_EXPANDED,
    COMPONENT_REMOVED,
    BUTTON_PRESSED,
    BUTTON_RELEASED,
    START_MOVING,
    STOP_MOVING,
    STOP_MOVEMENT,
    SET_MOVEMENT_DIRECTION,
    CHANGE_DIRECTION,
    HAS_MOVED,
    COLLISION_OCCURED,
    CHANGE_STATE,
    SET_OPPOSITE_DIRECTION
};

#endif /* MessageTypeEnum_h */
