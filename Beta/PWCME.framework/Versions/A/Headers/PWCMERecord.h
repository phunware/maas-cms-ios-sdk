//
//  PWCMERecord.h
//  PWCME2
//
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

@import Foundation;
#import <PWCME/PWCMEObject.h>

@class PWCMERecordID, PWCMESchema;

/**
 The `PWCMERecordValue` protocol provides strong type checking for objects that the Phunware CME framework stores on the server. Do not adopt this protocol in your custom classes. Phunware CME does not support writing custom data types to the server. Attempting to do so results in an error.
 */
@protocol PWCMERecordValue <NSObject>
@end

/**
 A `PWCMERecord` object is a dictionary of key-value pairs that you use to fetch and save the data of your app. Records are the fundamental objects you use to manage data in Phunware CME. You may define any number of record types for your app, with each record type corresponding to a different type of information you need. Within a given record type, you then define one or more fields, with a name and a data value. Records can contain simple data types such as strings and numbers or more complex types such as pointers to other records.
 
 An important step in using Phunware CME is defining the record types your app supports. Initially, each new record object contains no keys or values. This must be done through the Phunware portal.
 */

@interface PWCMERecord : PWCMEObject <NSSecureCoding, NSCopying>

/** 
 The unique ID of the record. (read-only)
 @discussion The ID of a new record is always set at initialization time. If you use the initWithRecordID: method to initialize the record, the ID is derived from the PWCMERecordID object you provide. The ID of a record never changes over the lifetime of that record.
 
 When you save a new record object to the server, the server validates the uniqueness of the record but reports an error only if the save policy calls for it. Specifically, it reports an error when the save policy is set to `PWCMERecordSaveIfServerRecordUnchanged`, which is the default. For other save policies, the server overwrites the contents of the existing record accordingly.
 */
@property (nonatomic, readonly, copy) PWCMERecordID *recordID;

/** The identifier of the schema associated with the record. */
@property (nonatomic, readonly) NSString *schemaID;

///----------------------------
/// @name Initializing A Record
///----------------------------

/** NOTE: The standard initializer is not available. */
- (instancetype)init NS_UNAVAILABLE;

/** 
 Initializes and returns a new record of the specified type.
 @param recordID The record identifier associated with the new record.
 
 @discussion This initializer should only be used for creating new CME content locally.
 */
- (instancetype)initWithRecordID:(PWCMERecordID *)recordID;

/*
 In addition to objectForKey: and setObject:forKey:, dictionary-style subscripting (record[key] and record[key] = value) can be used to get and set values.
 Acceptable value object classes are:
 NSData
 NSURL
 NSDate
 NSNumber
 NSString
 NSArray containing objects of any of the types above
 
 Any other classes will result in an exception with name NSInvalidArgumentException.
 
 The following keys are reserved for system use:
 id
 structureId
 schemaId
 createdAt
 updatedAt
 ancestors
 parentId
 
 Key names roughly match C variable name restrictions. They must begin with an ASCII letter and can contain ASCII
 letters and numbers and the underscore character.
 The maximum key length is 255 characters.
 */

///------------------------------------
/// @name Accessing the Record's Fields
///------------------------------------

/**
 Returns the value for the given key stored in the record.
 @param key The string that identifies a field in the record. Key names consist of one or more alphanumeric characters and start with a letter. You may also include underscore characters if you do not use an underscore as the first character in the name. Spaces are not allowed in key names.
 @return The object associated with the specified key or `nil` if no such key exists in the record.
 
 @discussion New records do not contain any keys or values initially.
 */
- (id)objectForKey:(NSString *)key;

/**
  Adds the specified key-value pair to the record.
 @param object The value to assign to the specified key. The object must belong to the `PWCMERecordValue` protocol. It is a programmer error to specify an object of any other type. Specify `nil` for this parameter to remove the value for the field.
 @param key The key to associate with the object. Use this key to retrieve the value later. Key names consist of one or more alphanumeric characters and start with a letter. You may also include underscore characters if you do not use an underscore as the first character in the name. Spaces are not allowed in key names. The names of your keys must not match the names of any properties of this class.
 
 @discussion If the specified key already exists in the record, its old value is deleted and replaced with the one in the object parameter. This change affects only the local copy of the record. You must save the record to the server again before the change becomes available to other clients.
 
 If the type of the object parameter differs from the type of the object currently saved on the server, you will encounter an error when you attempt to save this record to the server. For example, if the current value is an `NSString` object, you will get an error if you change the value to an `NSNumber` object and save the record. */
- (void)setObject:(id <PWCMERecordValue>)object forKey:(NSString *)key;

/** 
 Returns the value for the given key stored in the record.
 @param key The string that identifies a field in the record. Key names consist of one or more alphanumeric characters and start with a letter. You may also include underscore characters but cannot use an underscore as the first character in the name. Spaces are not allowed in key names.
 @return The value associated with the specified key or `nil` if no such key exists in the record.
 
 @discussion Do not call this method directly. The presence of this method is required to support subscripting syntax for record objects. 
 */
- (id)objectForKeyedSubscript:(NSString *)key;

/**
 Adds the specified key-value pair to the record.
 @param object The value to assign to the specified key. The object must belong to the `PWCMERecordValue` protocol. It is a programmer error to specify an object of any other type. Specify `nil` for this parameter to remove the value for the field.
 @param key The key to associate with the object. Use this key to retrieve the value later. Key names consist of one or more alphanumeric characters and start with a letter. You may also include underscore characters but cannot use an underscore as the first character in the name. Spaces are not allowed in key names. The names of your keys must not match the names of any properties of this class.
 @discussion Do not call this method directly. The presence of this method is required to support subscripting syntax for record objects. 
 */
- (void)setObject:(id <PWCMERecordValue>)object forKeyedSubscript:(NSString *)key;

/**
 Returns an array of strings corresponding to all keys currently in the record.
 @return An array of `NSString` objects. The returned array contains only the keys that have corresponding values in the record. If no keys are set for the record, this method returns an empty array.
 
 @discussion This method may not return all possible keys in the record. Specifically, the method does not return keys whose values are `nil`. 
 */
- (NSArray /* NSString */ *)allKeys;

/** 
 Returns an array of strings representing the keys that have changed recently.
 @return An array of NSString objects, each of which represents a key whose value has changed since the record was downloaded or saved. If no keys have changed, this method returns an empty array. 
 */
- (NSArray /* NSString */ *)changedKeys;

@end

@interface NSString (PWCMERecordValue) <PWCMERecordValue>
@end

@interface NSNumber (PWCMERecordValue) <PWCMERecordValue>
@end

@interface NSArray (PWCMERecordValue) <PWCMERecordValue>
@end

@interface NSDate (PWCMERecordValue) <PWCMERecordValue>
@end

@interface NSData (PWCMERecordValue) <PWCMERecordValue>
@end

@interface NSURL (PWCMERecordValue) <PWCMERecordValue>
@end