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
    DNKOption* option = new DNKOption();
    DNKSelection *selections = new DNKSelection[3]();
    
    for (int i=0; i<3; i++) {
        DNKSelection* selection = new DNKSelection();
        selection->initSelection(100, "cu lac", false);
        selections[i] = *selection;
    }
    
    option->initOption(selections);
    DNKItem* item = new DNKItem();
    item->init(10, "cai nay la cai eo gi", option);
    DNKItem *items = new DNKItem[10]();
    for (int i=0; i<10; i++) {
        items[i] = *item;
    }
    
    DNKTalk* talk = new DNKTalk();
    talk->init(items);
    
    _characterInfo = characterInfo;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height*.2));
    bg->setColor(Color3B(230,230,230));
    this->addChild(bg);
    
    auto line = Sprite::create();
    line->setAnchorPoint(Vec2(0, 0));
    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
    line->setColor(Color3B(100,100,100));
    this->addChild(line);
    
    auto text = StringUtils::format("Cell 10");
    auto label = Label::createWithSystemFont(text.c_str(), "Arial", 30);
    label->setAnchorPoint(Vec2(0, 0.5));
    label->setPosition(Vec2(visibleSize.width - 100, visibleSize.height*.1));
    label->setColor(Color3B(100,100,100));
    this->addChild(label);
    
    auto image = Sprite::create("三輪田薫4.jpg");
    image->setScale(0.15);
    image->setAnchorPoint(Vec2(0.5, 0.5));
    image->setPosition(Vec2(50, visibleSize.height*0.1));
    this->addChild(image);
    
    return this;
}