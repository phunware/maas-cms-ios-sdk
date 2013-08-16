//
//  PWMainViewController.h
//  Wheel Of Lunch
//
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import "iCarousel.h"

@interface PWMainViewController : UIViewController <iCarouselDataSource, iCarouselDelegate>

@property (nonatomic, strong) iCarousel *carousel;
@property (nonatomic, strong) NSMutableArray *lunchOptions;

@end
