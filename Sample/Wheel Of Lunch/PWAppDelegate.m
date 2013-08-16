//
//  PWAppDelegate.m
//  Wheel Of Lunch
//
//  Created by Illya Busigin on 8/14/13.
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import "PWAppDelegate.h"
#import "PWMainViewController.h"

#import <MaaSCore/MaaSCore.h>

@implementation PWAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [MaaSCore setApplicationID:@"60"
                     accessKey:@"33f45a36278b56930483729cba08d5edb2659623"
                  signatureKey:@"52e33c107589f6946c0b0e61c521d8ed975959d2"
                 encryptionKey:@""];
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.mainViewController = [PWMainViewController new];
                                
    self.window.rootViewController = self.mainViewController;
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
