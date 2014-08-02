//
//  MainMenuLayer.h
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__MainMenuLayer__
#define __Henshin__MainMenuLayer__


#include "cocos2d.h"
#include "MainAppScene.h"
class MainMenu : public cocos2d::Layer
{
private:
    cocos2d::MenuItemImage * keepList;
    cocos2d::MenuItemImage* talkList;
    cocos2d::MenuItemImage* game;
    cocos2d::MenuItemImage* other;
    cocos2d::MenuItemSprite* header;
    cocos2d::MenuItemSprite* footer;
//    MainApp* mainApp;
public:
    
    virtual bool init();
    void onKeepList(cocos2d::Ref* sender );
    void onTalkList(cocos2d::Ref* sender);
    void onGame(cocos2d::Ref* sender);
    void onOther(cocos2d::Ref* sender);
    int getHeaderHeight();
    int getFooterHeight();
    inline void unSelectMenu();
    CREATE_FUNC(MainMenu);
};


#endif /* defined(__Henshin__MainMenuLayer__) */
