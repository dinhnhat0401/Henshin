//
//  MainMenuLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "MainMenuLayer.h"
#include "MainAppScene.h"
#include "ConstantValue.h"
USING_NS_CC;

bool MainMenu::init()
{
    if(!Layer::init()) return false;
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    header = cocos2d::MenuItemSprite::create(
                                                                      cocos2d::Sprite::create("res/common/bg_header.png"),
                                                                      cocos2d::Sprite::create("res/common/bg_header.png"));
    
    footer = cocos2d::MenuItemSprite::create(
                                                                      cocos2d::Sprite::create("res/common/bg_footer.png"),
                                                                      cocos2d::Sprite::create("res/common/bg_footer.png"));
    
    
    
    keepList = cocos2d::MenuItemImage::create("res/common/btn_keep_off.png", "res/common/btn_keep_on.png",CC_CALLBACK_1(MainMenu::onKeepList,this));
    talkList = cocos2d::MenuItemImage::create("res/common/btn_talk_off.png", "res/common/btn_talk_on.png",CC_CALLBACK_1(MainMenu::onTalkList,this));
    game= cocos2d::MenuItemImage::create("res/common/btn_gf_off.png", "res/common/btn_gf_on.png",CC_CALLBACK_1(MainMenu::onGame,this));
    other= cocos2d::MenuItemImage::create("res/common/btn_other_off.png", "res/common/btn_other_on.png",CC_CALLBACK_1(MainMenu::onOther,this));
//    mainApp = MainApp::getInstance();
    
    int halfHeight = origin.y + visibleSize.height/2;
    header->setPosition(cocos2d::Vec2(0,halfHeight - header->getContentSize().height/2));
    footer->setPosition(cocos2d::Vec2(0,footer->getContentSize().height/2 -halfHeight+100));
    
    keepList->setPosition(cocos2d::Vec2(- keepList->getContentSize().width - talkList->getContentSize().width/2-15,footer->getPosition().y));
    talkList->setPosition(cocos2d::Vec2(-talkList->getContentSize().width/2-5,footer->getPosition().y));
    other->setPosition(cocos2d::Vec2(other->getContentSize().width/2+5,footer->getPosition().y));
    game->setPosition(cocos2d::Vec2(other->getContentSize().width + game->getContentSize().width/2+15,footer->getPosition().y));
    
    talkList->selected();
    
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    pMenuItems.pushBack(header);
    pMenuItems.pushBack(footer);
    pMenuItems.pushBack(keepList);
    pMenuItems.pushBack(talkList);
    pMenuItems.pushBack(game);
    pMenuItems.pushBack(other);
    
    cocos2d::Menu* menu = cocos2d::Menu::createWithArray(pMenuItems);
    this->addChild(menu);
    return true;
    
};

void MainMenu::unSelectMenu()
{
    keepList->unselected();
    talkList->unselected();
    other->unselected();
    game->unselected();
}
void MainMenu::onKeepList(cocos2d::Ref* sender)
{
    unSelectMenu();
    keepList->selected();
    MainApp::getInstance()->changeState(ConstValue::STATE_KEEP);
};

void MainMenu::onGame(cocos2d::Ref* sender)
{
    unSelectMenu();
    game->selected();
    MainApp::getInstance()->changeState(ConstValue::STATE_GAME);
};

void MainMenu::onTalkList(cocos2d::Ref* sender)
{
    unSelectMenu();
    talkList->selected();
    MainApp::getInstance()->changeState(ConstValue::STATE_TALK);
};

void MainMenu::onOther(cocos2d::Ref* sender)
{
    unSelectMenu();
    other->selected();
    MainApp::getInstance()->changeState(ConstValue::STATE_OTHER);
};

int MainMenu::getHeaderHeight() { return header->getContentSize().height;};

int MainMenu::getFooterHeight() { return footer->getContentSize().height;};
