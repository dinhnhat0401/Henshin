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
#include "MainAppScene.h"
#include "LocalNotification.h"
#include "DBTalkHistory.h"

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

    FilePlists* plist = new FilePlists();
    string fileName = "chara_talk/chara_talk_" + to_string(this->chara_id) + ".plist";
    plist->readFile(fileName);
    info = plist->getValues();

    for(int i=0; i< 10; i++){
        selected[i] = -1;
    }
    
    DBConnect *dbconnect= new DBConnect();
    dbconnect->getConnect();
    string getNumberAsked = "SELECT max(talk_id) from talk_history where is_self=0 and chara_id="+to_string(this->chara_id);
    dbconnect->getData(const_cast<char*>(getNumberAsked.c_str()));
    char *value1 = dbconnect->getDataIndex(1,0);
    if(value1 == NULL) {
        numberAsked = -1;
    } else {
        numberAsked = atoi(value1);
    }
    
    dbconnect->getConnect();
    string getNumber = "SELECT max(talk_id) from talk_history where is_self=1 and chara_id="+to_string(this->chara_id);
    dbconnect->getData(const_cast<char*>(getNumber.c_str()));
    char *value = dbconnect->getDataIndex(1,0);
    if(value == NULL) {
        numberAnswered = -1;
    } else {
        numberAnswered = atoi(value);
    }
    
    dbconnect->freeTable();
    dbconnect->closeDB();
    
    DBData *db = new DBData();
    vector<DBTalkHistory *> talkHistory;
    string conditionstr = "chara_id="+to_string(this->chara_id)+" and is_self=1";
    char *condition = const_cast<char*>(conditionstr.c_str());

    talkHistory = db->getTalkHistorys(condition);
//    log("ALo %d",talkHistory[2]->getOptionId());
    if(talkHistory.size() > 0){
        for (int i=0; i<=numberAnswered; i++) {
            selected[i] = talkHistory[i]->getOptionId();
            //        log("lua chon %d %d", talkHistory[i].getOptionId(), i);
        }
    }
    
//    DNKOption* option = new DNKOption();
//    DNKSelection *selections = new DNKSelection[3]();
//    
//    for (int i=0; i<3; i++) {
//        DNKSelection* selection = new DNKSelection();
//        selection->initSelection(100, "五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介", false);
//        selections[i] = *selection;
//    }
//    
//    option->initOption(selections);
//    DNKItem* item = new DNKItem();
//    item->init(10, "五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介五十嵐信介", option);
//    DNKItem *items = new DNKItem[10]();
//    for (int i=0; i<10; i++) {
//        items[i] = *item;
//    }
//    
//    DNKTalk* talk = new DNKTalk();
//    talk->init(items);
//    
//    DNKResultItem* resultItem = new DNKResultItem();
//    resultItem->init("culac", "gion tan");
//    
//    DNKResultItem *resultItems = new DNKResultItem[3]();
//    for (int i=0; i<3; i++) {
//        resultItems[i] = *resultItem;
//    }
//    DNKResult* result = new DNKResult();
//    result->init(resultItems);
//    
//    info = new DNKCharacterInfo();
//    info->init(19, "alo", result, "aa", false, "a", "a", talk);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    cocos2d::ui::ImageView* bgImage = cocos2d::ui::ImageView::create("res/talk/bg_0.jpg");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage);
    
    this->settingOptionMenu();
    
    // Add tableview
    talkDetail = TableView::create(this, Size(visibleSize.width, visibleSize.height - 180));
    talkDetail->setDirection(TableView::Direction::VERTICAL);
//    talkDetail->setBounceable(false);
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
    std::string str = info->getName();
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
    
    return true;
}

