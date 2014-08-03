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
#include "DNKConstant.h"

USING_NS_CC;

DNKFriendChatTableViewCell* DNKFriendChatTableViewCell::initCell(DNKItem *item, DNKCharacterInfo *friendInfo, int chara_id){
    string question = item->getQuestion();
    float cellHeight = DNKCommon::calculateHeightOfTalkCell(question, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
    float textHeight = DNKCommon::calculateHeightOfLabel(question, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
    Size visibleSize = Director::getInstance()->getVisibleSize();
//    auto bg = Sprite::create();
//    bg->setAnchorPoint(Vec2(0, 0));
//    bg->setTextureRect(Rect(0, 0, visibleSize.width, cellHeight));
//    bg->setColor(Color3B(230,230,230));
//    this->addChild(bg);
//    auto line = Sprite::create();
//    line->setAnchorPoint(Vec2(0, 0));
//    line->setTextureRect(Rect(0, 0, visibleSize.width, 1));
//    line->setColor(Color3B(100,100,100));
//    this->addChild(line);

    string friendIconImg = StringUtils::format("res/chara/%d/icon.png",chara_id);
    friendIcon = cocos2d::ui::ImageView::create(friendIconImg);
    friendIcon->setAnchorPoint(Vec2(0, 0));
    friendIcon->setPosition(Vec2(0, cellHeight - 90));
    this->addChild(friendIcon);
    
    cocos2d::ui::ImageView* bubbleLeft = cocos2d::ui::ImageView::create("res/talk/fukisashi_u_l.png");
    bubbleLeft->setAnchorPoint(Vec2(0, 0));
    bubbleLeft->setPosition(Vec2(100, cellHeight - 90));
    this->addChild(bubbleLeft);
    
    cocos2d::ui::ImageView* downbubble = cocos2d::ui::ImageView::create("res/talk/fukisashi_d_l.png");
    downbubble->setAnchorPoint(Vec2(0, 0));
    downbubble->setPosition(Vec2(100, cellHeight - textHeight - 80));
    this->addChild(downbubble);
    
    cocos2d::ui::ImageView* middlebubble = cocos2d::ui::ImageView::create("res/talk/fukisashi_m_l.png");
    middlebubble->setAnchorPoint(Vec2(0, 0));
    float middlebubbleHeight = bubbleLeft->getPositionY() - downbubble->getPositionY() - downbubble->getContentSize().height;
//    middlebubble->setContentSize(Size(100, 400));
    middlebubble->setScale(1, middlebubbleHeight/middlebubble->getContentSize().height);
    middlebubble->setPosition(Vec2(100, downbubble->getPositionY() + downbubble->getContentSize().height));
    this->addChild(middlebubble);
    
    CCLabelTTF* friendName = CCLabelTTF::create(friendInfo->getName(), kDEFAULT_BOLD_FONT, 20);
    friendName->setColor(Color3B::BLACK);
    friendName->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    friendName->setPosition(Vec2(130, cellHeight - 30));
    friendName->setAnchorPoint(Vec2(0, 0));
    friendName->setDimensions(Size(Vec2(kTALK_DETAIL_POST_TEXT_WIDTH, 0)));
    this->addChild(friendName);
    
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
    
    CCLabelTTF* lbl = CCLabelTTF::create(item->getQuestion(), kDEFAULT_BOLD_FONT, kTALK_DETAIL_POST_TEXT_SIZE);
    lbl->setColor(Color3B::BLACK);
    lbl->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    lbl->setPosition(Vec2(130, cellHeight - 60 - textHeight));
    lbl->setAnchorPoint(Vec2(0, 0));
    lbl->setDimensions(Size(Vec2(kTALK_DETAIL_POST_TEXT_WIDTH, 0)));
    this->addChild(lbl);
    
    return this;
}