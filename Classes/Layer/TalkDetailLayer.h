//
//  TalkDetailLayer.h
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__TalkDetailLayer__
#define __Henshin__TalkDetailLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DNKCharaterInfo.h"
USING_NS_CC_EXT;
USING_NS_CC;

class TalkDetail : public cocos2d::Layer, public TableViewDelegate, public TableViewDataSource
{

private:
    Menu *optionMenu;
    Menu *selectMenu;
    Size opSize;
    Size visibleSize;
    float listSizeHeight;
    TableView* talkDetail;
    
    DNKCharacterInfo *info;
    int selected[10];       // hold number of selected info
    int numberAnswered;     // number question answered (by player)
    int numberAsked;        // number question be asked (by machine)
    int chara_id;           // id of character
    
    void settingSelectionView();
    void settingOptionMenu();
    
    int nextTime = 0;
public:
    static cocos2d::Scene* createScene(int chara_id);
    virtual bool initWithChara(int chara_id);
    
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // show or hide options
    void showOrHideOptions(cocos2d::Ref* pSender);

    // select
    void selectAnswer(cocos2d::Ref* pSender);
    
    void pushNotification();
    
    // update loop
    
    void update(float d);
    
    void loadData();
    
    void insertTalkHistory(int chara_id, int is_self,int talk_id, int option_id);
    
    static TalkDetail* create(int chara_id)
    {
        TalkDetail *pRet = new TalkDetail();
        if (pRet && pRet->initWithChara(chara_id))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
};

#endif /* defined(__Henshin__TalkDetailLayer__) */
