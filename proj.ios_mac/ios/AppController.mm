/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "CCEAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }
    
    //check app run the first
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger first = [defaults integerForKey:@"first_henshin"];
    if(first != 123)
    {
        [defaults setInteger:123 forKey:@"first_henshin"];
        [defaults setInteger:-1 forKey:@"notification_charaid"];
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
    }
    // Handle launching from a notification
    UILocalNotification *locationNotification = [launchOptions objectForKey:UIApplicationLaunchOptionsLocalNotificationKey];
    if (locationNotification) {
        NSDictionary *userinfor = [locationNotification userInfo];
        NSLog(@"Chara ID(lauch app) %li",(long)[[userinfor valueForKey:@"ID"] integerValue]);
        
        [defaults setInteger:(int)[[userinfor valueForKey:@"ID"] integerValue] forKey:@"notification_charaid"];
//        [defaults synchronize];
//        MainApp * mApp = new MainApp();
//        mApp->setCurrentChara((int)[[userinfor valueForKey:@"ID"] integerValue]);
//        mApp->changeState(ConstValue::STATE_TALK_DETAIL);
    }
    else
        NSLog(@"Khong dc!");

    //landscape(横画面)の一番下に広告を表示
    bannerView_ = [[GADBannerView alloc]initWithAdSize:kGADAdSizeBanner];
    bannerView_.center = CGPointMake(_viewController.view.center.y, _viewController.view.frame.size.width-bannerView_.frame.size.height/2);
    
    bannerView_.adUnitID = @"ca-app-pub-0217125550937927/4419837235";
    CGRect screenRect = [[UIScreen mainScreen] bounds];
    CGFloat screenWidth = screenRect.size.width;
    CGFloat screenHeight = screenRect.size.height;
    bannerView_.center = CGPointMake(screenWidth/2, screenHeight-50/2);
    
    [_viewController.view addSubview: bannerView_];
    [bannerView_ setRootViewController:_viewController];
    
    GADRequest *request = [GADRequest request];
    request.testing = YES; //テスト中の合図。本番ではコメントアウトを。
    [bannerView_ loadRequest:request];
    
    ///end ads
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLView::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();
    
    
//    application.applicationIconBadgeNumber = 0;
    DBChara *chara = new DBChara();
    application.applicationIconBadgeNumber = chara->getUnreadNotification();
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
    DBChara *chara = new DBChara();
    NSInteger badge = chara->getUnreadNotification();
    application.applicationIconBadgeNumber = badge;
    
    /// reload notification
    NSArray *pendingNotifications = [[[UIApplication sharedApplication] scheduledLocalNotifications] sortedArrayUsingComparator:^(id obj1, id obj2) {
        if ([obj1 isKindOfClass:[UILocalNotification class]] && [obj2 isKindOfClass:[UILocalNotification class]])
        {
            UILocalNotification *notif1 = (UILocalNotification *)obj1;
            UILocalNotification *notif2 = (UILocalNotification *)obj2;
            return [notif1.fireDate compare:notif2.fireDate];
        }
        
        return NSOrderedSame;
    }];
    // if there are any pending notifications -> adjust their badge number
    if (pendingNotifications.count != 0)
    {
        // clear all pending notifications
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
        
        // the for loop will 'restore' the pending notifications, but with corrected badge numbers
        // note : a more advanced method could 'sort' the notifications first !!!
        
        for (UILocalNotification *notification in pendingNotifications)
        {
            // modify the badgeNumber
            badge++;
            notification.applicationIconBadgeNumber = badge;
            
            // schedule 'again'
            [[UIApplication sharedApplication] scheduleLocalNotification:notification];
        }
    }
    
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
    DBChara *chara = new DBChara();
    NSInteger badge = chara->getUnreadNotification();
    application.applicationIconBadgeNumber = badge;
    
    /// reload notification
    NSArray *pendingNotifications = [[[UIApplication sharedApplication] scheduledLocalNotifications] sortedArrayUsingComparator:^(id obj1, id obj2) {
        if ([obj1 isKindOfClass:[UILocalNotification class]] && [obj2 isKindOfClass:[UILocalNotification class]])
        {
            UILocalNotification *notif1 = (UILocalNotification *)obj1;
            UILocalNotification *notif2 = (UILocalNotification *)obj2;
            return [notif1.fireDate compare:notif2.fireDate];
        }
        
        return NSOrderedSame;
    }];
    // if there are any pending notifications -> adjust their badge number
    if (pendingNotifications.count != 0)
    {
        // clear all pending notifications
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
        
        // the for loop will 'restore' the pending notifications, but with corrected badge numbers
        // note : a more advanced method could 'sort' the notifications first !!!
        
        for (UILocalNotification *notification in pendingNotifications)
        {
            // modify the badgeNumber
            notification.applicationIconBadgeNumber = badge++;
            
            // schedule 'again'
            [[UIApplication sharedApplication] scheduleLocalNotification:notification];
        }
    }
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
//    application.applicationIconBadgeNumber = 0;
//    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
//
//    [defaults setInteger:0 forKey:@"number_notification"];
    DBChara *chara = new DBChara();
    NSInteger badge = chara->getUnreadNotification();
    application.applicationIconBadgeNumber = badge;
    
    /// reload notification
    NSArray *pendingNotifications = [[[UIApplication sharedApplication] scheduledLocalNotifications] sortedArrayUsingComparator:^(id obj1, id obj2) {
        if ([obj1 isKindOfClass:[UILocalNotification class]] && [obj2 isKindOfClass:[UILocalNotification class]])
        {
            UILocalNotification *notif1 = (UILocalNotification *)obj1;
            UILocalNotification *notif2 = (UILocalNotification *)obj2;
            return [notif1.fireDate compare:notif2.fireDate];
        }
        
        return NSOrderedSame;
    }];
    // if there are any pending notifications -> adjust their badge number
    if (pendingNotifications.count != 0)
    {
        // clear all pending notifications
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
        
        // the for loop will 'restore' the pending notifications, but with corrected badge numbers
        // note : a more advanced method could 'sort' the notifications first !!!
        
        for (UILocalNotification *notification in pendingNotifications)
        {
            // modify the badgeNumber
            badge++;
            notification.applicationIconBadgeNumber = badge;
            
            // schedule 'again'
            [[UIApplication sharedApplication] scheduleLocalNotification:notification];
        }
    }
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
    DBChara *chara = new DBChara();
    NSInteger badge = chara->getUnreadNotification();
    application.applicationIconBadgeNumber = badge;
