#import <UIKit/UIKit.h>
#include "MainAppScene.h"
#include "ConstantValue.h"
#include "DBChara.h"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

