//
//  TalkListLayer.h
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__TalkListLayer__
#define __Henshin__TalkListLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstantValue.h"
#include "TimeLineItem.h"
#include "DBTalkNext.h"

USING_NS_CC_EXT;


class TalkList : public cocos2d::Layer, public TableViewDelegate, public TableViewDataSource
{
private:
    std::vector<TimeLineItem*> listItem ;
    long int nextTime;
    TableView * tbv;
public:
    virtual bool init();


    virtual void scrollViewDidZoom(ScrollView* view){};
    virtual void scrollViewDidScroll(ScrollView* view){};
    

    virtual cocos2d::Size cellSizeForTable(TableView* table);
    
    //セルの中身を設定
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    
    //セルの数を設定
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //セルをタップしたときの処理
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    
    // loop
//    void update(float d);
     void rlData(DBTalkNext* talkNext);
    
    
    void initTableView(cocos2d::Size size);
    vector<string> split(char* str,const char* delim);
    void loadData();
    
    static bool sortFunc(TimeLineItem * a,TimeLineItem * b);
    static bool compareFunc(TimeLineItem *a, int chara_id);

    CREATE_FUNC(TalkList);
};

#endif /* defined(__Henshin__TalkListLayer__) */
