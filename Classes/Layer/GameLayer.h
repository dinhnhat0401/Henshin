//
//  GameLayer.h
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__GameLayer__
#define __Henshin__GameLayer__

#include "cocos2d.h"

class Game : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(Game);
};

#endif /* defined(__Henshin__GameLayer__) */
