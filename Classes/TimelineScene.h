//
//  TimelineScene.h
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/24.
//
//

#ifndef Henshin_TimelineScene_h
#define Henshin_TimelineScene_h

#include "Cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;

class Timeline : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Timeline);
};

#endif
