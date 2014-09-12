//
//  KeepListLayer.h
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__KeepListLayer__
#define __Henshin__KeepListLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "DNKCharacterInfo.h"
#include "DBChara.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace std;

class KeepList : public cocos2d::Layer, public TableViewDelegate, public TableViewDataSource
{
private:
    Size visibleSize;
    TableView *keepTable;
    vector <DNKCharacterInfo*> keepList;
    vector <DBChara*> charaList;

    void loadKeepList();
public:
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
//    virtual Size cellSizeForTable(TableView *table);
    virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    virtual bool init();
    CREATE_FUNC(KeepList);
};

#endif /* defined(__Henshin__KeepListLayer__) */
