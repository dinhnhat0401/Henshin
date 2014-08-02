//
//  TalkDetailLayer.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/24.
//
//
#include "HelloWorldScene.h"
#include "TalkDetailLayer.h"
#include <UIButton.h>
#include <UIText.h>
#include <string.h>
#include "Model.h"
#include "DNKFriendChatTableViewCell.h"
#include "DNKMyChatTableViewCell.h"
#include "FilePlists.h"
#include "DNKCommon.h"
#include "DNKConstant.h"
#include "DNKResult.h"
#include "DBData.h"

USING_NS_CC;

Scene* TalkDetail::createScene(int chara_id)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TalkDetail::create(chara_id);
    
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

bool TalkDetail::initWithChara(int chara_id)
{
    if (!Layer::init())return false;
    
    this->chara_id = chara_id;
    
    for(int i=0; i< 10; i++){
        selected[i] = -1;
    }
    // get from databse what use choiced
    selected[0] = 1;
    selected[1] = 2;
    selected[2] = 0;
    
    numberAnswered = 3;
    
    DNKOption* option = new DNKOption();
    DNKSelection *selections = new DNKSelection[3]();
    
    for (int i=0; i<3; i++) {
        DNKSelection* selection = new DNKSelection();
        selection->initSelection(100, "五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介", false);
        selections[i] = *selection;
    }
    
    option->initOption(selections);
    DNKItem* item = new DNKItem();
    item->init(10, "五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介", option);
    DNKItem *items = new DNKItem[10]();
    for (int i=0; i<10; i++) {
        items[i] = *item;
    }
    
    DNKTalk* talk = new DNKTalk();
    talk->init(items);
    
    DNKResultItem* resultItem = new DNKResultItem();
    resultItem->init("culac", "gion tan");
    
    DNKResultItem *resultItems = new DNKResultItem[3]();
    for (int i=0; i<3; i++) {
        resultItems[i] = *resultItem;
    }
    DNKResult* result = new DNKResult();
    result->init(resultItems);
    
    info = new DNKCharacterInfo();
    info->init(19, "alo", result, "aa", false, "a", "a", talk);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    cocos2d::ui::ImageView* bgImage = cocos2d::ui::ImageView::create("res/talk/bg_0.jpg");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    this->settingOptionMenu();
    
    // Add tableview
    talkDetail = TableView::create(this, Size(visibleSize.width, visibleSize.height - 170));
    talkDetail->setDirection(TableView::Direction::VERTICAL);
    talkDetail->setBounceable(true);
    talkDetail->setAnchorPoint(Vec2(0, 0));
    talkDetail->setPosition(Vec2(0, 90));
    
    talkDetail->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    talkDetail->setDelegate(this);
    addChild(talkDetail);
    talkDetail->reloadData();
    
    // Add header image
    cocos2d::ui::ImageView* imageView = cocos2d::ui::ImageView::create("res/talk/bg_header.png");
    imageView->setAnchorPoint(Vec2(0, 0));
    imageView->setPosition(Vec2(0, visibleSize.height - imageView->getContentSize().height));
    this->addChild(imageView);
    //create back button
    cocos2d::ui::Button* backButton = cocos2d::ui::Button::create();
    backButton->loadTextures("btn_back.png", "btn_back_r.png", "");
    backButton->setAnchorPoint(Vec2(0, 0));
    backButton->setPosition(Point(0, visibleSize.height - backButton->getContentSize().height - 10));
    backButton->setTouchEnabled(true);
    backButton->addTouchEventListener(CC_CALLBACK_1(TalkDetail::menuCloseCallback, this));
    this->addChild(backButton);
    
    // add Title (screen name)
    std::string str = "五十嵐信介あろほほほaaaaaaaaaaaa";
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    CCLabelTTF* lbl = CCLabelTTF::create(str, "MSGothic Bold", 34);
    lbl->setPosition(Vec2(130, visibleSize.height - 60));
    lbl->setAnchorPoint(Vec2(0, 0));
    lbl->setDimensions(Size(visibleSize.width - 130 * 2, 40));
    this->addChild(lbl);
    
    // Add heart image
    cocos2d::ui::ImageView* heart = cocos2d::ui::ImageView::create("res/talk/heart_off.png");
    heart->setAnchorPoint(Vec2(0, 0));
    heart->setPosition(Vec2(visibleSize.width - 125, visibleSize.height - heart->getContentSize().height - 15));
    this->addChild(heart);
    
    this->settingSelectionView();
    
    FilePlists* plist = new FilePlists();
    string fileName = "chara_talk/chara_talk_" + to_string(this->chara_id) + ".plist";
    plist->readFile("chara_talk/chara_talk_1.plist");
    DNKCharacterInfo *userInfor = plist->getValues();
    log("charaid === %d", this->chara_id);
    DBData *db = new DBData();
    DBTalkHistory *talkHistory;
    char condition[] = "chara_id = 11 LIMIT 10";
    
    talkHistory = db->getTalkHistorys(condition);
    log("ALo %d",talkHistory[3].getCharaId());
    
    return true;
}

