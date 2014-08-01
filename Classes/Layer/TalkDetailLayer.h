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

class TalkDetail : public cocos2d::Layer, public TableViewDelegate, public TableViewDataSource
{

private:
    DNKCharacterInfo *info;
    int selected[10];       // hold number of selected info
    int numberAnswered;     // number question be asked (by machine)
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // TableViewDelegateがScrollViewDelegateを継承している事情で必要
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    //セルのサイズを設定
    virtual cocos2d::Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    
    //セルの中身を設定
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    
    //セルの数を設定
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //セルをタップしたときの処理
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(TalkDetail);
};

#endif /* defined(__Henshin__TalkDetailLayer__) */
