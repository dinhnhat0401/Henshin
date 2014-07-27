//
//  DNKGirlChatTableviewCell.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/26.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKFriendChatTableViewCell.h"
#include <UIButton.h>
#include <UIImageView.h>
#include <UIText.h>
#include <string.h>
#include "DNKOption.h"
#include "DNKItem.h"
#include "DNKTalk.h"
USING_NS_CC;

DNKFriendChatTableViewCell* DNKFriendChatTableViewCell::initCell(DNKCharacterInfo *characterInfo){
    
    _characterInfo = characterInfo;
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    auto bg = Sprite::create();
//    bg->setAnchorPoint(Vec2(0, 0));
//    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height*.2));
//    bg->setColor(Color3B(230,230,230));
//    this->addChild(bg);
//    
//    auto line = Sprite::create();
//    line->setAnchorPoint(Vec2(0, 0));
//    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
//    line->setColor(Color3B(100,100,100));
//    this->addChild(line);
    
    cocos2d::ui::ImageView* bgImage = cocos2d::ui::ImageView::create("11icon.png");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
//    auto image = Sprite::create("detail.png");
//    image->setScale(0.25);
//    image->setAnchorPoint(Vec2(0.5, 0.5));
//    image->setPosition(Vec2(50, visibleSize.height*0.1));
//    this->addChild(image);
    
    auto text = StringUtils::format("Cell 10");
    auto label = Label::createWithSystemFont(text.c_str(), "Arial", 30);
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(Vec2(visibleSize.width - 100, visibleSize.height*.1));
    label->setColor(Color3B(100,100,100));
    this->addChild(label);
    
   
    
    return this;
}