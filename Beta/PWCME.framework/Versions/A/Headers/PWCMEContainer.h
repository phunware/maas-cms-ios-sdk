//
//  PWCMEContainer.h
//  PWCME
//
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

@import Foundation;
#import <PWCME/PWCMEObject.h>

@class PWCMEOperation, PWCMEObject, PWCMERecord, PWCMERecordID, PWCMEStructure, PWCMESchema, PWCMEQuery;

/**
 A `PWCMEContainer` object encapsulates content associated with an app, including content that is publicly accessible to all users of the app and content that is private to a specific user. A container object manages all explicit and implicit attempts to access the contents of the container.
 
 Your application must set a valid `defaultContainer`.
 
 Most of these calls operate on a single item in the current container and allow for simple operations. If you'd like to batch your requests, add dependencies between requests, set priorities or schedule operations on your own queue, take a look at the corresponding `PWCMEOperation`.
 */

@interface PWCMEContainer : PWCMEObject <NSSecureCoding>

/** The name of the container. (read-only) */
@property (nonatomic, readonly) NSString *name;

/** The string that identifies the app’s container. (read-only) 
 @discussion Use the value in this property to distinguish between different container objects in your app.
 */
@property (nonatomic, readonly) NSString *containerIdentifier;

/**
 The queue on which container operations are posted.
*/
@property (nonatomic, readonly) NSOperationQueue *operationQueue;

/**
 Returns the default container object for managing the current app’s content.
 @return The container object associated with the current app’s content. This method always returns a valid container object.
 @discussion Use this method to retrieve the container for your app’s native content. This container is the one your app typically uses to store its data. If you want the container for a different app, create and initialize that container using the containerWithIdentifier: method. The default container is persisted.
 */
+ (instancetype)defaultContainer;

/** Specify the default container.
 @param container The default container. This parameter cannot be `nil`. 
 */
+ (void)setDefaultContainer:(PWCMEContainer *)container;

///--------------------------
/// @name Getting A Container
///--------------------------

/** 
 Instantiates a container with the given container identifier.
 @param containerIdentifier The identifier of the container. This parameter cannot be `nil`.
 @discussion This method instantiates a container locally and does not seek to fetch additional container metadata such as the name.
 */
+ (instancetype)containerWithIdentifier:(NSString *)containerIdentifier;


/**
 Instantiates a container with the given container identifier.
 @param containerIdentifier The identifier of the container. This parameter cannot be `nil`.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
 
 - container: The requested container object. If no such record is found, this parameter is `nil`.
 
 - error: An error object, or `nil` if the container was fetched successfully. Use the information in the error object to determine whether a problem has a workaround.
 
 @discussion Use this method to fetch a container that is not urgent to your app’s execution. This method fetches the container with a default priority, which may cause the task to execute after higher-priority tasks. To fetch container more urgently, create a `PWCMEFetchContainersOperation` object with the desired priority. You can also use that operation object to fetch multiple containers simultaneously.
 @discussion This method attempts to fetch the remote container.
 */
+ (void)fetchContainerWithIdentifier:(NSString *)containerIdentifier completionHandler:(void (^)(PWCMEContainer *container, NSError *error))completionHandler;

/**
 Queues an operation for execution in the current container.
 @param operation The operation to queue.
 @discussion This method adds the operation object to an operation queue managed by the container itself. Operation objects in the container’s queue execute concurrently with default priorities in background threads.
 
 This method changes the operation object’s container (if any) to the current container. 
 */
- (void)addOperation:(PWCMEOperation *)operation;

@end


///--------------------------
/// @name Convenience Methods
///--------------------------

/**
 These calls operate on a single item in the current container and allow for simple operations. If you'd like to batch your requests, add dependencies between requests, set priorities, or schedule operations on your own queue, take a look at the corresponding PWCMEOperation.
 */

@interface PWCMEContainer (Convenience)

/**
 Returns all containers that the application has access to.
 @param completionHandler A block object to be executed when `fetchAllContainersWithCompletionHandler:` is complete. This block has no return value and takes two argument: an `NSArray` of returned containers and an `NSError` object describing the error that occurred.
 */
+ (void)fetchAllContainersWithCompletionHandler:(void (^)(NSArray /* PWCMEContainer */ *containers, NSError *error))completionHandler;

/** Fetches one record asynchronously from the current container. 
 @param recordID The ID of the record you want to fetch. This method throws an exception if this parameter is `nil`.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
 
 - record: The requested record object. If no such record is found, this parameter is `nil`.
 
 - error: An error object, or `nil` if the record was fetched successfully. Use the information in the error object to determine whether a problem has a workaround
 
 @discussion Use this method to fetch records that are not urgent to your app’s execution. This method fetches the record with a default priority, which may cause the task to execute after higher-priority tasks. To fetch records more urgently, create a `PWCMEFetchRecordsOperation` object with the desired priority. You can also use that operation object to fetch multiple records simultaneously.
 */
- (void)fetchRecordWithID:(PWCMERecordID *)recordID completionHandler:(void (^)(PWCMERecord *record, NSError *error))completionHandler;

