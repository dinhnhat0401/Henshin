//
//  TimelineScene.cpp
//  Henshin
//
//  Created by Đinh Văn Nhật on 2014/07/24.
//
//
#include "HelloWorldScene.h"
#include "TimelineScene.h"

USING_NS_CC;

Scene* Timeline::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Timeline::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Timeline::init()
{
    if (!Layer::init())return false;
    auto image = Sprite::create("三輪田薫4.jpg");
    image->setScale(0.7);
    image->setAnchorPoint(Vec2(0, 0));
    image->setPosition(Vec2(0, 0));
    this->addChild(image);
    
    auto closeItem = MenuItemImage::create(
                                           "btn_back_r.png",
                                           "btn_back.png",
                                           CC_CALLBACK_1(Timeline::menuCloseCallback, this));
    Size visibleSize = Director::getInstance()->getVisibleSize();
	closeItem->setPosition(Vec2(50, visibleSize.height - 80));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void Timeline::menuCloseCallback(Ref* pSender)
{
    log("back press");
//    Director::getInstance()->popScene();
    auto newScene = HelloWorld::createScene();
    auto tran1 = TransitionMoveInL::create(0.3f, newScene);
    Director::getInstance()->replaceScene(tran1);
}