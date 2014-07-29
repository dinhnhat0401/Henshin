//
//  DNKGirlChatTableviewCell.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/26.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKFriendChatTableViewCell.h"
#include <UIButton.h>

#include <UIText.h>
#include <string.h>
#include "DNKOption.h"
#include "DNKItem.h"
#include "DNKTalk.h"
#include "DNKCommon.h"
USING_NS_CC;

DNKFriendChatTableViewCell* DNKFriendChatTableViewCell::initCell(DNKItem *item){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height*.2));
    bg->setColor(Color3B(230,230,230));
    this->addChild(bg);
//    auto line = Sprite::create();
//    line->setAnchorPoint(Vec2(0, 0));
//    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
//    line->setColor(Color3B(100,100,100));
//    this->addChild(line);
    
    friendIcon = cocos2d::ui::ImageView::create("res/chara/12/icon.png");
    friendIcon->setAnchorPoint(Vec2(0, 0));
//    friendIcon->setPosition(Vec2(0, this->getBoundingBox()));
    log("%f", this->getBoundingBox().size.height);
    this->addChild(friendIcon);
    
    cocos2d::ui::ImageView* bubbleLeft = cocos2d::ui::ImageView::create("res/talk/fukisashi_u_l.png");
    bubbleLeft->setAnchorPoint(Vec2(0, 0));
    bubbleLeft->setPosition(Vec2(0, 0));
    this->addChild(bubbleLeft);
    
//    auto image = Sprite::create("detail.png");
//    image->setScale(0.25);
//    image->setAnchorPoint(Vec2(0.5, 0.5));
//    image->setPosition(Vec2(50, visibleSize.height*0.1));
//    this->addChild(image);
    
//    auto text = StringUtils::format("Cell 10");
//    auto label = Label::createWithSystemFont(text.c_str(), "Arial", 30);
//    label->setAnchorPoint(Vec2(0, 0.5));
//    label->setPosition(Vec2(visibleSize.width - 100, visibleSize.height*.1));
//    label->setColor(Color3B(100,100,100));
//    this->addChild(label);
    
    CCLabelTTF* lbl = CCLabelTTF::create(item->getQuestion(), "MSGothic", 30);
    lbl->setColor(Color3B::BLACK);
    lbl->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    lbl->setPosition(Vec2(130, 100));
    lbl->setAnchorPoint(Vec2(0, 0));
    lbl->setDimensions(Size(Vec2(300, 0)));
    this->addChild(lbl);
    
    return this;
}