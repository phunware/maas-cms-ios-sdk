//
//  PWCMEFetchSchemasOperation.h
//  PWCME
// 10/24/14.
//  Copyright (c) 2014 Phunware Inc. All rights reserved.
//

#import "PWCMEOperation.h"

@class PWCMESchema;

/**
 A `PWCMEFetchSchemasOperation` object retrieves `PWCMESchema` objects with known IDs from Phunware CME. Use this operation object to fetch record zones so that you can ascertain their capabilities.
 
 If you assign a completion block to the `completionBlock` property of the operation object, the completion block is called after the operation executes and returns its results to you. You can use a completion block to perform housekeeping chores related to the operation, but do not use it to process the results of the operation itself. Any completion block you specify should be prepared to handle the failure of the operation to complete its task, whether due to an error or an explicit cancellation.
 */
@interface PWCMEFetchSchemasOperation : PWCMEOperation

/**
 The IDs of the schemas you want to retrieve.
 @discussion Use this property to view or change the IDs of the schemas you want to retrieve. Each item in the array must be an `NSString` object. If you intend to change the value of this property, do so before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, copy) NSArray *schemaIdentifiers;

/**
 The block to execute when the results of a single schema are available.
 @discussion The block returns no value and takes the following parameters:
 - schema: The retrieved schema or `nil` if the specified schema cannot be retrieved.
 - error: An error object containing information about a problem or `nil` if the results are retrieved successfully.
 
 The operation object executes this block once for each schema ID in the `schemaIdentifiers` property. Each time the block is executed, it is executed serially with respect to the other progress blocks of the operation.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, copy) void (^perSchemaCompletionBlock)(PWCMESchema *schema, NSError *error);

/**
 The block to execute with the fetch results. The `[NSOperation completionBlock]` will also be called if both are set.
 @discussion The block returns no value and takes the following parameters:
 - schemas: An array of returned schemas.
 - operationError: An error object containing information about a problem or `nil` if the results are retrieved successfully.
 
 This block is executed only once and is your only chance to process the operation results. It is executed before the operation’s completion block. Your block must be capable of executing on a background thread, so any tasks that require access to the main thread must be redirected accordingly.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue.
 
 This block reports an error of type `PWCMEErrorPartialFailure` when it retrieves only some of the schemas successfully. The userInfo dictionary of the error contains a `PWCMEPartialErrorsByItemIDKey` key whose value is an NSDictionary object. The keys of that dictionary are the IDs of the schemas that were not retrieved and the corresponding values are error objects containing information about what happened.
 */
@property (nonatomic, copy) void (^fetchSchemasCompletionBlock)(NSArray /* PWCMESchema */ *schemas, NSError *operationError);

/**
 Initializes and returns an operation object configured to fetch the specified schemas.
 @param schemaIdentifiers An array of `NSString` objects representing the schemas you want to retrieve. This parameter is used to initialize the value in the `schemaIdentifiers` property. If you specify `nil`, you must assign a value to the `schemaIdentifiers` property before executing the operation.
 @return An initialized operation object.
 @discussion After initializing the operation, assign a block to the `fetchSchemasCompletionBlock` property to process the results.
 */
- (instancetype)initWithSchemaIdentifiers:(NSArray *)schemaIdentifiers;

/**
 Initializes and returns an operation object.
 @return An initialized operation object.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end
