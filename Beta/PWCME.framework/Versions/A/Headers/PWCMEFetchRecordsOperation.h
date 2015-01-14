//
//  PWCMEFetchRecordsOperation.h
//  PWCME2
// 8/28/14.
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

#import "PWCMEOperation.h"

@class PWCMERecord, PWCMERecordID;

/**
 A `PWCMEFetchRecordsOperation` object retrieves `PWCMERecord` objects with known IDs from Phunware CME. Use this operation to retrieve the entire contents of each record or a subset of its contained values. As records become available, the operation object reports progress about the state of the operation to several different blocks, which you can use to process the results.
 
 Fetching records is a common use of Phunware CME even if your app does not cache record IDs locally.
 
 The blocks you assign to process the fetched records are executed serially on an internal queue managed by the fetch records operation. Your blocks must be capable of executing on a background thread, so any tasks that require access to the main thread must be redirected accordingly.
 
 If you assign a completion block to the `completionBlock` property of the operation object, the completion block is called after the operation executes and returns its results to you. You can use a completion block to perform housekeeping chores related to the operation, but do not use it to process the results of the operation itself. Any completion block you specify should be prepared to handle the failure of the operation to complete its task, whether due to an error or an explicit cancellation.
 */
@interface PWCMEFetchRecordsOperation : PWCMEOperation

/**
 The array of IDs corresponding to the records to fetch.
 @discussion Use this property to view or change the IDs of the records you want to retrieve. Each item in the array must be a `PWCMERecordID` object.
 
 If you intend to specify a value other than `nil`, do so before executing the operation or submitting the operation object to a queue. The records you fetch do not need to be in the same record zone. The record ID for each record provides the zone information needed by the server to fetch the corresponding record.
 */
@property (nonatomic, copy) NSArray /* PWCMERecordID */ *recordIDs;

/**
 The block to execute when the results of a single record are available.
 @discussion The block returns no value and takes the following parameters:
 - record: The retrieved record or `nil` if the specified record cannot be retrieved.
 - recordID: The ID of the record. This value corresponds to one of the IDs you specified in the recordIDs property.
 - error: An error object containing information about a problem or `nil` if the results are retrieved successfully.
 */
@property (nonatomic, copy) void (^perRecordCompletionBlock)(PWCMERecord *record, PWCMERecordID *recordID, NSError *error);

/**
 The block to execute after all records are fetched or have received appropriate errors. This block is called when the operation completes. The `[NSOperation completionBlock]` will also be called if both are set.
 @discussion The block returns no value and takes the following parameters:
 - recordsByRecordID: A dictionary containing the records that are retrieved successfully. Each key in the dictionary is a `PWCMERecordID` object corresponding to a record you requested. The value of each key is the corresponding `PWCMERecord` object that was retrieved from the database.
 - operationError: An error object containing information about a problem or `nil` if the results are retrieved successfully.
 
 The operation object executes this block only once and is your last chance to process the operation results. The block is executed after all of the individual progress blocks but before the operation’s completion block. The block is executed serially with respect to the other progress blocks of the operation.
 
 This block reports an error of type `PWCMEErrorPartialFailure` when it retrieves only some of the records successfully. The userInfo dictionary of the error contains a `PWCMEPartialErrorsByItemIDKey` key whose value is an `NSDictionary` object. The keys of that dictionary are the IDs of the records that were not retrieved, and the corresponding values are error objects containing information about what happened.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, copy) void (^fetchRecordsCompletionBlock)(NSDictionary /* PWCMERecordID * -> PWCMERecord */ *recordsByRecordID, NSError *operationError);

/** Initializes and returns an operation object. */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Initializes and returns an operation object configured to fetch records with the specified IDs.
 @param recordIDs An array of `PWCMERecordID` objects representing the records you want to retrieve. This parameter is used to initialize the value in the recordIDs property. If `nil`, you must assign an appropriate value to the `recordIDs` property before executing the operation.
 
 If any of the objects in the array are not `PWCMERecordID` objects, this method raises an exception.
 @return An initialized operation object.
 @discussion The returned operation object is configured to retrieve all fields of the record, including any assets stored in those fields. If you want to minimize the amount of data initially returned, configure the desiredKeys property with the subset of keys whose values you want to retrieve.
 
 After initializing the operation, you must associate at least one progress block with the operation object (excluding the completion block) to process the results.
 */
- (instancetype)initWithRecordIDs:(NSArray /* PWCMERecord */ *)recordIDs;

@end
