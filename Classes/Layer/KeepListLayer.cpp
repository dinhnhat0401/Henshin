//
//  KeepListLayer.cpp
//  Henshin
//
//  Created by duong minh khoa on 7/30/14.
//  Copyright (c) 2014 (THE) ONE of THEM. All rights reserved.
//

#include "KeepListLayer.h"
#include "DNKConstant.h"
#include <UIImageView.h>
#include "DNKKeepListViewCell.h"
#include "DNKStoreData.h"
#include "DNKStoreData.h"
#include "DBData.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace std;

bool KeepList::init()
{
    if(!Layer::init()) return false;
    visibleSize = Director::getInstance()->getVisibleSize();
    
    this->loadKeepList();
    
    auto bg = Sprite::create();
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
    bg->setColor(Color3B(255,255,255));
    this->addChild(bg,-999);
    
    // add Title (screen name)
//    auto titleLbl = cocos2d::Label::createWithSystemFont("キープ", kDEFAULT_FONT, 35);
//    titleLbl->setColor(Color3B::WHITE);
//    titleLbl->setAnchorPoint(Vec2(0.5, 0));
//    titleLbl->setPosition((visibleSize.width - titleLbl->getContentSize().width)/2,visibleSize.height - 20);
//    this->addChild(titleLbl, 999);
    
    keepTable = TableView::create(this, Size(visibleSize.width, visibleSize.height - 266));
    keepTable->setDelegate(this);
    keepTable->setDataSource(this);
    
    keepTable->setDirection(TableView::Direction::VERTICAL);
    keepTable->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    keepTable->setBounceable(false);
    
    keepTable->setAnchorPoint(Vec2(0, 0));
    keepTable->setPosition(Vec2(0, 180));
    
    this->addChild(keepTable, -888);
    
    return true;
};

#pragma mark - TableviewDelegate
Size KeepList::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    if (idx == 0 || idx == 2) {
        return Size(Vec2(visibleSize.width, 50));
    }
    else {
        return Size(Vec2(visibleSize.width, 90));
    }
}


TableViewCell* KeepList::tableCellAtIndex(TableView *table, ssize_t idx){

    if (idx == 0 || idx == 2) {
        TableViewCell *cell = table->dequeueCell();
        cell = new TableViewCell();
        cell->autorelease();

        ImageView* section_bg = ImageView::create("res/keep/bg_section.png");
        section_bg->setAnchorPoint(Vec2(0, 0));
        section_bg->setPosition(Vec2(0, 0));
        cell->addChild(section_bg);
        
        string headerStr = "";
        if (idx == 0) {
            headerStr = "プロフィール";
        } else {
            headerStr = "キープ";
        }
        auto headerLbl = cocos2d::Label::createWithSystemFont(headerStr, kDEFAULT_FONT, 25);
        headerLbl->setColor(Color3B::BLACK);
        headerLbl->setAnchorPoint(Vec2(0, 0));
        headerLbl->setPosition(0,0);
        cell->addChild(headerLbl, 999);
        return cell;
    } else {
        DNKKeepListViewCell *cell = (DNKKeepListViewCell*)table->dequeueCell();
        cell = new DNKKeepListViewCell();
        cell->autorelease();
        if (idx == 1) {
            cell->initCell(true, NULL, NULL);
        } else {
            int pos = (int)idx - 3;
            cell->initCell(false, keepList[pos], charaList[pos]->getCharaId());
        }

        ImageView* cell_bg = ImageView::create("res/keep/bg_list.png");
        cell_bg->setAnchorPoint(Vec2(0, 0));
        cell_bg->setPosition(Vec2(0, 0));
        cell->addChild(cell_bg);
        return cell;
    }
    
}

ssize_t KeepList::numberOfCellsInTableView(TableView *table){
    return 3 + keepList.size();
}

void KeepList::tableCellTouched(TableView* table, TableViewCell* cell){
    log("%zd番目がタップされました", cell->getIdx());
}

#pragma mark - Load data
void KeepList::loadKeepList()
{
    long int now = static_cast<long int>(time(NULL));

    DBData *db = new DBData();
//    vector<DBChara*>charaList;
    string getCharaCondition = "is_keep=1 and best_point>=70 and is_show_profile=1 and time <= " + to_string(now);

    charaList = db->getCharas(const_cast<char*>(getCharaCondition.c_str()));
    
    
    if(charaList.size() > 0){
        for (int i=0; i<charaList.size(); i++) {
            keepList.push_back(StoreData::GetInstance()->GetData(charaList[i]->getCharaId()));
        }
    }
    
}
