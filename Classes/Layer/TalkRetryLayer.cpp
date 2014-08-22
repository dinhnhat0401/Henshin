//
//  TalkRetryLayer.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/15.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "TalkRetryLayer.h"
#include <UIButton.h>
#include <UIImageView.h>
USING_NS_CC;
using namespace std;
using namespace ui;
bool TalkRetry::init()
{
    if(!LayerColor::init()) return false;
    zPos = 0;
    visibleSize = Director::getInstance()->getVisibleSize();

    ImageView* bgImage = cocos2d::ui::ImageView::create("res/common/btn_close_l.png");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    ImageView* profile = ImageView::create("res/common/bg_popup.png");
    profile->setAnchorPoint(Vec2(0, 0));
    float profileX = (visibleSize.width - profile->getContentSize().width)/2;
    float profileY = (visibleSize.height - profile->getContentSize().height)/2;
    profile->setPosition(Vec2(profileX, profileY));
    this->addChild(profile, zPos++);
    
    Button *backButton = Button::create();
    backButton->setTouchEnabled(true);
    backButton->loadTextures("res/common/btn_close_l.png", "res/common/btn_close_l.png");
    backButton->setAnchorPoint(Vec2(0, 0));
    backButton->setPosition(Vec2(profileX, profileY));
    this->addChild(backButton, zPos++);
    
    
    return true;
};