/**
 Saves one record asynchronously to the current database.
 @param record The record to save. This method throws an exception if this parameter is `nil`.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
 - record: The record object you attempted to save.
 - error: An error object, or `nil` if the record was saved successfully. Use the information in the error object to determine whether a problem has a workaround.
 
 @discussion This method saves the record only if it has never been saved before or if it is newer than the version on the server. You cannot use this method to overwrite newer versions of a record on the server.
 
 This method saves the record with a default priority, which may cause the task to execute after higher-priority tasks. To save records more urgently, create a `PWCMEModifyRecordsOperation` object with the desired priority. You can also use that operation object to save multiple records simultaneously.
 */
- (void)saveRecord:(PWCMERecord *)record completionHandler:(void (^)(PWCMERecord *record, NSError *error))completionHandler;

/** Deletes the specified record asynchronously from the current container.
 @param recordID The ID of the record you want to delete. This method throws an exception if this parameter is `nil`.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
 
 - record: The record ID you attempted to delete. If no such record is found, this parameter is `nil`.
 
 - error: An error object or `nil` if the record was fetched successfully. Use the information in the error object to determine whether a problem has a workaround.
 
 @discussion Deleting a record may trigger additional deletions if the record was referenced by other records. This method reports only the ID of the record you asked to delete. PWCME does not report deletions triggered by owning relationships between records.
 
 This method deletes the record with a default priority, which may cause the task to execute after higher-priority tasks. To delete records more urgently, create a `PWCMEModifyRecordsOperation` object with the desired priority. You can also use that operation object to delete multiple records simultaneously.
 */
- (void)deleteRecordWithID:(PWCMERecordID *)recordID completionHandler:(void (^)(PWCMERecordID *recordID, NSError *error))completionHandler;

/**
 Searches the current container asynchronously for records that match the query parameters.
 @param query The query object containing the parameters for the search. This method throws an exception if this parameter is nil. For information about how to construct queries, see `PWCMEQuery` Class Reference.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
 
 - results: An array containing zero or more PWCMERecord objects. The returned records correspond to the records in the current container that match the parameters of the query.
 
 - error: An error object or `nil` if the record was fetched successfully. Use the information in the error object to determine whether a problem has a workaround.
 
 @discussion Use this method to execute searches against the current container.
 
 Do not use this method when the number of returned records is potentially more than a hundred records. For efficiency, all queries automatically limit the number of returned records based on current conditions. If your query hits the maximum value, this method returns only the first portion of the overall results. The number of returned records should be sufficient in most cases, but to get the entire set of records you must use a `PWCMEQueryOperation` object instead. Query operations also return a maximum number of results, but when they do, they provide a cursor object that you can use to fetch the next batch of results.
 */
- (void)performQuery:(PWCMEQuery *)query completionHandler:(void (^)(NSArray /* PWCMEREcord */ *results, NSError *error))completionHandler;

// Structures

/**
 Fetches all structures in the current container.
 @return A newly allocated operation object.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
 
 - structures: An array containing zero or more `PWCMEStructure` objects. The returned structures correspond to the structures in the current container.
 
 - error: An error object, or `nil` if the structuress were fetched successfully. Use the information in the error object to determine whether a problem has a workaround.
 */
- (void)fetchAllStructuresWithCompletionHandler:(void (^)(NSArray /* PWCMEStructure */ *structures, NSError *error))completionHandler;

/** Fetches specified structures asynchronously from the current container.
 @param structureIdentifiers An array of structure identifiers that you want to fetch. This method throws an exception if this parameter is `nil`. Structure identifiers must be of type `NSNumber`.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
 
 - schemas: An array containing zero or more `PWCMEStructure` objects.
 - error: An error object or `nil` if the record was fetched successfully. Use the information in the error object to determine whether a problem has a workaround.
 
 @discussion Use this method to fetch structures that are not urgent to your app’s execution. This method fetches the structures with a default priority, which may cause the task to execute after higher-priority tasks. To fetch structures more urgently, create a `PWCMEFetchStructuresOperation` object with the desired priority. You can also use that operation object to fetch multiple records simultaneously.
 */
- (void)fetchStructures:(NSArray *)structureIdentifiers completionHandler:(void (^)(NSArray /* PWCMEStructure */ *structures, NSError *error))completionHandler;

/** Fetches specified schemas asynchronously from the current container.
 @param schemaIdentifiers An array of schema identifiers that you want to fetch. This method throws an exception if this parameter is `nil`. Schema identifiers must be of type `NSString`.
 @param completionHandler The block to execute with the results. Your block must be capable of running on any thread of the app and take the following parameters:
    - schemas: An array containing zero or more `PWCMESchema` objects.
    - error: An error object or `nil` if the record was fetched successfully. Use the information in the error object to determine whether a problem has a workaround.
 
 @discussion Use this method to fetch schemas that are not urgent to your app’s execution. This method fetches the schemas with a default priority, which may cause the task to execute after higher-priority tasks. To fetch schemas more urgently, create a `PWCMEFetchSchemasOperation` object with the desired priority. You can also use that operation object to fetch multiple records simultaneously.
 */
- (void)fetchSchemas:(NSArray *)schemaIdentifiers completionHandler:(void (^)(NSArray /* PWCMESchema */ *schemas, NSError *error))completionHandler;

@end