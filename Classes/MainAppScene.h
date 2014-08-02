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
    public:
        virtual bool init();
    static MainApp* getInstance();
    void changeState(int state);
    void removeState(int state);

};

#endif /* defined(__Henshin__MainAppScene__) */
