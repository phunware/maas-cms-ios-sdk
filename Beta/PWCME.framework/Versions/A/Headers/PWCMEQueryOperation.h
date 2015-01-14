//
//  PWCMEQueryOperation.h
//  PWCME
// 8/27/14.
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

@import Foundation;

#import "PWCMEDefines.h"
#import "PWCMEOperation.h"

PWCME_EXTERN const NSUInteger PWCMEQueryOperationMaximumResults;

@class PWCMERecord, PWCMEQuery, PWCMEQueryCursor;

/**
 A `PWCMEQueryOperation` object is a concrete operation that you can use to execute queries against a container. A query operation takes the query parameters you provide and applies those parameters to the specified container, delivering any matching records asynchronously to the blocks that you provide.
 
 To perform a new search:
 
 1. Initialize a `PWCMEQueryOperation` object with a `PWCMEQuery` object containing the search criteria and sorting information for the records you want.
 
 2. Assign a block to the queryCompletionBlock property so that you can process the results and execute the operation.
 
 If the search yields many records, the operation object may deliver a portion of the total results to your blocks immediately, along with a cursor for obtaining the remaining records. If a cursor is provided, use it to initialize and execute a separate `PWCMEQueryOperation` object when you are ready to process the next batch of results.
 
 3. Optionally configure the return results by specifying values for the resultsLimit and desiredKeys properties.
 
 4. Pass the query operation object to the `addOperation:` method of the target container to execute the operation against that container.
 */

@interface PWCMEQueryOperation : PWCMEOperation

/** The query to use for the search. 
 @discussion You set the initial value of this property with the `initWithQuery:` method. When the value in the cursor property is `nil`, the query operation uses the `PWCMEQuery` object in this property to execute a new search and return the results to your completion handler. If the cursor value is not `nil`, the cursor is used instead.
 
 If you intend to specify or change the value of this property, do so before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, copy) PWCMEQuery *query;

/**
 The data cursor to use for continuing the search.
 @discussion  You set the initial value of this property with the `initWithCursor:` method. When you use a cursor, the contents of the query property are ignored. The data cursor stored in this property is an opaque object that is provided to you by the server. For more information about getting this cursor, see the `queryCompletionBlock` property.
 
 If you intend to specify or change the value in this property, do so before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, copy) PWCMEQueryCursor *cursor;

/**
 Defaults to PWCMEQueryOperationMaximumResults.
 Queries may return fewer than resultsLimit in some scenarios:
 - There are legitimately fewer than 'resultsLimit' number of records matching the query (and visible to the current user).
 - During the process of querying and fetching the results, some records were deleted, or became unreadable by the current user.
 When determining if there are more records to fetch, always check for the presence of a cursor in queryCompletionBlock. 
 */
@property (nonatomic, assign) NSUInteger resultsLimit;

/** This block will be called once for every record that is returned as a result of the query. The callbacks will happen in the order that the results were sorted in. 
 */
@property(nonatomic, copy) void (^recordFetchedBlock)(PWCMERecord *record);

/**
 This block is called when the operation completes.
 The `[NSOperation completionBlock]` will also be called if both are set.
 */
@property (nonatomic, copy) void (^queryCompletionBlock)(NSArray *records, PWCMEQueryCursor *cursor, NSError *operationError);

/** The standard initializer is not available for `PWCMEQueryOperation`. */
- (instancetype)init NS_UNAVAILABLE;

/** 
 Initializes and returns an operation object configured to search for records in the specified container.
 @param query The query to use during the search. This parameter must not be `nil`.
 @return An initialized operation object.
 @discussion You can use the returned PWCMEQueryOperation object only once to perform a search, but the object you specify in the query parameter can be reused as needed. When executed, this query object performs a new search and returns the first batch of results. If there are more results available, you must create a separate query object using the provided cursor object.
 */
- (instancetype)initWithQuery:(PWCMEQuery *)query NS_DESIGNATED_INITIALIZER;

/**
 Initializes and returns an operation object that returns more results from a previous search.
 @param cursor The cursor object identifying the previous search. This value is passed to the completion block of the previous search. For more information, see the `queryCompletionBlock` property.
 @return An initialized operation object ready to continue the search.
 @discussion Use this method to initialize a query operation that retrieves the next batch of results from a previous search. When executing searches based on a cursor, do not cache cursor objects for a long time before using them. A cursor is not a snapshot of the previous search results; it stores a relative offset into the results list. An operation object created using a cursor performs a new search, sorts the new set of results and uses the previous offset value to determine where the next batch of results starts.
 */
- (instancetype)initWithCursor:(PWCMEQueryCursor *)cursor NS_DESIGNATED_INITIALIZER;

@end
