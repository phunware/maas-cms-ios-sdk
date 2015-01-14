//
//  PWCMEOperation.h
//  PWCME
// 8/27/14.
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

@import Foundation;

@class PWCMEContainer;


/**
 The `PWCMEOperation` class is the abstract base class for all operations executed against Phunware CME. All Phunware CME operation objects descend from this class, which provides the infrastructure for executing tasks against one of your app’s containers. Do not subclass or create instances of this class directly. Instead, create instances of one of its concrete subclasses.
 
 Use the properties of this class to configure the behavior of the operation object before submitting it to an operation queue or executing it directly. Phunware CME operations involve communicating with the Phunwares' servers to send and receive data. The properties of this class let you configure the behavior of those network operations to ensure the best performance for your app.
 */

@interface PWCMEOperation : NSOperation

/** All PWCMEOperations default to `self.qualityOfService == `NSOperationQualityOfServiceUserInitiated` */

/** The container to use for the operation. If no container is set, `[PWCMEContainer defaultContainer]` is used.
 @discussion The container sets the context for where the operation should perform its work. The addOperation: method of the PWCMEContainer class implicitly set the value of this property to their container.
 
 If you execute the operation yourself, either directly or using a custom operation queue, it is recommended that you sets the value of this property explicitly. If the value is `nil` when you execute an operation, the operation object implicitly executes against your app’s default container. If no default container is present, an exception will be thrown. */
@property (nonatomic, strong) PWCMEContainer *container;

/** A Boolean value indicating whether the operation object may send data over the cell network. 
 @discussion When you send or receive many records or when you send records with large assets, you might set this property to `NO` to avoid consuming too much of the user’s cellular data bandwidth. For operations involving only a few records, it is fine to leave this property set to `YES`, which is the default.
 
 When this property is set to `NO`, the operation executes normally but fails if Wi-Fi is not available. */
@property (nonatomic, assign) BOOL allowsCellularAccess;

@end