//    
//    /// reload notification
//    NSArray *pendingNotifications = [[[UIApplication sharedApplication] scheduledLocalNotifications] sortedArrayUsingComparator:^(id obj1, id obj2) {
//        if ([obj1 isKindOfClass:[UILocalNotification class]] && [obj2 isKindOfClass:[UILocalNotification class]])
//        {
//            UILocalNotification *notif1 = (UILocalNotification *)obj1;
//            UILocalNotification *notif2 = (UILocalNotification *)obj2;
//            return [notif1.fireDate compare:notif2.fireDate];
//        }
//        
//        return NSOrderedSame;
//    }];
//    // if there are any pending notifications -> adjust their badge number
//    if (pendingNotifications.count != 0)
//    {
//        // clear all pending notifications
//        [[UIApplication sharedApplication] cancelAllLocalNotifications];
//        
//        // the for loop will 'restore' the pending notifications, but with corrected badge numbers
//        // note : a more advanced method could 'sort' the notifications first !!!
//        
//        for (UILocalNotification *notification in pendingNotifications)
//        {
//            // modify the badgeNumber
//            badge++;
//            notification.applicationIconBadgeNumber = badge;
//            
//            // schedule 'again'
//            [[UIApplication sharedApplication] scheduleLocalNotification:notification];
//        }
//    }
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
    DBChara *chara = new DBChara();
    NSInteger badge = chara->getUnreadNotification();
    application.applicationIconBadgeNumber = badge;
    
    /// reload notification
    NSArray *pendingNotifications = [[[UIApplication sharedApplication] scheduledLocalNotifications] sortedArrayUsingComparator:^(id obj1, id obj2) {
        if ([obj1 isKindOfClass:[UILocalNotification class]] && [obj2 isKindOfClass:[UILocalNotification class]])
        {
            UILocalNotification *notif1 = (UILocalNotification *)obj1;
            UILocalNotification *notif2 = (UILocalNotification *)obj2;
            return [notif1.fireDate compare:notif2.fireDate];
        }
        
        return NSOrderedSame;
    }];
    // if there are any pending notifications -> adjust their badge number
    if (pendingNotifications.count != 0)
    {
        // clear all pending notifications
        [[UIApplication sharedApplication] cancelAllLocalNotifications];
        
        // the for loop will 'restore' the pending notifications, but with corrected badge numbers
        // note : a more advanced method could 'sort' the notifications first !!!
        
        for (UILocalNotification *notification in pendingNotifications)
        {
            // modify the badgeNumber
            badge++;
            notification.applicationIconBadgeNumber = badge;
            
            // schedule 'again'
            [[UIApplication sharedApplication] scheduleLocalNotification:notification];
        }
    }
}

- (void) application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    UIApplicationState state = [[UIApplication sharedApplication] applicationState];
    if (state == UIApplicationStateActive)
    {
        NSLog(@"App is running!");
    }
    else
    {
        NSDictionary *userinfor = [notification userInfo];
        NSLog(@"Chara(recived) ID %li",(long)[[userinfor valueForKey:@"ID"] integerValue]);
//
//        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
//        NSInteger value = [defaults integerForKey:@"notification_charaid"];
//        if(value >= 1)
//        {
//        [defaults setInteger:(int)[[userinfor valueForKey:@"ID"] integerValue] forKey:@"notification_charaid"];
//        [defaults synchronize];
//
            MainApp * mApp = new MainApp();
            mApp->setCurrentChara((int)[[userinfor valueForKey:@"ID"] integerValue]);
            mApp->changeState(ConstValue::STATE_TALK_DETAIL);
//        }
    }
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
