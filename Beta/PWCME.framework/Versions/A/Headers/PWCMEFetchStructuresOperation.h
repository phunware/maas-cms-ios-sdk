//
//  PWCMEFetchStructuresOperation.h
//  PWCME2
// 8/28/14.
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

#import "PWCMEOperation.h"

@class PWCMEStructure;

extern NSInteger const kPWCMEDepthFullyHierarchy;

/**
 A `PWCMEFetchStructuresOperation` object retrieves `PWCMEStructure` objects with known IDs from Phunware CME. Use this operation object to fetch record zones so that you can ascertain their capabilities.
 
 If you assign a completion block to the `completionBlock` property of the operation object, the completion block is called after the operation executes and returns its results to you. You can use a completion block to perform housekeeping chores related to the operation, but do not use it to process the results of the operation itself. Any completion block you specify should be prepared to handle the failure of the operation to complete its task, whether due to an error or an explicit cancellation.
 */
@interface PWCMEFetchStructuresOperation : PWCMEOperation

/** 
 The depth to traverse into child structures. If the depth is set to 0, then no child structures will be returned; if the depth is set to 1, then the immediate child structures will be returned; and so on. To get the full hierarchy of children, use `kMaaSCMSDepthFullHierarchy`. Be careful when using this value for large structures.
 */
@property (nonatomic) NSInteger depth;

/** 
 If `YES`, then the `PWSchema` objects will be returned for structures that have one.
 @discussion The default value is `NO`.
 */
@property (nonatomic) BOOL includeSchema;

/**
 The IDs of the structures you want to retrieve.
 @discussion Use this property to view or change the IDs of the structures you want to retrieve. Each item in the array must be an `NSNumber` object. If you intend to change the value of this property, do so before executing the operation or submitting the operation object to a queue.
 
 If you used the `fetchAllStructuresOperation` method to create the operation object, the contents of this property are ignored and the default value is set to `nil`.
 */
@property (nonatomic, copy) NSArray *structureIdenifiers;

/**
 The block to execute when the results of a single structure are available.
 @discussion The block returns no value and takes the following parameters:
 - structure: The retrieved structure or `nil` if the specified structure cannot be retrieved.
 - error: An error object containing information about a problem or `nil` if the results are retrieved successfully.
 
 The operation object executes this block once for each structure ID in the structureIdentifiers property. Each time the block is executed, it is executed serially with respect to the other progress blocks of the operation.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, copy) void (^perStructureCompletionBlock)(PWCMEStructure *structure, NSError *error);

/**
 The block to execute with the fetch results. The `[NSOperation completionBlock]` will also be called if both are set.
 @discussion fetchStructuresCompletionBlock The block returns no value and takes the following parameters:
 - structures: An array of returned structures.
 - operationError: An error object containing information about a problem or `nil` if the results are retrieved successfully.
 
 This block is executed only once and is your only chance to process the operation results. It is executed before the operation’s completion block. Your block must be capable of executing on a background thread, so any tasks that require access to the main thread must be redirected accordingly.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue.
 
 This block reports an error of type `PWCMEErrorPartialFailure` when it retrieves only some of the structures successfully. The userInfo dictionary of the error contains a `PWCMEPartialErrorsByItemIDKey` key whose value is an NSDictionary object. The keys of that dictionary are the IDs of the structures that were not retrieved, and the corresponding values are error objects containing information about what happened.
 */
@property (nonatomic, copy) void (^fetchStructuresCompletionBlock)(NSArray /* PWCMEStructure */ *structures, NSError *operationError);

/**
 Returns an operation object that can be used to fetch all structures in the current container.
 @return A newly allocated operation object.
 @discussion After initializing the operation, assign a value to the `fetchStructuresCompletionBlock` property to process the results.
 */
+ (instancetype)fetchAllStructuresOperation;

/**
 Initializes and returns an operation object configured to fetch the specified structures.
 @param structureIdentifiers An array of `NSNumber` objects representing the structures you want to retrieve. This parameter is used to initialize the value in the `structureIdentifiers` property. If you specify `nil`, you must assign a value to the `structureIdentifiers` property before executing the operation.
 @return An initialized operation object.
 @discussion After initializing the operation, assign a block to the `fetchStructuresCompletionBlock` property to process the results.
 */
- (instancetype)initWithStructureIdentifiers:(NSArray *)structureIdentifiers;

/**
 Returns an operation object.
 @return A newly allocated operation object.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end
