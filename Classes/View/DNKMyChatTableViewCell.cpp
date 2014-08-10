//
//  DNKMyChatTableViewCell.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/26.
//  Copyright (c) 2014年 (THE) ONE of THEM. All rights reserved.
//

#include "DNKMyChatTableViewCell.h"
#include <UIButton.h>

#include <UIText.h>
#include <string.h>
#include "DNKOption.h"
#include "DNKItem.h"
#include "DNKTalk.h"
#include "DNKCommon.h"
#include "DNKConstant.h"

USING_NS_CC;

DNKMyChatTableViewCell *DNKMyChatTableViewCell::initCell(string answer, int talkTime){
    float cellHeight = DNKCommon::calculateHeightOfTalkMyCell(answer, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
    float textHeight = DNKCommon::calculateHeightOfLabel(answer, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
//    Size visibleSize = Director::getInstance()->getVisibleSize();
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
    
    cocos2d::ui::ImageView* bubbleRight = cocos2d::ui::ImageView::create("res/talk/fukisashi_u_r.png");
    bubbleRight->setAnchorPoint(Vec2(0, 0));
    bubbleRight->setPosition(Vec2(200, cellHeight - 10));
    this->addChild(bubbleRight);
    
    cocos2d::ui::ImageView* downbubble = cocos2d::ui::ImageView::create("res/talk/fukisashi_d_r.png");
    downbubble->setAnchorPoint(Vec2(0, 0));
    downbubble->setPosition(Vec2(200, cellHeight - textHeight - 10));
    this->addChild(downbubble);
    
    cocos2d::ui::ImageView* middlebubble = cocos2d::ui::ImageView::create("res/talk/fukisashi_m_r.png");
    middlebubble->setAnchorPoint(Vec2(0, 0));
    float middlebubbleHeight = bubbleRight->getPositionY() - downbubble->getPositionY() - downbubble->getContentSize().height;
    //    middlebubble->setContentSize(Size(100, 400));
    middlebubble->setScale(1, middlebubbleHeight/middlebubble->getContentSize().height);
    middlebubble->setPosition(Vec2(200, downbubble->getPositionY() + downbubble->getContentSize().height));
    this->addChild(middlebubble);
    
//    CCLabelTTF* friendName = CCLabelTTF::create(friendInfo->getName(), "MSGothic", 20);
//    friendName->setColor(Color3B::BLACK);
//    friendName->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
//    friendName->setPosition(Vec2(130, cellHeight - 30));
//    friendName->setAnchorPoint(Vec2(0, 0));
//    friendName->setDimensions(Size(Vec2(kTALK_DETAIL_POST_TEXT_WIDTH, 0)));
//    this->addChild(friendName);
    
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
    
    CCLabelTTF* lbl = CCLabelTTF::create(answer, kDEFAULT_BOLD_FONT, kTALK_DETAIL_POST_TEXT_SIZE);
    lbl->setColor(Color3B::BLACK);
    lbl->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    lbl->setPosition(Vec2(220, cellHeight - textHeight + 10));
    lbl->setAnchorPoint(Vec2(0, 0));
    lbl->setDimensions(Size(Vec2(kTALK_DETAIL_POST_TEXT_WIDTH, 0)));
    this->addChild(lbl);
    
    CCLabelTTF* timeLbl = CCLabelTTF::create(DNKCommon::convertTime(talkTime), kDEFAULT_FONT, 20);
    timeLbl->setColor(Color3B::BLACK);
    timeLbl->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    timeLbl->setAnchorPoint(Vec2(0, 0));
    timeLbl->setPosition(Vec2(150, cellHeight - textHeight + 10));
    this->addChild(timeLbl);
    
    CCLabelTTF* readed = CCLabelTTF::create("既読", kDEFAULT_FONT, 20);
    readed->setColor(Color3B::BLACK);
    readed->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    readed->setAnchorPoint(Vec2(0, 0));
    readed->setPosition(Vec2(150, cellHeight - textHeight + 40));
    this->addChild(readed);
    return this;
}