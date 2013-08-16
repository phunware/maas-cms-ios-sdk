//
//  PWLunchView.h
//  Wheel Of Lunch
//
//  Created by Illya Busigin on 8/14/13.
//  Copyright (c) 2013 Phunware, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PWLunchView : UIView

@property (nonatomic, weak) UIView *contentView;
@property (nonatomic, weak) UIImageView *lunchImageView;
@property (nonatomic, weak) UILabel *lunchLabel;

+ (instancetype)create;

@end
