//
//  StartAppScene.cpp
//  Henshin
//
//  Created by hoangdieu on 8/7/14.
//  Copyright (c) 2014 DNK. All rights reserved.
//

#include "StartAppScene.h"
#include "MainAppScene.h"
USING_NS_CC;

Scene* StartApp::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartApp::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartApp::init()
{
    //init background color
    if ( !CCLayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    xCenter = origin.x + visibleSize.width/2;
    yCenter = origin.y + visibleSize.height/2;
    
    logo = cocos2d::Sprite::create("res/init/logo.png");
    logo->setPosition(Vec2(xCenter,origin.y+2*visibleSize.height/3));
    float _bgWidth = logo->getContentSize().width;
    float _bgHeight = logo->getContentSize().height;
    logo->setContentSize(Size(visibleSize.width,_bgHeight*visibleSize.width/_bgWidth));
    this->addChild(logo);
    
    //add button
    btnStart1 = cocos2d::MenuItemImage::create("res/init/btn_start_1.png", "res/init/btn_start_1.png",CC_CALLBACK_1(StartApp::menuStart,this));
    float btnWidth = btnStart1->getContentSize().width;
    float btnHeight = btnStart1->getContentSize().height;
    
    btnStart1->setContentSize(Size(visibleSize.width/2,btnHeight*visibleSize.width/(2*btnWidth)));
    auto menu = Menu::create(btnStart1, NULL);
    menu->setPosition(xCenter,origin.y+visibleSize.height/5);
    this->addChild(menu);
    
    return true;
}


void StartApp::menuStart(Ref* pSender)
{
    log("A");
//    btnStart1->retain();
    this->removeAllChildrenWithCleanup(true);
    
    logo1 = cocos2d::Sprite::create("res/init/logo_1.png");
    
    float _bgWidth = logo1->getContentSize().width;
    float _bgHeight = logo1->getContentSize().height;
    logo1->setPosition(Vec2(xCenter,origin.y+_bgHeight));
    logo1->setContentSize(Size(visibleSize.width,_bgHeight*visibleSize.width/_bgWidth));
    this->addChild(logo1);
    

    
    // add button gender
    
    btnMale = cocos2d::MenuItemImage::create("res/other/btn_male.png", "res/other/btn_male.png",CC_CALLBACK_1(StartApp::menuMale,this));
    float btnWidth = btnMale->getContentSize().width;
    float btnHeight = btnMale->getContentSize().height;
    btnMale->setContentSize(Size(visibleSize.width/2-20,btnHeight*(visibleSize.width/2-10)/btnWidth));
    btnMale->setPosition(Vec2(-xCenter+origin.x+visibleSize.width/4,2*btnHeight));
    
    btnFeMale1 = cocos2d::MenuItemImage::create("res/other/btn_female_none.png", "res/other/btn_female_none.png",CC_CALLBACK_1(StartApp::menuFemale,this));
    btnWidth = btnFeMale1->getContentSize().width;
    btnHeight = btnFeMale1->getContentSize().height;
    btnFeMale1->setContentSize(Size(visibleSize.width/2-20,btnHeight*(visibleSize.width/2-10)/btnWidth));
    btnFeMale1->setPosition(Vec2(origin.x+visibleSize.width/4,2*btnHeight));
    
    //disbale button
    btnMale1 = cocos2d::MenuItemImage::create("res/other/btn_male_none.png", "res/other/btn_male_none.png",CC_CALLBACK_1(StartApp::menuMale,this));
    btnWidth = btnMale1->getContentSize().width;
    btnHeight = btnMale1->getContentSize().height;
    btnMale1->setContentSize(Size(visibleSize.width/2-20,btnHeight*(visibleSize.width/2-10)/btnWidth));
    btnMale1->setPosition(Vec2(-xCenter+origin.x+visibleSize.width/4,2*btnHeight));
    
    btnFeMale = cocos2d::MenuItemImage::create("res/other/btn_female.png", "res/other/btn_female.png",CC_CALLBACK_1(StartApp::menuFemale,this));
    btnWidth = btnFeMale->getContentSize().width;
    btnHeight = btnFeMale->getContentSize().height;
    btnFeMale->setContentSize(Size(visibleSize.width/2-20,btnHeight*(visibleSize.width/2-10)/btnWidth));
    btnFeMale->setPosition(Vec2(origin.x+visibleSize.width/4,2*btnHeight));
    
    //default Male
    btnMale1->setVisible(false);
    btnFeMale->setVisible(false);
    
    cocos2d::LabelTTF *_genderLabel= LabelTTF::create("性別", "Arial", 24);
    _genderLabel->setColor(Color3B::BLACK);
    _genderLabel->setPosition(Vec2(40,yCenter+3*btnHeight));
    _genderLabel->setVerticalAlignment(TextVAlignment::CENTER);
    this->addChild(_genderLabel);
    
    /// add input text
    Scale9Sprite *spInput = Scale9Sprite::create("res/other/input.png");
    float inputWidth = spInput->getContentSize().width;
    float inputHeight = spInput->getContentSize().height;
    
    name = EditBox::create(Size(visibleSize.width-40,inputHeight*(visibleSize.width-40)/inputWidth), spInput);
    name->setPosition(Vec2(xCenter,yCenter+4*btnHeight));
    name->setFontSize(20);
    name->setFontColor(Color3B(0,0,0));
    name->setMaxLength(40);
    name->setReturnType(EditBox::KeyboardReturnType());
    //    name->setDelegate(this);
    this->addChild(name);
    
    cocos2d::LabelTTF *_nameLabel= LabelTTF::create("名前", "Arial", 24);
    _nameLabel->setColor(Color3B::BLACK);
    _nameLabel->setPosition(Vec2(40,yCenter+5*btnHeight));
    _nameLabel->setVerticalAlignment(TextVAlignment::CENTER);
    this->addChild(_nameLabel);
    

    //add button
    btnOk = cocos2d::MenuItemImage::create("res/init/btn_ok.png", "res/init/btn_ok.png",CC_CALLBACK_1(StartApp::menuRegister,this));
    btnWidth = btnOk->getContentSize().width;
    btnHeight = btnOk->getContentSize().height;
    
    btnOk->setContentSize(Size(visibleSize.width/2,btnHeight*visibleSize.width/(2*btnWidth)));
    
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    pMenuItems.pushBack(btnMale);
    pMenuItems.pushBack(btnOk);
    pMenuItems.pushBack(btnFeMale);
    pMenuItems.pushBack(btnMale1);
    pMenuItems.pushBack(btnFeMale1);
    
    auto menu = Menu::createWithArray(pMenuItems);
    menu->setPosition(xCenter,yCenter);
    this->addChild(menu);
}
void StartApp::menuRegister(Ref *pSender)
{
    
    if(strcmp(name->getText(),"") == 0)
    {
        return;
    }
    //save data
    UserDefault *userDefalt = UserDefault::getInstance();
    userDefalt->setStringForKey("username", name->getText());
    userDefalt->setBoolForKey("gender", this->gender);
    
    //初めてボタン
    this->removeAllChildrenWithCleanup(true);
    
    logo2 = cocos2d::Sprite::create("res/init/logo_2.png");
    logo2->setPosition(Vec2(xCenter,origin.y+2*visibleSize.height/3));
    float _bgWidth = logo2->getContentSize().width;
    float _bgHeight = logo2->getContentSize().height;
    logo2->setContentSize(Size(visibleSize.width,_bgHeight*visibleSize.width/_bgWidth));
    this->addChild(logo2);
    
    
    
    //add button
    btnStart = cocos2d::MenuItemImage::create("res/init/btn_start.png", "res/init/btn_start.png",CC_CALLBACK_1(StartApp::menuStartapp,this));
    float btnWidth = btnStart->getContentSize().width;
    float btnHeight = btnStart->getContentSize().height;
    
    btnStart->setContentSize(Size(2*visibleSize.width/3,2*btnHeight*visibleSize.width/(3*btnWidth)));
    auto menu1 = Menu::create(btnStart, NULL);
    menu1->setPosition(Vec2(xCenter,origin.y+visibleSize.height/5));
    this->addChild(menu1);
}

//start app
void StartApp::menuStartapp(cocos2d::Ref *pSender)
{
    // fade out the current scene and fade in the new scene in 1 second
    auto newScene = MainApp::getInstance();
    auto transition = TransitionFade::create(1.0f, newScene);
    cocos2d::Director::getInstance()->replaceScene(transition);
}

void StartApp::menuMale(Ref *pSender)
{
    this->gender = true;
    btnMale->setVisible(true);
    btnMale1->setVisible(false);
    
    btnFeMale->setVisible(false);
    btnFeMale1->setVisible(true);
}

void StartApp::menuFemale(Ref *pSender)
{
    this->gender = false;
    
    btnMale1->setVisible(true);
    btnMale->setVisible(false);
    
    btnFeMale1->setVisible(false);
    btnFeMale->setVisible(true);
}
