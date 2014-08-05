#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "LocalNotification.h"

using namespace std;

void LocalNotification::show(std::string message, int interval, int tag)
{
  // create notification
  NSString* noti = [[NSString alloc] initWithUTF8String:message.c_str()];
  UILocalNotification *notification = [[UILocalNotification alloc] init];
  
  notification.fireDate = [[NSDate date] dateByAddingTimeInterval:interval];
  notification.timeZone = [NSTimeZone defaultTimeZone];
  notification.alertBody = noti;
  notification.alertAction = @"Open";
  notification.soundName = UILocalNotificationDefaultSoundName;
  
  NSNumber* tag1 = [NSNumber numberWithInteger:tag];
  NSDictionary *infoDict = [NSDictionary dictionaryWithObject:tag1 forKey:@"ID"];
  notification.userInfo = infoDict;
  
  // notification register
  [[UIApplication sharedApplication] scheduleLocalNotification:notification];
  
  [notification release];
}

void LocalNotification::cancel(int tag)
{
  for(UILocalNotification *notification in [[UIApplication sharedApplication] scheduledLocalNotifications]) {
    if([[notification.userInfo objectForKey:@"ID"] integerValue] == tag) {
      [[UIApplication sharedApplication] cancelLocalNotification:notification];
    }
  }
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS