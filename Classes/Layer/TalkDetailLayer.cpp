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
#include "FriendInfoLayer.h"
#include "DBService.h"
#include "NotificationService.h"
#include "DNKStoreData.h"

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
    tableViewHeight = 0;
    toCompare = 0;
    loadData();
    showingOptionView = false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    int bg_num = rand()%5;
    string bg_name = "res/talk/bg_"+to_string(bg_num)+".jpg";

    ImageView* bgImage = ImageView::create(bg_name);
    bgImage->setAnchorPoint(Vec2(0, 0));
    bgImage->setPosition(Vec2(0, 0));
    this->addChild(bgImage, -999);
    this->settingOptionMenu();
    
    // Add tableview
    talkDetail = TableView::create(this, Size(visibleSize.width, visibleSize.height - 280));
    talkDetail->setDelegate(this);
    talkDetail->setDataSource(this);
    
    talkDetail->setDirection(TableView::Direction::VERTICAL);
    talkDetail->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    talkDetail->setBounceable(false);

    talkDetail->setAnchorPoint(Vec2(0, 0));
    talkDetail->setPosition(Vec2(0, 180));
    talkDetail->setContentOffset(Vec2::ZERO);

    this->addChild(talkDetail, -888);
    talkDetail->reloadData();
//    float offsetY = talkDetail->getContentSize().height - visibleSize.height;
//    if (offsetY > 0) {
//        talkDetail->setContentOffset(Vec2(0, 0));
//    }
    
    // Add header image
    ImageView* imageView = ImageView::create("res/talk/bg_header.png");
    imageView->setAnchorPoint(Vec2(0, 0));
    imageView->setPosition(Vec2(0, visibleSize.height - imageView->getContentSize().height));
    this->addChild(imageView);
    
    //create back button
    backButton = MenuItemImage::create("btn_back.png", "btn_back_r.png",
                                       CC_CALLBACK_1(TalkDetail::menuCloseCallback, this));
    backButton->setAnchorPoint(Vec2(0, 0));
    backButton->setPosition(Vec2(0, 0));
    Menu *backMenu = Menu::create(backButton, NULL);
    backMenu->setAnchorPoint(Vec2(0, 0));
    backMenu->setPosition(Point(0, visibleSize.height - backButton->getContentSize().height - 10));
    this->addChild(backMenu);
    
    // add Title (screen name)
    std::string str = info->getNickName();
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    CCLabelTTF* lbl = CCLabelTTF::create(str, "MSGothic Bold", 34);
    lbl->setPosition(Vec2(130, visibleSize.height - 60));
    lbl->setAnchorPoint(Vec2(0, 0));
    lbl->setDimensions(Size(visibleSize.width - 130 * 2, 40));
    this->addChild(lbl);
    
    this->displayHeart(currentPoint);
    
    answerSelected = false;
    
    // setup for update
    this->schedule(schedule_selector(TalkDetail::update), 1.0);

    if (numberAnswered == 10) {
        this->settingRetryView(1);
    }
    return true;
}

#pragma mark - setting view functions
#pragma mark - add view when retry
void TalkDetail::settingRetryView(int type)
{
    if (!showingView) {
        showingView = true;
        retryLayer = TalkRetry::create(type);
        retryLayer->setAnchorPoint(Vec2(0, 0));
        retryLayer->setPosition(Vec2(0, 0));
        Button* backButton = retryLayer->getBackButton();
        backButton->addTouchEventListener(CC_CALLBACK_1(TalkDetail::closeRetryView, this));
        
        if (type == 0) {
            Button* goToKeepList = retryLayer->getGoToKeepListButton();
            goToKeepList->addTouchEventListener(CC_CALLBACK_1(TalkDetail::goToKeepList, this));
        } else {
            Button* retryButton = retryLayer->getRetryButton();
            retryButton->addTouchEventListener(CC_CALLBACK_1(TalkDetail::retryTalk, this));
        }

        this->addChild(retryLayer, 99);
        this->displayHeart(currentPoint);
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event)
        {
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, retryLayer);
    }
}

