//
//  FriendInfoLayer.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/11.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "FriendInfoLayer.h"
#include <UIImageView.h>
USING_NS_CC;
using namespace ui;

bool FriendInfo::init()
{
    if(!Layer::init()) return false;

    cocos2d::ui::ImageView* bgImage = cocos2d::ui::ImageView::create("res/common/dlgback.png");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    auto label = cocos2d::Label::createWithSystemFont("Other Layer", "Arial", 35);
    label->setAnchorPoint(Vec2(0, 0));
    label->setPosition(0,0);
    this->addChild(label);
    return true;
};