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

bool MainApp::init()
{
    if(!Scene::init()) return false;
    currentState = 1000;
    MainMenu* menu = MainMenu::create();
    this->addChild(menu,0,ConstValue::MENU_TAG);
    changeState(ConstValue::STATE_TALK);
    
    return true;
};

void MainApp::changeState(int state)
{
    if(currentState == state) return;
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
            tList->setPosition(xCenter,yCenter);
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
            this->removeChildByTag(ConstValue::MENU_TAG);
            TalkDetail* tDetail  = TalkDetail::create();
            tDetail->setPosition(xCenter,yCenter);
            this->addChild(tDetail,1,currentState);
            break;
        }
        default:
            break;
    }
};

void MainApp::removeState(int state)
{
    this->removeChildByTag(state);
    if(state == ConstValue::STATE_TALK_DETAIL)
    {
        MainMenu* menu = MainMenu::create();
        this->addChild(menu,0,ConstValue::MENU_TAG);
    }
};

