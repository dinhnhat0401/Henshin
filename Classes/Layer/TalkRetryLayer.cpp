//
//  TalkRetryLayer.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/08/15.
//  Copyright (c) 2014年 DNK. All rights reserved.
//

#include "TalkRetryLayer.h"
#include <UIImageView.h>
#include "DNKConstant.h"
USING_NS_CC;
using namespace std;
using namespace ui;
bool TalkRetry::init()
{
    if(!LayerColor::init()) return false;
    zPos = 0;
    visibleSize = Director::getInstance()->getVisibleSize();
    
    ImageView* bgImage = cocos2d::ui::ImageView::create("res/common/dlgback.png");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    ImageView* profile = ImageView::create("res/common/bg_popup.png");
    profile->setAnchorPoint(Vec2(0, 0));
    float profileX = (visibleSize.width - profile->getContentSize().width)/2;
    float profileY = (visibleSize.height - profile->getContentSize().height)/2;
    profile->setPosition(Vec2(profileX, profileY));
    this->addChild(profile, zPos++);
    
    string str = "おや、飽きられてしまいましたね。。。\n\n一体何がいけなかったのでしょうか。\n再挑戦してみてはいかがでしょうか？";
    _message = CCLabelTTF::create(str, kDEFAULT_BOLD_FONT, 30);
    _message->setColor(Color3B::BLACK);
    _message->setHorizontalAlignment(TextHAlignment::CENTER);
    _message->setAnchorPoint(Vec2(0, 0));
    _message->setPosition(Vec2(profileX + 10, profileY + 200));
    _message->setDimensions(Size(Vec2(visibleSize.width - 20, 0)));
    this->addChild(_message, zPos++);
    
    backButton = Button::create();
    backButton->setTouchEnabled(true);
    backButton->loadTextures("res/common/btn_close_l.png", "res/common/btn_close_l.png");
    backButton->setAnchorPoint(Vec2(0, 0));
    backButton->setPosition(Vec2(profileX + 6, profileY + 10));
    this->addChild(backButton, zPos++);
    
    retryButton = Button::create();
    retryButton->setTouchEnabled(true);
    retryButton->loadTextures("res/common/btn_retry.png", "res/common/btn_retry.png");
    retryButton->setAnchorPoint(Vec2(0, 0));
    retryButton->setPosition(Vec2(profileX + 310, profileY + 10));
    this->addChild(retryButton, zPos++);
    
//    goKeepList = Button::create();
//    goKeepList->setTouchEnabled(true);
//    goKeepList->loadTextures("res/common/btn_keep_list.png", "res/common/btn_keep_list.png");
//    goKeepList->setAnchorPoint(Vec2(0, 0));
//    goKeepList->setPosition(Vec2(profileX + 6, profileY + 10));
//    this->addChild(goKeepList, zPos);
    
    return true;
};

Button* TalkRetry::getBackButton()
{
    return this->backButton;
}

Button* TalkRetry::getRetryButton()
{
    return this->retryButton;
}

