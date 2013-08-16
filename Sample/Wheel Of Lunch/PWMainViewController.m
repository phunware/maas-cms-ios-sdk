//
//  PWMainViewController.m
//  Wheel Of Lunch
//
//  Created by Illya Busigin on 8/14/13.
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import "PWMainViewController.h"
#import "PWLunchView.h"
#import "PWRestaurant.h"

#import "AFNetworking.h"

#import <MaaSCMS/MaaSCMS.h>

@interface PWMainViewController ()

@property (nonatomic, weak) UIActivityIndicatorView *activityIndicator;

@end

@implementation PWMainViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	
    [[UIApplication sharedApplication] setStatusBarHidden:YES];
    
    self.lunchOptions = @[].mutableCopy;
    
    [self setupCarousel];
    
    UIActivityIndicatorView *activityIndicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    activityIndicator.center = self.view.center;
    activityIndicator.hidesWhenStopped = YES;
    activityIndicator.userInteractionEnabled = NO;
    
    [activityIndicator startAnimating];
    
    [self.view addSubview:activityIndicator];
    self.activityIndicator = activityIndicator;
    
    [self fetchLunchOptions];
}

- (void)setupCarousel
{
    // Boilerplate
    iCarousel *carousel = [[iCarousel alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]];
    carousel.backgroundColor = [UIColor redColor];
    carousel.dataSource = self;
    carousel.delegate = self;
    carousel.type = iCarouselTypeCylinder;
    carousel.vertical = YES;
    
    [self.view addSubview:carousel];
    self.carousel = carousel;
    
    // Add a nifty gradient background
    UIColor *colorOne = [UIColor colorWithRed:(29/255.0) green:(174/255.0) blue:(236/255.0) alpha:1.0];
    UIColor *colorTwo = [UIColor colorWithRed:(34/255.0)  green:(153/255.0)  blue:(212/255.0)  alpha:1.0];
    
    NSArray *colors = @[(id)colorOne.CGColor, (id)colorTwo.CGColor];
    NSNumber *stopOne = @(0.0);
    NSNumber *stopTwo = @(1.0);
    
    NSArray *locations = @[stopOne, stopTwo];
    
    CAGradientLayer *headerLayer = [CAGradientLayer layer];
    headerLayer.colors = colors;
    headerLayer.locations = locations;
    headerLayer.shouldRasterize = YES;
    
    headerLayer.frame = self.carousel.bounds;
    [self.carousel.layer insertSublayer:headerLayer atIndex:0];
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [self.view becomeFirstResponder];
    
}


-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    [self.view resignFirstResponder];
}


#pragma mark - Memory Management

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
    self.carousel.delegate = nil;
    self.carousel.dataSource = nil;
}


#pragma mark - Shake Handling

- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event
{
    if (event.subtype == UIEventSubtypeMotionShake)
    {
        // Shake detected
        [self spinWheelOfLunch];
    }
    
    if ([super respondsToSelector:@selector(motionEnded:withEvent:)])
    {
        [super motionEnded:motion withEvent:event];
    }
}

- (BOOL)canBecomeFirstResponder
{
    return YES;
}

#pragma mark - Convenience

- (void)fetchLunchOptions
{
    __weak __typeof(&*self)weakSelf = self;
    
    [MaaSCMS getContentsForContainerID:@"520d421d7cbc6ee477000008" structureID:6 limit:100 offset:0 success:^(NSArray *contents, PWPagination *pagination, BOOL pagingEnabled) {
       
        // Process contents
        for (NSDictionary *dictionary in contents)
        {
            PWRestaurant *restaurant = [PWRestaurant unpack:dictionary];
            
            [self.lunchOptions addObject:restaurant];
        }
        
        [weakSelf.carousel reloadData];
        
        [weakSelf.activityIndicator stopAnimating];
    } failure:^(NSError *error) {
        NSLog(@"Error: %@", error.localizedDescription);
        [weakSelf.activityIndicator stopAnimating];
    }];
}

- (void)spinWheelOfLunch
{
    // Time to spin the wheel of lucnh!
    NSInteger randomRestaurantIndex = arc4random_uniform(20) + 1;
    [self.carousel scrollByNumberOfItems:20+randomRestaurantIndex duration:3];
}


#pragma mark - iCarousel methods

- (NSUInteger)numberOfItemsInCarousel:(iCarousel *)carousel
{
    return [self.lunchOptions count];
}

- (UIView *)carousel:(iCarousel *)carousel viewForItemAtIndex:(NSUInteger)index reusingView:(UIView *)view
{
    // Get our lunch view
    PWLunchView *lunchView = (PWLunchView *)view;
    
    if (view == nil)
    {
        lunchView = [PWLunchView create];
    }
    
    // Get the restaurant information
    PWRestaurant *restaurant = self.lunchOptions[index];
    
    // Populate with restaurant information
    [lunchView.lunchImageView setImageWithURL:[NSURL URLWithString:restaurant.imageURL] placeholderImage:[UIImage imageNamed:@"placeholder"]];
    
    return lunchView;
}

- (NSUInteger)numberOfPlaceholdersInCarousel:(iCarousel *)carousel
{
    //note: placeholder views are only displayed on some carousels if wrapping is disabled
    return 0;
}

- (CATransform3D)carousel:(iCarousel *)carousel itemTransformForOffset:(CGFloat)offset baseTransform:(CATransform3D)transform
{
    //implement 'flip3D' style carousel
    transform = CATransform3DRotate(transform, M_PI / 8.0f, 0.0f, 1.0f, 0.0f);
    return CATransform3DTranslate(transform, 0.0f, 0.0f, offset * carousel.itemWidth);
}

- (CGFloat)carousel:(iCarousel *)carousel valueForOption:(iCarouselOption)option withDefault:(CGFloat)value
{
    //customize carousel display
    switch (option)
    {
        case iCarouselOptionWrap:
        {
            //normally you would hard-code this to YES or NO
            return YES;
        }
        case iCarouselOptionSpacing:
        {
            //add a bit of spacing between the item views
            return value * 1.05f;
        }
        case iCarouselOptionFadeMax:
        {
            if (carousel.type == iCarouselTypeCustom)
            {
                //set opacity based on distance from camera
                return 0.0f;
            }
            return value;
        }
        default:
        {
            return value;
        }
    }
}


#pragma mark - iCarousel Delegate

- (void)carousel:(iCarousel *)carousel didSelectItemAtIndex:(NSInteger)index
{
    NSNumber *item = (self.lunchOptions)[index];
    NSLog(@"Tapped view number: %@", item);
}

@end
