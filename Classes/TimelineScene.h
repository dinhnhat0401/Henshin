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

class Timeline : public cocos2d::Layer, public TableViewDelegate, public TableViewDataSource
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    // TableViewDelegateがScrollViewDelegateを継承している事情で必要
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    //セルのサイズを設定
    virtual cocos2d::Size cellSizeForTable(TableView* table);
    
    //セルの中身を設定
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    
    //セルの数を設定
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //セルをタップしたときの処理
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);

    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Timeline);
};

#endif
