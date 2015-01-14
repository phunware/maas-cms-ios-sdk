//
//  PWCMEFetchContainersOperation.h
//  PWCME2
//
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

#import "PWCMEOperation.h"

/**
 A `PWCMEFetchContainersOperation` object retrieves `PWCMEContainer` objects with known IDs from Phunware CME. As containers become available, the operation object reports progress about the state of the operation to several different blocks, which you can use to process the results.
 
 The blocks you assign to process the fetched records are executed serially on an internal queue managed by the fetch containers operation. Your blocks must be capable of executing on a background thread, so any tasks that require access to the main thread must be redirected accordingly.
 
 If you assign a completion block to the `completionBlock` property of the operation object, the completion block is called after the operation executes and returns its results to you. You can use a completion block to perform housekeeping chores related to the operation, but do not use it to process the results of the operation itself. Any completion block you specify should be prepared to handle the failure of the operation to complete its task, whether due to an error or an explicit cancellation.
 */
@interface PWCMEFetchContainersOperation : PWCMEOperation

/**
 The array of IDs corresponding to the containers to fetch.
 @discussion Use this property to view the IDs of the records you want to retrieve. Each item in the array must be an `NSString` object.
 
 If you intend to specify a value other than `nil`, do so before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, readonly) NSArray /* NSString */ *containerIDs;

/**
 The block to execute when the results of a single record are available.
 @discussion The block returns no value and takes the following parameters:
 - container: The retrieved container or `nil` if the specified container cannot be retrieved.
 - error: An error object containing information about a problem or nil if the results are retrieved successfully.
 */
@property (nonatomic, copy) void (^perContainerCompletionBlock)(PWCMEContainer *container, NSError *error);

/**
 The block to execute after all records are fetched or have received appropriate errors.
 @discussion The block returns no value and takes the following parameters:
 - containers: An array containing the containers that are retrieved successfully.
 - operationError: An error object containing information about a problem or `nil` if the results are retrieved successfully.
 */
@property (nonatomic, copy) void (^fetchContainersCompletionBlock)(NSArray /* PWCMEContainer */ *containers, NSError *operationError);

/** NOTE: The standard initializer is unavailale for this operation. */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Initializes and returns an operation object configured to fetch the containers with the specified IDs.
 @param containerIDs An array of `NSString` objects representing the containers you want to retrieve. This parameter is used to initialize the value in the `containerIDs` property. Cannot be `nil`.
 
 If any of the objects in the array are not `NSString` objects, this method raises an exception.
 @return An initialized operation object.
 @discussion After initializing the operation, you must associate at least one progress block with the operation object (excluding the completion block) to process the results.
 */
- (instancetype)initWithContainerIDs:(NSArray /* NSString */ *)containerIDs;

@end
