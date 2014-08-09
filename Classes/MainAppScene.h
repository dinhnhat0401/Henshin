//
//  MainAppScene.h
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__MainAppScene__
#define __Henshin__MainAppScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Layer/MainMenuLayer.h"
USING_NS_CC_EXT;

class MainApp : public cocos2d::Scene
{
    private:
        static MainApp* global;
        int currentState;
        int headerHeight;
        int footerHeight;
        int currentChara;
    cocos2d::Label * unReadLabel;
    public:
        virtual bool init();
    static MainApp* getInstance();
    static MainApp* createNew();
    void changeState(int state);
    void removeState(int state);
    void setCurrentChara(int chara_id);
    
    void SetUnreadLabel(int unread);

};

#endif /* defined(__Henshin__MainAppScene__) */