#pragma mark - setting view functions
void TalkDetail::settingOptionMenu()
{
    auto listOptionBg = MenuItemImage::create("res/talk/bg_options.png", "res/talk/bg_options.png");
    listOptionBg->setAnchorPoint(Vec2(0, 0));
    listOptionBg->setPosition(Vec2(0, 0));
    listSizeHeight = listOptionBg->getContentSize().height;
    
    auto helpButton = MenuItemImage::create(
                                            "res/talk/btn_stamp.png",
                                            "res/talk/btn_stamp_r.png");
    helpButton->setAnchorPoint(Vec2(0, 0));
    helpButton->setPosition(Vec2(10, listSizeHeight - helpButton->getContentSize().height - 10));
    
   
    
    
    auto closeButton = MenuItemImage::create("res/talk/btn_close.png",
                                                  "res/talk/btn_close.png",
                                                  CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    closeButton->setAnchorPoint(Vec2(0, 0));
    closeButton->setPosition(Vec2(visibleSize.width - closeButton->getContentSize().width, helpButton->getPosition().y));
    closeButton->setTag(100);
    
    
    MenuItemImage *showOptionText;
    MenuItemImage *openButton;
    MenuItemImage *openButtonOff;
    
    DNKItem *lastItem = info->getTalk()->getItem(numberAsked);
    DNKOption *options = lastItem->getOptions();
    // config options
    auto op1 = MenuItemImage::create("res/talk/btn_option.png",
                                     "res/talk/btn_option.png",
                                     CC_CALLBACK_1(TalkDetail::selectAnswer, this));
    
    
    op1->setAnchorPoint(Vec2(0, 0));
    opSize = op1->getContentSize();
    
    //    auto bgSelect = MenuItemImage::create("res/talk/bg_list_r.png", "res/talk/bg_list_r.png");
    //    bgSelect->setAnchorPoint(Vec2(0, 0));
    //    bgSelect->setPosition(Vec2(0, 0));
    //    bgSelect->setScale(1, (3*opSize.height + 4*kPADDING)/bgSelect->getContentSize().height);
    //    bgSelect->setPosition(0, 0);
    //
    float xPos = (visibleSize.width - opSize.width) / 2.0f;
    op1->setPosition(Vec2(xPos, 2 * opSize.height + 3 * kPADDING));
    op1->setTag(1001);
    
    auto op2 = MenuItemImage::create("res/talk/btn_option.png",
                                     "res/talk/btn_option.png",
                                     CC_CALLBACK_1(TalkDetail::selectAnswer, this));
    op2->setAnchorPoint(Vec2(0, 0));
    op2->setPosition(Vec2(xPos, opSize.height + 2 * kPADDING));
    op2->setTag(1002);
    
    auto op3 = MenuItemImage::create("res/talk/btn_option.png",
                                     "res/talk/btn_option.png",
                                     CC_CALLBACK_1(TalkDetail::selectAnswer, this));
    op3->setAnchorPoint(Vec2(0, 0));
    op3->setPosition(Vec2(xPos, kPADDING));
    op3->setTag(1003);
    
    float lblHeight = 0;
    string str = options->getSelection(0).getAnswer();
    lblHeight = DNKCommon::calculateHeightOfLabel(str, 25, visibleSize.width - kPADDING);
    
    CCLabelTTF* tmpLbl1 = CCLabelTTF::create(options->getSelection(0).getAnswer(), kDEFAULT_BOLD_FONT, 25);
    tmpLbl1->setColor(Color3B::BLACK);
    tmpLbl1->setDimensions(Size(visibleSize.width - kPADDING * 3, 0));
    tmpLbl1->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    tmpLbl1->setAnchorPoint(Vec2(0, 0));
    tmpLbl1->setPosition(Vec2(kPADDING, (opSize.height - lblHeight)/2));
    op1->addChild(tmpLbl1, 999);
    
    str = options->getSelection(1).getAnswer();
    lblHeight = DNKCommon::calculateHeightOfLabel(str, 25, visibleSize.width - kPADDING);
    CCLabelTTF* tmpLbl2 = CCLabelTTF::create(options->getSelection(1).getAnswer(), kDEFAULT_BOLD_FONT, 25);
    tmpLbl2->setColor(Color3B::BLACK);
    tmpLbl2->setDimensions(Size(visibleSize.width - kPADDING * 3, 0));
    tmpLbl2->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    tmpLbl2->setAnchorPoint(Vec2(0, 0));
    tmpLbl2->setPosition(Vec2(kPADDING, (opSize.height - lblHeight)/2));
    op2->addChild(tmpLbl2, 999);
    
    str = options->getSelection(2).getAnswer();
    lblHeight = DNKCommon::calculateHeightOfLabel(str, 25, visibleSize.width - kPADDING);
    CCLabelTTF* tmpLbl3 = CCLabelTTF::create(options->getSelection(2).getAnswer(), kDEFAULT_BOLD_FONT, 25);
    tmpLbl3->setColor(Color3B::BLACK);
    tmpLbl3->setDimensions(Size(visibleSize.width - kPADDING * 3, 0));
    tmpLbl3->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    tmpLbl3->setAnchorPoint(Vec2(0, 0));
    tmpLbl3->setPosition(Vec2(kPADDING, (opSize.height - lblHeight)/2));
    op3->addChild(tmpLbl3, 999);
    
    showOptionText = MenuItemImage::create("res/talk/bg_text.png",
                                           "res/talk/bg_text.png",
                                           CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    showOptionText->setAnchorPoint(Vec2(0, 0));
    showOptionText->setPosition(Vec2(helpButton->getPosition().x + helpButton->getContentSize().width + 10, helpButton->getPosition().y));
    showOptionText->setTag(103);
    
    openButton = MenuItemImage::create("res/talk/btn_open.png",
                                       "res/talk/btn_open.png",
                                       CC_CALLBACK_1(TalkDetail::showOrHideOptions, this));
    openButton->setAnchorPoint(Vec2(0, 0));
    openButton->setPosition(Vec2(visibleSize.width - openButton->getContentSize().width, helpButton->getPosition().y));
    openButton->setTag(101);
    
    openButtonOff = MenuItemImage::create("res/talk/btn_open_off.png",
                                          "res/talk/btn_open_off.png");
    openButtonOff->setAnchorPoint(Vec2(0, 0));
    openButtonOff->setPosition(Vec2(visibleSize.width - openButton->getContentSize().width, helpButton->getPosition().y));
    openButtonOff->setTag(102);
    optionMenu = Menu::create(listOptionBg, helpButton, showOptionText, closeButton, openButton, openButtonOff, op1, op2, op3, NULL);
    if (numberAsked <= numberAnswered) {
        showOptionText->setEnabled(false);
        openButton->setVisible(false);
        openButtonOff->setVisible(true);
    } else {
        showOptionText->setEnabled(true);
        openButton->setVisible(true);
        openButtonOff->setVisible(false);
    }
    optionMenu->setPosition(Vec2(0, 90 - listSizeHeight));
    this->addChild(optionMenu, 2);
}


void TalkDetail::settingSelectionView(){
    
    
//    selectMenu = Menu::create(bgSelect, op1, op2, op3, NULL);
//    selectMenu->setAnchorPoint(Vec2(0, 0));
//    selectMenu->setPosition(Vec2(0, -selectMenu->getContentSize().height));
//    this->addChild(selectMenu);
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
    return numberAsked + numberAnswered + 2;
}

TableViewCell* TalkDetail::tableCellAtIndex(TableView* table, ssize_t idx){
    if(idx%2 == 0){
        DNKFriendChatTableViewCell *cell = (DNKFriendChatTableViewCell*)table->dequeueCell();
        cell = new DNKFriendChatTableViewCell();
        int row = (int)idx/2;
        cell->initCell(info->getTalk()->getItem(row), info, this->chara_id);
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
    auto mApp = MainApp::createNew();
    Director::getInstance()->replaceScene(mApp);
//    log("back press");
    //    Director::getInstance()->popScene();
//    auto newScene = HelloWorld::createScene();
//    auto tran1 = TransitionMoveInL::create(0.3f, newScene);
//    Director::getInstance()->replaceScene(tran1);
}

void TalkDetail::selectAnswer(Ref* pSender){
    MenuItemImage* img = (MenuItemImage*) pSender;
    log("aaa == %d", img->getTag());
    numberAnswered++;
    int option = 0;
    switch (img->getTag()) {
        case 1001:
            option = 0;
            break;
        case 1002:
            option = 1;
            break;
        case 1003:
            option = 2;
            break;
        default:
            break;
    }
    selected[numberAnswered] = option;
    talkDetail->reloadData();
    MenuItemImage *closeBtn = (MenuItemImage*)optionMenu->getChildByTag(100);
    MenuItemImage *openBtn = (MenuItemImage*)optionMenu->getChildByTag(101);
    MenuItemImage *openBtnOff = (MenuItemImage*)optionMenu->getChildByTag(102);
    MenuItemImage *openText = (MenuItemImage*)optionMenu->getChildByTag(103);
    openBtnOff->setVisible(true);
    openBtn->setVisible(false);
    closeBtn->setVisible(false);
    openText->setEnabled(false);
    this->showOrHideOptions(NULL);
    // insert answer to db
    insertTalkHistory(chara_id, 1, numberAsked, option);
    // notification
    pushNotification();
}

void TalkDetail::showOrHideOptions(cocos2d::Ref* pSender)
{
    log("show or hide");
    MenuItemImage *closeBtn = (MenuItemImage*)optionMenu->getChildByTag(100);
    MenuItemImage *openBtn = (MenuItemImage*)optionMenu->getChildByTag(101);
    
    float pos = 90 - listSizeHeight;
    float tableViewHeight = visibleSize.height - 90 - 90;
    if (optionMenu->getPosition().y == pos) {
        tableViewHeight = tableViewHeight + pos;
        pos = 0;
        closeBtn->setVisible(true);
        openBtn->setVisible(false);
    } else {
        closeBtn->setVisible(false);
        openBtn->setVisible(true);
    }
    
    auto  actionBy = MoveTo::create(0.3f, Vec2(0, pos));
    cocos2d::Action *action = EaseIn::create(actionBy, 1);
    optionMenu->runAction(action);
    
    auto  actionBy1 = MoveTo::create(0.3f, Vec2(0, pos + listSizeHeight));
    cocos2d::Action *action1 = EaseIn::create(actionBy1, 1);
    talkDetail->runAction(action1);
    
    talkDetail->setViewSize(Size(Vec2(talkDetail->getContentSize().width, tableViewHeight)));
    talkDetail->reloadData();
}


/////////// Notification

void TalkDetail::pushNotification()
{
    int nextAsk = numberAsked + 1;
    string body = info->getTalk()->getItem(nextAsk)->getQuestion();
    string name = info->getName();
    string key  = StringUtils::format("chara_%d",chara_id);
    string message = name + "：" + body;
    
    int randTime    = rand() % 100 + 10;
    long int t = static_cast<long int>(time(NULL));
    LocalNotification::show(message,randTime,1);
    
    DBLocalNotification* notify = new DBLocalNotification();
    notify->init(chara_id, key, message, t+randTime);
   bool update = notify->update();
   
    insertTalkHistory(chara_id, 0, nextAsk, 0);
    printf("--------------");
    printf(update ? "true" : "false");
}

void TalkDetail::insertTalkHistory(int chara_id, int is_self,int talk_id, int option_id)
{
    long int t = static_cast<long int>(time(NULL));
    DBTalkHistory * history = new DBTalkHistory();
    history->init(chara_id,is_self,0,talk_id,option_id,0,t);
    history->insert();
}