#pragma mark - setting view functions
void TalkDetail::settingOptionMenu()
{
    auto listOptionBg = MenuItemImage::create("res/talk/bg_list.png", "res/talk/bg_list.png");
    listOptionBg->setAnchorPoint(Vec2(0, 0));
    listOptionBg->setPosition(Vec2(0, 0));
    listOptionBg->setScale(1, 90/listOptionBg->getContentSize().height);
    
    auto showOptionButton = MenuItemImage::create("res/talk/btn_close.png",
                                                  "res/talk/btn_close.png",
                                                  CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    showOptionButton->setAnchorPoint(Vec2(0, 0));
    showOptionButton->setPosition(Vec2(visibleSize.width - showOptionButton->getContentSize().width, 10));
    
    auto showOptionText = MenuItemImage::create("res/talk/bg_text.png",
                                                "res/talk/bg_text.png",
                                                CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    showOptionText->setAnchorPoint(Vec2(0, 0));
    showOptionText->setPosition(Vec2(showOptionButton->getPosition().x - showOptionText->getContentSize().width - 10, 10));
    
    auto helpButton = MenuItemImage::create(
                                            "res/talk/btn_stamp.png",
                                            "res/talk/btn_stamp_r.png",
                                            CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    helpButton->setAnchorPoint(Vec2(0, 0));
    helpButton->setPosition(Vec2(10, 10));
    
    optionMenu = Menu::create(listOptionBg, helpButton, showOptionText, showOptionButton, NULL);
    optionMenu->setPosition(Vec2(0, 0));
    this->addChild(optionMenu, 2);
}


void TalkDetail::settingSelectionView(){
    std::string str = "五十嵐信介あろほほほaaaaaaaaaaaa";
    // config options
    auto op1 = MenuItemImage::create("res/talk/btn_option.png",
                                     "res/talk/btn_option.png",
                                     CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    
    
    op1->setAnchorPoint(Vec2(0, 0));
    opSize = op1->getContentSize();
    
    auto bgSelect = MenuItemImage::create("res/talk/bg_list_r.png", "res/talk/bg_list_r.png");
    bgSelect->setAnchorPoint(Vec2(0, 0));
    bgSelect->setPosition(Vec2(0, 0));
    bgSelect->setScale(1, (3*opSize.height + 4*kPADDING)/bgSelect->getContentSize().height);
    bgSelect->setPosition(0, 0);
    
    float xPos = (visibleSize.width - opSize.width) / 2.0f;
    op1->setPosition(Vec2(xPos, 2 * opSize.height + 3 * kPADDING));
    
    auto op2 = MenuItemImage::create("res/talk/btn_option.png",
                                     "res/talk/btn_option.png",
                                     CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    op2->setAnchorPoint(Vec2(0, 0));
    op2->setPosition(Vec2(xPos, opSize.height + 2 * kPADDING));
    
    auto op3 = MenuItemImage::create("res/talk/btn_option.png",
                                     "res/talk/btn_option.png",
                                     CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    op3->setAnchorPoint(Vec2(0, 0));
    op3->setPosition(Vec2(xPos, kPADDING));
    
    float lblHeight = 0;
    lblHeight = DNKCommon::calculateHeightOfLabel(str, 30, visibleSize.width - kPADDING);
    
    CCLabelTTF* tmpLbl1 = CCLabelTTF::create("私はだれですか", "MSGothic", 30);
    tmpLbl1->setColor(Color3B::BLACK);
    tmpLbl1->setDimensions(Size(visibleSize.width - kPADDING, lblHeight));
    tmpLbl1->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    tmpLbl1->setAnchorPoint(Vec2(0, 0));
    tmpLbl1->setPosition(Vec2(kPADDING, (opSize.height - lblHeight)/2));
    op1->addChild(tmpLbl1, 999);
    
    CCLabelTTF* tmpLbl2 = CCLabelTTF::create(str, "MSGothic", 30);
    tmpLbl2->setColor(Color3B::BLACK);
    tmpLbl2->setDimensions(Size(visibleSize.width - kPADDING, lblHeight));
    tmpLbl2->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    tmpLbl2->setAnchorPoint(Vec2(0, 0));
    tmpLbl2->setPosition(Vec2(kPADDING, (opSize.height - lblHeight)/2));
    op2->addChild(tmpLbl2, 999);
    
    CCLabelTTF* tmpLbl3 = CCLabelTTF::create(str, "MSGothic", 30);
    tmpLbl3->setColor(Color3B::BLACK);
    tmpLbl3->setDimensions(Size(visibleSize.width - kPADDING, lblHeight));
    tmpLbl3->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    tmpLbl3->setAnchorPoint(Vec2(0, 0));
    tmpLbl3->setPosition(Vec2(kPADDING, (opSize.height - lblHeight)/2));
    op3->addChild(tmpLbl3, 999);
    
    selectMenu = Menu::create(bgSelect, op1, op2, op3, NULL);
    selectMenu->setAnchorPoint(Vec2(0, 0));
    selectMenu->setPosition(Vec2(0, -selectMenu->getContentSize().height));
    this->addChild(selectMenu);
}

#pragma mark - Tableview Delegate
//Size TalkDetail::cellSizeForTable(TableView *table){
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    return Size(visibleSize.width, visibleSize.height*.2);
//}
Size TalkDetail::tableCellSizeForIndex(TableView *table, ssize_t idx){
    
    float height;
    int row = (int)idx/2;
    if(idx%2==0){ // this is a question asked by machine
        string question = info->getTalk()->getItem(row)->getQuestion();
        height = DNKCommon::calculateHeightOfTalkCell(question, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
    } else {      // this is an answer from user
        DNKSelection selection = info->getTalk()->getItem(row)->getOptions()->getSelection(selected[row]);
        string answer = selection.getAnswer();
        height = DNKCommon::calculateHeightOfTalkMyCell(answer, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size cellSize = Size(visibleSize.width, height);
    return cellSize;
}

ssize_t TalkDetail::numberOfCellsInTableView(TableView *table){
    int i = 0;
    for (i=0; i<10; i++) {
        if (selected[i] == -1) {
            break;
        }
    }
    return i + numberAnswered;
}

TableViewCell* TalkDetail::tableCellAtIndex(TableView* table, ssize_t idx){
    if(idx%2 == 0){
        DNKFriendChatTableViewCell *cell = (DNKFriendChatTableViewCell*)table->dequeueCell();
        cell = new DNKFriendChatTableViewCell();
        cell->initCell(info->getTalk()->getItem(0), info);
        cell->autorelease();
        return cell;
    }
    else {
        DNKMyChatTableViewCell *cell = (DNKMyChatTableViewCell*)table->dequeueCell();
        cell = new DNKMyChatTableViewCell();
        int row = (int)idx/2;
        DNKSelection selection = info->getTalk()->getItem(row)->getOptions()->getSelection(selected[row]);
        cell->initCell(selection);
        cell->autorelease();
        return cell;
    }
}

void TalkDetail::tableCellTouched(TableView* table, TableViewCell* cell){
    log("%zd番目がタップされました", cell->getIdx());
    //    auto newScene = TalkDetail::createScene();
    //    auto tran1 = TransitionMoveInR::create(0.3f, newScene);
    //    Director::getInstance()->replaceScene(tran1);
    //    Director::getInstance()->pushScene(TalkDetail::createScene());
}

#pragma mark - private function
void TalkDetail::menuCloseCallback(Ref* pSender)
{
    log("back press");
    //    Director::getInstance()->popScene();
    auto newScene = HelloWorld::createScene();
    auto tran1 = TransitionMoveInL::create(0.3f, newScene);
    Director::getInstance()->replaceScene(tran1);
}

void TalkDetail::showOrHideOptions(cocos2d::Ref* pSender)
{
    log("show or hide");
    float pos = 0;
    float selectPos = -(opSize.height * 3 + kPADDING * 4);
    float tableViewHeight = visibleSize.height - 180;
    float yPos = 100;
    if (optionMenu->getPosition().y == 0) {
        pos = opSize.height * 3 + kPADDING * 4;
        tableViewHeight = tableViewHeight + selectPos;
        yPos -= selectPos;
        selectPos = 0;
    }
    
    //    talkDetail->setScale(1, tableViewHeight/talkDetail->getContentSize().height);
    //    talkDetail->setContentSize(Size(Vec2(talkDetail->getContentSize().width, tableViewHeight)));
    talkDetail->setPosition(Vec2(0, yPos));
    talkDetail->setViewSize(Size(Vec2(talkDetail->getContentSize().width, tableViewHeight)));
    
    auto  actionBy = MoveTo::create(0.3f, Vec2(0, pos));
    cocos2d::Action *action = EaseIn::create(actionBy, 1);
    optionMenu->runAction(action);
    
    auto moveSelectMenu = MoveTo::create(0.3f, Vec2(0, selectPos));
    cocos2d::Action *action1 = EaseIn::create(moveSelectMenu, 1);
    selectMenu->runAction(action1);
}