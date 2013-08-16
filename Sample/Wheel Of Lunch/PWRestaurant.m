//
//  PWRestaurant.m
//  Wheel Of Lunch
//
//  Created by Illya Busigin on 8/14/13.
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import "PWRestaurant.h"

@implementation PWRestaurant

+ (instancetype)unpack:(NSDictionary *)dictionary
{
    PWRestaurant *restaurant = [[self alloc] init];
    
    restaurant.name = dictionary[@"name"];
    restaurant.imageURL = dictionary[@"image_url"];
    
    return restaurant;
}

@end
