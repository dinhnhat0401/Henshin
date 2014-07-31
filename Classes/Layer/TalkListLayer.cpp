//
//  TalkListLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "TalkListLayer.h"

bool TalkList::init()
{
    if(!Layer::init()) return false;
    auto label = cocos2d::Label::createWithSystemFont("Talk Layer", "Arial", 35);
    label->setPosition(0,0);
    this->addChild(label);
    
    // your init
    
    return true;
};
