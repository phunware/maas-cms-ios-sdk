//
//  PWRestaurant.h
//  Wheel Of Lunch
//
//  Created by Illya Busigin on 8/14/13.
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PWRestaurant : NSObject

@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *imageURL;

+ (instancetype)unpack:(NSDictionary *)dictionary;

@end
