//
//  StartAppScene.h
//  Henshin
//
//  Created by hoangdieu on 8/7/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#ifndef __Henshin__StartAppScene__
#define __Henshin__StartAppScene__
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

class StartApp : public cocos2d::LayerColor
{
public:
    Sprite *logo;
    Sprite *logo1;
    Sprite *logo2;
    
    MenuItemImage *btnStart1;
    MenuItemImage *btnStart;
    MenuItemImage *btnOk;
    
    MenuItemImage *btnMale;
    MenuItemImage *btnFeMale;
    
    MenuItemImage *btnMale1;
    MenuItemImage *btnFeMale1;
    
    EditBox *name;
    
    Size visibleSize;
    Vec2 origin;
    int xCenter;
    int yCenter;
    
    //gender
    bool gender = true; //default male
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuStart(Ref* pSender);
    void menuMale(Ref* pSender);
    void menuFemale(Ref* pSender);
    
    /// register user
    void menuRegister(Ref* pSender);
    void menuStartapp(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(StartApp);
};

#endif