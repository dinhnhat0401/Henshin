//
//  MainAppScene.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "MainAppScene.h"
#include "Layer/MainMenuLayer.h"
#include "Layer/KeepListLayer.h"
#include "Layer/OtherLayer.h"
#include "Layer/GameLayer.h"
#include "Layer/TalkListLayer.h"
#include "Layer/TalkDetailLayer.h"
#include "ConstantValue.h"
#include "DBService.h"
#include "DNKCommon.h"

MainApp*  MainApp::global = NULL;
MainApp * MainApp::getInstance()
{
    if(!global)
    {
        global = new MainApp();
        if(global && global->init())
        {
            global->autorelease();
            return global;
        }
        else
        {
            CC_SAFE_DELETE(global);
            return nullptr;
        }
        
    }
    return global;
};

MainApp* MainApp::createNew()
{
    global = new MainApp();
    global->init();
    global->autorelease();
    return global;
}

bool MainApp::init()
{
    if(!Scene::init()) return false;
    currentState = 1000;
    currentChara = 0;
    MainMenu* menu = MainMenu::create();
    headerHeight    = menu->getHeaderHeight();
    footerHeight    = menu->getFooterHeight();
    unReadLabel     = cocos2d::Label::create(StringUtils::format("0"),"Arial",30);
    this->addChild(unReadLabel, 16);
    this->addChild(menu,10,ConstValue::MENU_TAG);
    changeState(ConstValue::STATE_TALK);
    
    nextTime = 0;
    updateUnreadLabel();
    this->schedule(schedule_selector(MainApp::update),1.0);
    
    return true;
};

void MainApp::changeState(int state)
{
    if(currentState == state) return;
    if(state != ConstValue::STATE_TALK_DETAIL)
        removeState(currentState);
    currentState = state;
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    int xCenter = origin.x + visibleSize.width/2;
    int yCenter = origin.y + visibleSize.height/2;
    
    switch (state) {
        case ConstValue::STATE_KEEP:
        {
            KeepList* kList = KeepList::create();
            kList->setPosition(xCenter,yCenter);
            this->addChild(kList,1,currentState);
            break;
        }
            
        case ConstValue::STATE_TALK:
        {
            TalkList* tList = TalkList::create();
            cocos2d::Size tableSize =  cocos2d::Size(visibleSize.width,visibleSize.height - headerHeight - footerHeight);
            tList->initTableView(tableSize);
            this->addChild(tList,1,currentState);
            break;
        }
        case ConstValue::STATE_OTHER:
        {
            Other* other = Other::create();
            other->setPosition(xCenter,yCenter);
            this->addChild(other,1,currentState);
            break;
        }
        case ConstValue::STATE_GAME:
        {
            Game* game = Game::create();
            game->setPosition(xCenter,yCenter);
            this->addChild(game,1,currentState);
            break;
        }
        case ConstValue::STATE_TALK_DETAIL:
        {
            auto scene = TalkDetail::createScene(currentChara);
            Director::getInstance()->replaceScene(scene);
            break;
        }
        default:
            break;
    }
};

void MainApp::removeState(int state)
{

    if(state != ConstValue::STATE_TALK_DETAIL)
    {
        this->removeChildByTag(state);
    }
  
};

void MainApp::setCurrentChara(int chara_id)
{
    currentChara = chara_id;
}

void MainApp::SetUnreadLabel(int unread)
{
    if(unread <= 0)
    {
        unReadLabel->setVisible(false);
        return;
    }
    unReadLabel->setVisible(true);
    auto sprite = cocos2d::Sprite::create("res/common/batch.png");
    sprite->setPosition(Vec2(290,80));
    unReadLabel->setPosition(sprite->getPosition());
    unReadLabel->setString(StringUtils::format("%d",unread));
    this->addChild(sprite,15);
}

void MainApp::update(float d)
{
    if(nextTime > 0)
    {
        long int t = static_cast<long int>(time(NULL));
        if(t >= nextTime)
        {
            updateUnreadLabel();
            TalkList *tl = (TalkList *)this->getChildByTag(ConstValue::STATE_TALK);
            if(tl != nullptr)
            {
                tl->rlData();
            }
        }
    }

}

void MainApp::updateUnreadLabel()
{
    DNKCommon::updateTalk(0);
    long int t = static_cast<long int>(time(NULL));
    nextTime = db->getNextTimeLine(t);
    int unread = DBService::getUnreadNum();
    printf(" read -- %d",unread);
    SetUnreadLabel(unread);
}