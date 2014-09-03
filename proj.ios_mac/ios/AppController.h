#import <UIKit/UIKit.h>
#include "MainAppScene.h"
#include "ConstantValue.h"
#include "DBChara.h"

@class RootViewController;

extern "C"{
#import "GADBannerView.h"
};

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    GADBannerView *bannerView_;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

