//
//  PWLunchView.m
//  Wheel Of Lunch
//
//  Created by Illya Busigin on 8/14/13.
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import "PWLunchView.h"

#import <QuartzCore/QuartzCore.h>

@implementation PWLunchView

#pragma mark - Initialization & Setup

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self)
    {
        [self commonSetup];
    }
    
    return self;
}

- (void)commonSetup
{
    // Setup the main view
    self.backgroundColor = [UIColor blueColor];
    self.layer.masksToBounds = NO;
    self.layer.cornerRadius = 8; // if you like rounded corners
    self.layer.shadowOffset = CGSizeMake(0, 2);
    self.layer.shadowRadius = 5;
    self.layer.shadowOpacity = 0.5;
    self.layer.shadowPath = [UIBezierPath bezierPathWithRect:self.bounds].CGPath;
    self.layer.rasterizationScale = [UIScreen mainScreen].scale;
    
    // Setup the content view
    UIView *contentView = [[UIView alloc] initWithFrame:self.bounds];
    contentView.backgroundColor = [UIColor clearColor];
    contentView.layer.cornerRadius = 8;
    contentView.clipsToBounds = YES;
    contentView.layer.rasterizationScale = [UIScreen mainScreen].scale;
    contentView.layer.shouldRasterize = YES;
    
    [self addSubview:contentView];
    self.contentView = contentView;
    
    // Add a gradient
    UIColor *colorOne = [UIColor colorWithWhite:0.9 alpha:1.0];
    UIColor *colorTwo = [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.85 alpha:1.0];
    UIColor *colorThree     = [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.7 alpha:1.0];
    UIColor *colorFour = [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.4 alpha:1.0];
    
    NSArray *colors =  [NSArray arrayWithObjects:(id)colorOne.CGColor, colorTwo.CGColor, colorThree.CGColor, colorFour.CGColor, nil];
    
    NSNumber *stopOne = [NSNumber numberWithFloat:0.0];
    NSNumber *stopTwo = [NSNumber numberWithFloat:0.02];
    NSNumber *stopThree     = [NSNumber numberWithFloat:0.99];
    NSNumber *stopFour = [NSNumber numberWithFloat:1.0];
    
    NSArray *locations = [NSArray arrayWithObjects:stopOne, stopTwo, stopThree, stopFour, nil];
    CAGradientLayer *headerLayer = [CAGradientLayer layer];
    headerLayer.colors = colors;
    headerLayer.locations = locations;
    headerLayer.frame = self.contentView.bounds;
    headerLayer.shouldRasterize = YES;
    
    
    [self.contentView.layer insertSublayer:headerLayer atIndex:0];
    
    
    UIImageView *lunchImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 200.0f, 200.0f)];
    lunchImageView.contentMode = UIViewContentModeScaleAspectFill;
    
    [self.contentView addSubview:lunchImageView];
    self.lunchImageView = lunchImageView;
    
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 200, 50)];
    label.backgroundColor = [UIColor clearColor];
    label.textAlignment = UITextAlignmentCenter;
    label.font = [label.font fontWithSize:50];
    
    [self.contentView addSubview:label];
    self.lunchLabel = label;
}


#pragma mark - Convenience

+ (instancetype)create
{
    PWLunchView *lunchView = [[self alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    
    return lunchView;
}

+ (CAGradientLayer *) greyGradient {
    
    UIColor *colorOne = [UIColor colorWithWhite:0.9 alpha:1.0];
    UIColor *colorTwo = [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.85 alpha:1.0];
    UIColor *colorThree     = [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.7 alpha:1.0];
    UIColor *colorFour = [UIColor colorWithHue:0.625 saturation:0.0 brightness:0.4 alpha:1.0];
    
    NSArray *colors =  [NSArray arrayWithObjects:(id)colorOne.CGColor, colorTwo.CGColor, colorThree.CGColor, colorFour.CGColor, nil];
    
    NSNumber *stopOne = [NSNumber numberWithFloat:0.0];
    NSNumber *stopTwo = [NSNumber numberWithFloat:0.02];
    NSNumber *stopThree     = [NSNumber numberWithFloat:0.99];
    NSNumber *stopFour = [NSNumber numberWithFloat:1.0];
    
    NSArray *locations = [NSArray arrayWithObjects:stopOne, stopTwo, stopThree, stopFour, nil];
    CAGradientLayer *headerLayer = [CAGradientLayer layer];
    headerLayer.colors = colors;
    headerLayer.locations = locations;
    
    return headerLayer;
    
}


@end
