//
//  PWAppDelegate.h
//  Wheel Of Lunch
//
//  Created by Illya Busigin on 8/14/13.
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PWMainViewController;

@interface PWAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) PWMainViewController *mainViewController;

@end
