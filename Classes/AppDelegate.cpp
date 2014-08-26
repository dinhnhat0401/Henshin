#include "AppDelegate.h"
#include "MainAppScene.h"
#include "TalkDetailLayer.h"
#include "StartAppScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    auto scene = MainApp::getInstance();
    UserDefault *userDefalt = UserDefault::getInstance();
//    userDefalt->setStringForKey("username", "");
    if(strcmp(userDefalt->getStringForKey("username").c_str(), "") == 0)
    {
        auto scene = StartApp::createScene();
        director->runWithScene(scene);
    }
    else
    {
        UserDefault *userDefalt = UserDefault::getInstance();
        
        int value = userDefalt->getIntegerForKey("notification_charaid",-1);
        if(value < 1)
        {
            auto scene1 = MainApp::getInstance();
            director->runWithScene(scene1);
        }
        else
        {
            auto scene3 = TalkDetail::createScene(value);
            director->runWithScene(scene3);
            userDefalt->setIntegerForKey("notification_charaid", -1);
        }
    }
//    auto layer  = TalkDetail::create(17);
//    Scene * scene = Scene::create();
//    scene->addChild(layer);

    // run
    

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

