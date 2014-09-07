//
//  OtherLayer.h
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#ifndef __Henshin__OtherLayer__
#define __Henshin__OtherLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstantValue.h"

#include "network/HttpClient.h"
#include <string>

USING_NS_CC_EXT;
USING_NS_CC;

class Other : public cocos2d::Layer, public TableViewDelegate, public TableViewDataSource
{
    std::vector<std::string> links ;
    std::vector<std::string> imgs ;
    std::vector<std::string> names ;
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
    
    
    
    void initTableView(cocos2d::Size size);

    bool getContentURL(const char*);
    void onHttpRequestCompleted(cocos2d::network::HttpClient* sender,
                                cocos2d::network::HttpResponse* response);
    CREATE_FUNC(Other);
};


#endif /* defined(__Henshin__OtherLayer__) */