#pragma mark - add view when show friend info
void TalkDetail::friendIconOnclick(cocos2d::Ref* pSender)
{
    if (!showingView) {
        if (showingOptionView) {
            this->showOrHideOptions(NULL);
        }
        showingView = true;
        infoScene = FriendInfo::create(this->chara_id, info);
        infoScene->setAnchorPoint(Vec2(0, 0));
        infoScene->setPosition(Vec2(0, 0));
        infoScene->setColor(Color3B::BLACK);
        Button* backButton = infoScene->getBackButton();
        backButton->addTouchEventListener(CC_CALLBACK_1(TalkDetail::closeInfoView, this));
        this->addChild(infoScene, 99);
        this->displayHeart(currentPoint);
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event)
        {
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, infoScene);
    }
}

void TalkDetail::settingOptionMenu()
{
    auto listOptionBg = MenuItemImage::create("res/talk/bg_options.png", "res/talk/bg_options.png");
    listOptionBg->setAnchorPoint(Vec2(0, 0));
    listOptionBg->setPosition(Vec2(0, 0));
    listSizeHeight = listOptionBg->getContentSize().height;
    
    helpButton = MenuItemImage::create(
                                            "res/talk/btn_stamp.png",
                                            "res/talk/btn_stamp_r.png",
                                            CC_CALLBACK_1(TalkDetail::helpButtonOnclick, this));
    helpButton->setAnchorPoint(Vec2(0, 0));
    helpButton->setPosition(Vec2(10, listSizeHeight - helpButton->getContentSize().height - 10));
    
   
    
    
    closeButton = MenuItemImage::create("res/talk/btn_close.png",
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

    optionMenu->setPosition(Vec2(0, 190 - listSizeHeight));
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

#pragma mark - Tableview Delegate
//Size TalkDetail::cellSizeForTable(TableView *table){
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    return Size(visibleSize.width, visibleSize.height*.2);
//}
Size TalkDetail::tableCellSizeForIndex(TableView *table, ssize_t idx){
    
    float height;
    string str;
    int row = (int)idx/2;
    if(idx%2==0){ // this is a question asked by machine
        if (row > 9) {
            str = info->getResult()->getResultAtIndex(0)->getText();
        } else {
            str = info->getTalk()->getItem(row)->getQuestion();
        }
        height = DNKCommon::calculateHeightOfTalkCell(str, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
    } else {      // this is an answer from user
        if (row > 9) {
            int result_id;
            if (currentPoint >= 70) {
                result_id = 0;
            } else {
                result_id = 1;
            }
            DNKResultItem *result = info->getResult()->getResultAtIndex(result_id);
            str = result->getOption();
        } else {
            DNKSelection selection = info->getTalk()->getItem(row)->getOptions()->getSelection(selected[row]);
            str = selection.getAnswer();
        }

        height = DNKCommon::calculateHeightOfTalkMyCell(str, kTALK_DETAIL_POST_TEXT_SIZE, kTALK_DETAIL_POST_TEXT_WIDTH);
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
        Button *friendIcon = cell->getFriendIcon();
        friendIcon->addTouchEventListener(CC_CALLBACK_1(TalkDetail::friendIconOnclick, this));

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
#pragma mark TODO setting helpView
void TalkDetail::settingHelpView(cocos2d::Ref* pSender)
{
    log("setting help view");
}

void TalkDetail::helpButtonOnclick(Ref* pSender)
{
    //log("on touch");
    if (!showingView) {
        if (showingOptionView) {
            this->showOrHideOptions(NULL);
        }
        showingView = true;
        helpLayer = TalkDetailHelpLayer::create();
        helpLayer->setAnchorPoint(Vec2(0, 0));
        helpLayer->setPosition(Vec2(0, 100));
        this->addChild(helpLayer, -800);
        
        this->displayHeart(currentPoint);
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event)
        {
            return this->closeHelpView(touch, event);
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, helpLayer);
    }
}

bool TalkDetail::closeHelpView(Touch* touch, Event* event)
{
    helpLayer->removeFromParent();
    showingView = false;
    return true;
}

void TalkDetail::closeRetryView(cocos2d::Ref* pSender)
{
    retryLayer->removeFromParent();
    showingView = false;
}

#pragma mark TODO gotokeeplist
void TalkDetail::goToKeepList(cocos2d::Ref* pSender)
{
    retryLayer->removeFromParent();
    showingView = false;
    log("go to keep list");
}

void TalkDetail::retryTalk(cocos2d::Ref* pSender)
{
    retryLayer->removeFromParent();
    showingView = false;
    
    numberAsked = 0;
    numberAnswered = -1;
    
    talkDetail->reloadData();
    
    this->settingOptionMenu();
    
    long int now = static_cast<long int>(time(NULL));
    vector<DBTalkHistory *> talkHistory;
    string conditionstr = "chara_id="+to_string(this->chara_id)+" and time <= " + to_string(now);
    char *condition = const_cast<char*>(conditionstr.c_str());
    DBData *db = new DBData();
    talkHistory = db->getTalkHistorys(condition);
    //    log("ALo %d",talkHistory[2]->getOptionId());
    if(talkHistory.size() > 0){
        for (int i=0; i<talkHistory.size(); i++) {
            talkHistory[i]->delele();
        }
    }
    DBService::insertTalkHistory(this->chara_id, 0, 0, 0, 0, 0, now);
    log("retry talk");
}

void TalkDetail::closeInfoView(cocos2d::Ref* pSender)
{
    infoScene->removeFromParent();
    showingView = false;
}

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
    if(answerSelected) return;
    answerSelected = true;
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
    
    int addPoint;


    
    // insert answer to db
    long int currTime = static_cast<long int>(time(NULL));
    if (numberAnswered == 10) { // this talk end
        chara->setIsTalkEnd(1);
//        chara->setIsReceiveResult(1);
        if (currentPoint >= 70) {
            chara->setIsAddKeep(1);
            DBService::insertTalkHistory(this->chara_id, 1, 1, numberAsked, option, 0, currTime);
            this->settingRetryView(0);
        } else {
            DBService::insertTalkHistory(this->chara_id, 1, 1, numberAsked, option, 1, currTime);
            this->settingRetryView(1);
        }
    } else {
        if (numberAnswered == 9) {
            chara->setIsSendResult(1);
        }
        addPoint = info->getTalk()->getItem(numberAnswered)->getOptions()->getSelection(option).getPoint();
        currentPoint += addPoint;
        chara->setPoint(currentPoint);
        DBService::insertTalkHistory(this->chara_id, 1, 0, numberAsked, option, 0, currTime);
        // notification
        int randTime    =  rand() % 100 + 10;
        nextTime = NotificationService::pushNotification(chara_id,info,numberAsked +1, currentPoint,randTime);
        
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
        answer->setPosition(Vec2(visibleSize.width/2 - answer->getContentSize().width * 1.5, (visibleSize.height - 100)/2 - answer->getContentSize().height * 1.5));
        this->addChild(answer, 99999);
        this->scheduleOnce(schedule_selector(TalkDetail::fightToTop), kFlightTime/2);
    }
    chara->update();
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
    answerSelected = false;
    
    heartOff->setScale(0.8, 1);
    heartNormal->setScale(0.8, 1);
    heartGood->setScale(0.8, 1);
    this->scheduleOnce(schedule_selector(TalkDetail::heartSizeAnimation), 0.1);
}

void TalkDetail::heartSizeAnimation(float dt)
{
    heartOff->setScale(1, 1);
    heartNormal->setScale(1, 1);
    heartGood->setScale(1, 1);
}

void TalkDetail::showOrHideOptions(cocos2d::Ref* pSender)
{
    log("show or hide");
    showingOptionView = !showingOptionView;
    if (showingView) {
        this->closeHelpView(NULL, NULL);
    }
    
    MenuItemImage *closeBtn = (MenuItemImage*)optionMenu->getChildByTag(100);
    MenuItemImage *openBtn = (MenuItemImage*)optionMenu->getChildByTag(101);
    
    float pos = 190 - listSizeHeight;
    tableViewHeight = visibleSize.height - 90 - 90 - 100;
    if (optionMenu->getPosition().y == pos) {
        tableViewHeight = tableViewHeight + pos;
        pos = 100;
        toCompare = visibleSize.height - listSizeHeight - 90 - 100;
        
        closeBtn->setVisible(true);
        openBtn->setVisible(false);
        
        this->scheduleOnce(schedule_selector(TalkDetail::setTalkDetailTableHeigh), 0.2);
    } else {
        
        closeBtn->setVisible(false);
        openBtn->setVisible(true);
        this->setTalkDetailTableHeigh(0);
    }

    
    if (talkDetail->getContentSize().height > toCompare) {
        auto  actionBy1 = MoveTo::create(0.2f, Vec2(0, pos + listSizeHeight));
        cocos2d::Action *action1 = EaseIn::create(actionBy1, 0.8);
        talkDetail->runAction(action1);
    }

    auto  actionBy = MoveTo::create(0.2f, Vec2(0, pos));
    cocos2d::Action *action = EaseIn::create(actionBy, 0.8);
    optionMenu->runAction(action);
    
}

void TalkDetail::setTalkDetailTableHeigh(float dt)
{
    if (talkDetail->getContentSize().height >= toCompare) {
         talkDetail->setViewSize(Size(Vec2(talkDetail->getContentSize().width, tableViewHeight)));
        talkDetail->setContentOffset(Vec2::ZERO);
    }
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
    info = StoreData::GetInstance()->GetData(this->chara_id);
    
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
    string conditionstr = " select * from talk_history where chara_id="+to_string(this->chara_id)+" and is_self=1" + " and time <= " + to_string(now);
    char *condition = const_cast<char*>(conditionstr.c_str());
    
    talkHistory = db->getTalkHistorys(condition);
    //    log("ALo %d",talkHistory[2]->getOptionId());
    if(talkHistory.size() > 0){
        for (int i=0; i<=numberAnswered; i++) {
            selected[i] = talkHistory[i]->getOptionId();
            //        log("lua chon %d %d", talkHistory[i].getOptionId(), i);
        }
    }
    
    string conditionstr1 = "select * from talk_history where chara_id="+to_string(this->chara_id)+" and time <= " + to_string(now);
    char *condition1 = const_cast<char*>(conditionstr1.c_str());
    
    talkHistory = db->getTalkHistorys(condition1);
    //    log("ALo %d",talkHistory[2]->getOptionId());
    if(talkHistory.size() > 0){
        for (int i=0; i<talkHistory.size(); i++) {
            talkTime.push_back(talkHistory[i]->getTime());
        }
    }
    
    nextTime = db->getNextTalk(chara_id, now);
}

void TalkDetail::displayHeart(int curPoint) {
    if (heartOff) {
        heartOff->removeFromParent();
        heartNormal->removeFromParent();
        heartGood->removeFromParent();
    }
    // Add heart image
    heartOff = Sprite::create("res/talk/heart_off.png");
//    heartOff = ImageView::create("res/talk/heart_off.png");
    Vec2 pos = Vec2(visibleSize.width - 70, visibleSize.height - heartOff->getContentSize().height/2 - 8);
    heartOff->setAnchorPoint(Vec2(0.5, 0.5));
    heartOff->setPosition(pos);
    this->addChild(heartOff);
    
    heartNormal = ImageView::create("res/talk/heart_b.png");
    heartNormal->setAnchorPoint(Vec2(0.5, 0.5));
    heartNormal->setPosition(pos);
    this->addChild(heartNormal);
    
    heartGood = ImageView::create("res/talk/heart.png");
    heartGood->setAnchorPoint(Vec2(0.5, 0.5));
    heartGood->setPosition(pos);
    this->addChild(heartGood);
    
    this->changeHeartDisplay(curPoint);
}

void TalkDetail::changeHeartDisplay(int curPoint) {
    Point pos = Vec2(visibleSize.width - 70, visibleSize.height - heartOff->getContentSize().height/2 - 8);
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
        this->heartAnimationBigger(0);
    }
}

void TalkDetail::heartAnimationBigger(float dt) {
    heartOff->setScale(1.05);
    heartNormal->setScale(1.05);
    heartGood->setScale(1.05);
    this->scheduleOnce(schedule_selector(TalkDetail::heartAnimationNormal), 0.2);
}

void TalkDetail::heartAnimationNormal(float dt) {
    heartOff->setScale(1);
    heartNormal->setScale(1);
    heartGood->setScale(1);
    this->scheduleOnce(schedule_selector(TalkDetail::heartAnimationBigger), 0.2);
}
