//
//  PWCMEModifyRecordsOperation.h
//  PWCME
//
//  Copyright (c) 2014 Phunware Inc. All rights reserved.
//

#import "PWCMEOperation.h"

@class PWCMERecord, PWCMERecordID;

/** Constants indicating the policy to apply when saving records. */
typedef NS_ENUM(NSInteger, PWCMERecordSavePolicy) {
    /** Locally edited keys are written to the server. Any unseen changes on the server
     will be overwritten to the locally edited value. */
    PWCMERecordSaveChangedKeys             = 1,
    /** All local keys are written to the server.  Any unseen changes on the server will be
     overwritten with the local values.  Keys present only on the server remain unchanged.
     There are two common ways in which a server record will contain keys not present locally:
     1 - Since you've fetched this record, another client has added a new key to the record.
     2 - The presence of desiredKeys on the fetch / query that returned this record meant
     that only a portion of the record's keys were downloaded. */
    PWCMERecordSaveAllKeys                 = 2,
};

/**
 A `PWCMEModifyRecordsOperation` object saves changes to one or more `PWCMERecord` objects. After modifying the fields of a record, use this type of operation object to save those changes to a database. You also use instances of this class to delete records permanently from a database.
 
 When saving a record that contains references to other records, Phunware CME must be able to find the target of those references. During a save operation, Phunware CME verifies that any target records actually exist in the container. If it cannot verify the existence of a target record, Phunware CME reports an error and does not save the record containing the reference to that target. When creating two new records that have a reference between them, use the same operation object to save both records at the same time.
 
 When you save records, the value in the savePolicy property determines how to proceed when conflicts are detected on the server. Because records can be modified between the time you fetch them and the time you save them, the save policy determines whether new changes overwrite existing changes. By default, the operation object reports an error if a newer version of a record is found on the server. You can change the default setting to permit your changes to overwrite the server values wholly or partially.
 
 The blocks you assign to monitor progress of the operation are executed serially on an internal queue managed by the operation object. Your blocks must be capable of executing on a background thread, so any tasks that require access to the main thread must be redirected accordingly.
 
 If you assign a completion block to the `completionBlock` property of the operation object, the completion block is called after the operation executes and returns its results to you. You can use a completion block to perform housekeeping chores related to the operation, but do not use it to process the results of the operation itself. Any completion block you specify should be prepared to handle the failure of the operation to complete its task, whether due to an error or an explicit cancellation.
 */
@interface PWCMEModifyRecordsOperation : PWCMEOperation

/**
 The records to save to the database.
 @discussion This property contains the array of `PWCMERecord` objects that you want to save. The initial contents of the array are set to the records you specified in the `initWithRecordsToSave:recordIDsToDelete:` method. You can modify this array as needed before executing the operation. The records must all target the same container but may belong to different structures in the container.
 
 If you intend to change the value of this property, do so before executing the operation or submitting the operation object to a queue.
 */
@property (nonatomic, copy) NSArray /* PWCMERecord */ *recordsToSave;

/**
 The IDs of the records to delete permanently from the container.
 @discussion This property contains the array of `PWCMERecordID` objects that identify the records to delete. The initial contents of the array are set to the records you specified in the `initWithRecordsToSave:recordIDsToDelete:` method.
 
 If you intend to change the value of this property, do so before executing the operation or submitting the operation object to a queue.
 
 When deleting records, the operation object reports progress only on the records you specify in this property. Deleting records can trigger the deletion of related records if there is an owner-owned relationship between the records. When additional deletions occur, they are not reported to the progress blocks of this object.
 */
@property (nonatomic, copy) NSArray /* PWCMERecordID */ *recordIDsToDelete;

/**
 The policy to apply when the server contains a newer version of a specific record.
 @discussion The default value is PWCMERecordSaveChangedKeys.
 */
@property (nonatomic, assign) PWCMERecordSavePolicy savePolicy;

/**
 The block to execute when the delete results of a single record are known.
 @discussion The block returns no value and takes the following parameters:
 - recordID: A `PWCMERecordID` object for the record that you attempted to delete.
 - error: An error object containing information about a problem or ``` if the record was saved successfully.
 
 This block is executed once for each record in the `recordIDsToDelete` property. Each time the block is executed, it is executed serially with respect to the other progress blocks of the operation.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue. Use this block to take any actions after the status of saving the record is known.
 */
@property (nonatomic, copy) void (^perRecordIDDeleteCompletionBlock)(PWCMERecordID *recordID, NSError *error);

/**
 The block to execute when the save results of a single record are known.
 @discussion The block returns no value and takes the following parameters:
 - record: A `PWCMERecord` object that you attempted to save.
 - error: An error object containing information about a problem or `nil` if the record was saved successfully.
 
 This block is executed once for each record in the `recordsToSave` property. Each time the block is executed, it is executed serially with respect to the other progress blocks of the operation.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue. Use this block to take any actions after the status of saving the record is known.
 */
@property (nonatomic, copy) void (^perRecordSaveCompletionBlock)(PWCMERecord *record, NSError *error);

/**
 The block to execute after the status of all changes is known.
 @discussion The block returns no value and takes the following parameters:
 - savedRecord: The array of `PWCMERecord` objects you tried to save.
 - deletedRecordIDs: The array of `PWCMERecordID` objects corresponding to the records you tried to delete.
 - operationError: An error object containing information about a problem or `nil` if the results are saved successfully.
 
 This block is executed only once and represents your last chance to process the operation results. It is executed after all individual progress blocks have completed but before the operation’s completion block. The block is executed serially with respect to the other progress blocks of the operation.
 
 If you intend to use this block to process results, set it before executing the operation or submitting the operation object to a queue.
 
 This block reports an error of type `PWCMEErrorPartialFailure` when it saves or deletes only some of the records successfully. The userInfo dictionary of the error contains a `PWCMEPartialErrorsByItemIDKey` key whose value is an NSDictionary object. The keys of that dictionary are the IDs of the records that were not saved or deleted, and the corresponding values are error objects containing information about what happened.
 

 */
@property (nonatomic, copy) void (^modifyRecordsCompletionBlock)(NSArray /* PWCMERecord */ *savedRecords, NSArray /* PWCMERecordID */ *deletedRecordIDs, NSError *operationError);

/**
 Initializes and returns an operation object. 
 @return An initialized operation object.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Initializes and returns an operation object configured to save and delete the specified records.
 @param records An array of `PWCMERecord` objects representing the records to save, if any. You may specify `nil` for this parameter.
 @param recordIDs An array of `PWCMERecordID` objects representing the records you want to delete, if any. You may specify `nil` for this parameter.
 @return An initialized operation object.
 @discussion The records you intend to save or delete must all reside in the same container, which you can specify when you configure the operation object. Saving a record that is not in the current container creates it in the database. Trying to delete a record that does not exist in the current container returns an error for that record.
 */
- (instancetype)initWithRecordsToSave:(NSArray /* PWCMERecord */ *)records recordIDsToDelete:(NSArray /* PWCMERecord */ *)recordIDs;

@end