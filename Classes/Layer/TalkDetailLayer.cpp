//
//  TalkDetailLayer.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/24.
//
//
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
#include <time.h>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;
#define kFlightTime 0.5f

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
   
    loadData();

    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    cocos2d::ui::ImageView* bgImage = cocos2d::ui::ImageView::create("res/talk/bg_0.jpg");
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage, -999);
    this->settingOptionMenu();
    
    // Add tableview
    talkDetail = TableView::create(this, Size(visibleSize.width, visibleSize.height - 180));
    talkDetail->setDirection(TableView::Direction::VERTICAL);
//    talkDetail->setBounceable(false);
    talkDetail->setAnchorPoint(Vec2(0, 0));
    talkDetail->setPosition(Vec2(0, 90));
    
    talkDetail->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    talkDetail->setDelegate(this);
    this->addChild(talkDetail, -888);
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
    std::string str = info->getNickName();
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    CCLabelTTF* lbl = CCLabelTTF::create(str, "MSGothic Bold", 34);
    lbl->setPosition(Vec2(130, visibleSize.height - 60));
    lbl->setAnchorPoint(Vec2(0, 0));
    lbl->setDimensions(Size(visibleSize.width - 130 * 2, 40));
    this->addChild(lbl);
    
    this->displayHeart(currentPoint);
    
    this->settingSelectionView();
    
    // setup for update
    this->schedule(schedule_selector(TalkDetail::update), 1.0);

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
    
    
    DNKItem *lastItem;
    DNKResultItem *result;
    DNKOption *options;
    
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
    
    if (numberAsked <= numberAnswered) {
        showOptionText->setEnabled(false);
        openButton->setVisible(false);
        openButtonOff->setVisible(true);
    } else {
        showOptionText->setEnabled(true);
        openButton->setVisible(true);
        openButtonOff->setVisible(false);
    }
    
    if (numberAsked > 9) {   // tra loi het cac cau hoi
        result = info->getResult()->getResultAtIndex(0);
        auto lastAnswer = MenuItemImage::create("res/talk/btn_option.png",
                                                "res/talk/btn_option.png",
                                                CC_CALLBACK_1(TalkDetail::selectAnswer, this));
        
        
        lastAnswer->setAnchorPoint(Vec2(0, 0));
        opSize = lastAnswer->getContentSize();
        
        float xPos = (visibleSize.width - opSize.width) / 2.0f;
        lastAnswer->setPosition(Vec2(xPos, 2 * opSize.height + 3 * kPADDING));
        lastAnswer->setTag(1001);
        this->createLableAndAddToOption(lastAnswer, result->getOption());
        optionMenu = Menu::create(listOptionBg, helpButton, showOptionText, closeButton, openButton, openButtonOff, lastAnswer, NULL);
    } else {
        lastItem = info->getTalk()->getItem(numberAsked);
        options = lastItem->getOptions();
        
        // config options
        auto op1 = MenuItemImage::create("res/talk/btn_option.png",
                                         "res/talk/btn_option.png",
                                         CC_CALLBACK_1(TalkDetail::selectAnswer, this));
        
        
        op1->setAnchorPoint(Vec2(0, 0));
        opSize = op1->getContentSize();
        
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
        
        this->createLableAndAddToOption(op1, options->getSelection(0).getAnswer());
        this->createLableAndAddToOption(op2, options->getSelection(1).getAnswer());
        this->createLableAndAddToOption(op3, options->getSelection(2).getAnswer());
        
        optionMenu = Menu::create(listOptionBg, helpButton, showOptionText, closeButton, openButton, openButtonOff, op1, op2, op3, NULL);
    }

    
    
    optionMenu->setPosition(Vec2(0, 90 - listSizeHeight));
    this->addChild(optionMenu, 2);
}
void TalkDetail::createLableAndAddToOption(MenuItemImage* option, string text){
    float lblHeight = DNKCommon::calculateHeightOfLabel(text, 25, visibleSize.width - kPADDING);
    CCLabelTTF* tmpLbl1 = CCLabelTTF::create(text, kDEFAULT_BOLD_FONT, 25);
    tmpLbl1->setColor(Color3B::BLACK);
    tmpLbl1->setDimensions(Size(visibleSize.width - kPADDING * 3, 0));
    tmpLbl1->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    tmpLbl1->setAnchorPoint(Vec2(0, 0));
    tmpLbl1->setPosition(Vec2(kPADDING, (opSize.height - lblHeight)/2));
    option->addChild(tmpLbl1, 999);
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
    int _time = talkTime[idx];
    if(idx%2 == 0){
        DNKFriendChatTableViewCell *cell = (DNKFriendChatTableViewCell*)table->dequeueCell();
        cell = new DNKFriendChatTableViewCell();
        int row = (int)idx/2;
        if (row > 9) {
            cell->initCell(info->getResult()->getResultAtIndex(0)->getText(), _time, info, this->chara_id);
        } else {
            cell->initCell(info->getTalk()->getItem(row)->getQuestion(), _time, info, this->chara_id);
        }
        cell->autorelease();
        return cell;
    }
    else {
        DNKMyChatTableViewCell *cell = (DNKMyChatTableViewCell*)table->dequeueCell();
        cell = new DNKMyChatTableViewCell();
        int row = (int)idx/2;
        if (row > 9) {
            DNKResultItem *result = info->getResult()->getResultAtIndex(0);
            cell->initCell(result->getOption(), _time);
        } else {
            DNKSelection selection = info->getTalk()->getItem(row)->getOptions()->getSelection(selected[row]);
            cell->initCell(selection.getAnswer(), _time);
        }
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
    insertTalkHistory(chara_id, 1, numberAsked, option,0);
    // notification
    pushNotification();
    
    int addPoint = info->getTalk()->getItem(numberAnswered)->getOptions()->getSelection(option).getPoint();
    currentPoint += addPoint;
    chara->setPoint(currentPoint);
    chara->update();
    this->displayHeart(currentPoint);
    CocosDenshion::SimpleAudioEngine *engine = CocosDenshion::SimpleAudioEngine::getInstance();
    switch (addPoint) {
        case 0:
            answer = Sprite::create("res/talk/bad.png");
            engine->playEffect("sound/bad.aif");
            break;
        case 5:
            answer = Sprite::create("res/talk/good.png");
            engine->playEffect("sound/good.aif");
            break;
        case 10:
            answer = Sprite::create("res/talk/great.png");
            engine->playEffect("sound/great.aif");
            break;
        default:
            break;
    }
    answer->setAnchorPoint(Vec2(0, 0));
    answer->setScale(3);
    answer->setPosition(Vec2(visibleSize.width/2 - answer->getContentSize().width * 1.5, visibleSize.height/2 - answer->getContentSize().height * 1.5));
    this->addChild(answer, 99999);
    this->scheduleOnce(schedule_selector(TalkDetail::fightToTop), kFlightTime/2);
}

void TalkDetail::fightToTop(float dt){
    auto  move = MoveTo::create(kFlightTime, Vec2(visibleSize.width - 150, visibleSize.height - 140));
    Action *moveAction = EaseIn::create(move, 1);
    answer->runAction(moveAction);
    
    auto  scale = ScaleTo::create(kFlightTime, 1);
    Action *scaleAction = EaseOut::create(scale, 1);
    answer->runAction(scaleAction);
    
    this->scheduleOnce(schedule_selector(TalkDetail::myModification), kFlightTime);
}

void TalkDetail::myModification(float dt)
{
    answer->setVisible(false);
    answer->removeFromParent();
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
    bool update = notify->insert();
    
    DBTalkNext* next = new DBTalkNext();
    next->init(0, chara_id, nextAsk, t+randTime);
    next->insert();
   
    insertTalkHistory(chara_id, 0, nextAsk, 0,t+randTime);
    nextTime = t+randTime;

}

void TalkDetail::insertTalkHistory(int chara_id, int is_self,int talk_id, int option_id,int t = 0)
{
    DBTalkHistory * history = new DBTalkHistory();
    t = (t == 0) ? static_cast<long int>(time(NULL)) : t;
    history->init(chara_id,is_self,0,talk_id,option_id,0,t);
    history->insert();
}
// update per frame
void TalkDetail::update(float d)
{
    if(nextTime > 0)
    {
        long int now = static_cast<long int>(time(NULL));
        if(now >= nextTime)
        {
            loadData();
            if (numberAsked <= numberAnswered) {
                showOptionText->setEnabled(false);
                openButton->setVisible(false);
                openButtonOff->setVisible(true);
            } else {
                showOptionText->setEnabled(true);
                openButton->setVisible(true);
                openButtonOff->setVisible(false);
            }
            talkDetail->reloadData();
        }
    }
}

void TalkDetail::loadData()
{
    long int now = static_cast<long int>(time(NULL));
    FilePlists* plist = new FilePlists();
    string fileName = "chara_talk/chara_talk_" + to_string(this->chara_id) + ".plist";
    plist->readFile(fileName);
    info = plist->getValues();
    
    for(int i=0; i< 10; i++){
        selected[i] = -1;
    }
    
    DBConnect *dbconnect= new DBConnect();
    dbconnect->getConnect();
    string updateChara = StringUtils::format("update chara set unread = 0 where chara_id = %d", chara_id);
    dbconnect->executeCommand(const_cast<char*>(updateChara.c_str()));
    
    
    string removeTalkNext = StringUtils::format("delete from talk_next where chara_id = %d and time <= %d",chara_id,now);
    dbconnect->executeCommand(const_cast<char*>(removeTalkNext.c_str()));
    string getNumberAsked = "SELECT max(talk_id) from talk_history where is_self=0 and chara_id="+to_string(this->chara_id) + " and time <= " + to_string(now);
    
    printf("%s\n",getNumberAsked.c_str());
    dbconnect->getData(const_cast<char*>(getNumberAsked.c_str()));
    char *value1 = dbconnect->getDataIndex(1,0);
    if(value1 == NULL) {
        numberAsked = -1;
    } else {
        numberAsked = atoi(value1);
    }
    
    dbconnect->getConnect();
    string getNumber = "SELECT max(talk_id) from talk_history where is_self=1 and chara_id="+to_string(this->chara_id)+ " and time <= " + to_string(now);
    dbconnect->getData(const_cast<char*>(getNumber.c_str()));
    char *value = dbconnect->getDataIndex(1,0);
    if(value == NULL) {
        numberAnswered = -1;
    } else {
        numberAnswered = atoi(value);
    }
    
//    dbconnect->getConnect();
    string getPoint = "chara_id="+to_string(this->chara_id);
//    dbconnect->getData(const_cast<char*>(getPoint.c_str()));
//    char *temp = dbconnect->getDataIndex(1,0);
    DBData *db = new DBData();
    chara = db->getChara(const_cast<char*>(getPoint.c_str()));
    currentPoint = chara->getPoint();
    
    dbconnect->freeTable();
    dbconnect->closeDB();
    
    vector<DBTalkHistory *> talkHistory;
    string conditionstr = "chara_id="+to_string(this->chara_id)+" and is_self=1" + " and time <= " + to_string(now);
    char *condition = const_cast<char*>(conditionstr.c_str());
    
    talkHistory = db->getTalkHistorys(condition);
    //    log("ALo %d",talkHistory[2]->getOptionId());
    if(talkHistory.size() > 0){
        for (int i=0; i<=numberAnswered; i++) {
            selected[i] = talkHistory[i]->getOptionId();
            //        log("lua chon %d %d", talkHistory[i].getOptionId(), i);
        }
    }
    
    string conditionstr1 = "chara_id="+to_string(this->chara_id)+" and time <= " + to_string(now);
    char *condition1 = const_cast<char*>(conditionstr1.c_str());
    
    talkHistory = db->getTalkHistorys(condition1);
    //    log("ALo %d",talkHistory[2]->getOptionId());
    if(talkHistory.size() > 0){
        for (int i=0; i<talkHistory.size(); i++) {
            talkTime.push_back(talkHistory[i]->getTime());
        }
    }
    
    nextTime = db->getNextTalk(chara_id, now);
    printf("next --------- %d",nextTime);
    
}

void TalkDetail::displayHeart(int curPoint) {
    // Add heart image
    heartOff = Sprite::create("res/talk/heart_off.png");
//    heartOff = ImageView::create("res/talk/heart_off.png");
    Vec2 pos = Vec2(visibleSize.width - 125, visibleSize.height - heartOff->getContentSize().height - 8);
    heartOff->setAnchorPoint(Vec2(0, 0));
    heartOff->setPosition(pos);
    this->addChild(heartOff);
    
    heartNormal = ImageView::create("res/talk/heart_b.png");
    heartNormal->setAnchorPoint(Vec2(0, 0));
    heartNormal->setPosition(pos);
    this->addChild(heartNormal);
    
    heartGood = ImageView::create("res/talk/heart.png");
    heartGood->setAnchorPoint(Vec2(0, 0));
    heartGood->setPosition(pos);
    this->addChild(heartGood);
    
    this->changeHeartDisplay(curPoint);
}

void TalkDetail::changeHeartDisplay(int curPoint) {
    Point pos = Vec2(visibleSize.width - 125, visibleSize.height - heartOff->getContentSize().height - 8);
    Size heartSize = heartOff->getContentSize();
    if (curPoint == 0) {
        heartNormal->setVisible(false);
        heartGood->setVisible(false);
    } else if (curPoint > 0 && curPoint < 70) {
        heartNormal->setVisible(true);
        heartGood->setVisible(false);
        heartNormal->setTextureRect(Rect(0, heartSize.height * (1 - curPoint/100.0), heartSize.width, heartSize.height * curPoint/ 100.0));
//        CCLOG("%f %f", heartSize.height * curPoint/ 100.0, heartSize.height * (1 - curPoint/100.0));
//        heartNormal->setAnchorPoint(Vec2(0, 0));
        heartNormal->setPosition(Vec2(pos.x, pos.y - heartSize.height * (1 - curPoint/100.0)/2.0));
    } else { // curPoint >= 70
        heartNormal->setVisible(false);
        heartGood->setVisible(true);
        
        heartGood->setTextureRect(Rect(0, heartSize.height * (1 - curPoint/100.0), heartSize.width, heartSize.height * curPoint/ 100.0));
        heartGood->setPosition(Vec2(pos.x, pos.y - heartSize.height * (1 - curPoint/100.0)/2.0));
    }
}
