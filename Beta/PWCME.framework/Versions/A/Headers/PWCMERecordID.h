//
//  PWCMERecordID.h
//  PWCME2
//
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

@import Foundation;

/**
 A `PWCMERecordID` object uniquely identifies a record in a container. Record ID objects are normally created automatically when you create a new record, but you might also create IDs in several specific situations. For example, you must create record ID objects when you want to create a new a record locally. You can also create record ID objects when you want to retrieve records with known IDs from a container.
 
 A record ID object consists of a record identifier string, an optional parent record identifier and a structure identifier. For automatically created records, the ID name string is based on a UUID and is therefore guaranteed to be unique.
 
 This class is not intended to be subclassed.
 */

@interface PWCMERecordID : NSObject <NSSecureCoding, NSCopying>

/** The unique identifier of the record. (read-only) */
@property (nonatomic, readonly) NSString *recordIdentifier;

/** The unique identifier of the parent record.
 @discussion This property may be `nil` if no parent exists. */
@property (nonatomic, readonly) NSString *parentRecordIdentifier;

/** The structure identifier of the record. */
@property (nonatomic, readonly) NSInteger structureIdentifier;

///-------------------------------
/// @name Initializing A Record ID
///-------------------------------

/** NOTE: The standard initializer is not available. */
- (instancetype)init NS_UNAVAILABLE;

///-------------------------------
/// @name Initializing A Record ID
///-------------------------------

/** 
 Initializes a record identifier with the specified parameters.
 @param recordIdentifier The record identifier.
 @param structureIdentifier The structure identifier for the record.
 @return An initialized record ID object or `nil` if the object cannot be created.
 @discussion This initializer should be used when you want to fetch an existing record.
 */
- (instancetype)initWithRecordIdentifier:(NSString *)recordIdentifier structureIdentifier:(NSInteger)structureIdentifier;

/** 
 Initializes a record identifier with the specified parameters.
 @param structureIdentifier The structure identifier for the record.
 @param parentRecordIdentifier The parent identifier for the record. This property may be `nil` if the record does not have a parent.
 @return An initialized record ID object or `nil` if the object cannot be created.
 @discussion This initializer should be used when you want to fetch an existing record. 
 */
- (instancetype)initWithParentRecordIdentifier:(NSString *)parentRecordIdentifier structureIdentifier:(NSInteger)structureIdentifier;

/**
 Initializes a record identifier with the specified parameters.
 @param recordIdentifier The record identifier.
 @param structureIdentifier The structure identifier for the record.
 @param parentRecordIdentifier The parent identifier for the record. This property may be `nil` if the record does not have a parent.
 @return An initialized record ID object or `nil` if the object cannot be created.
 @discussion This initializer should be used to fetch an existing record.
 */
- (instancetype)initWithRecordIdentifier:(NSString *)recordIdentifier parentRecordIdentifier:(NSString *)parentRecordIdentifier structureIdentifier:(NSInteger)structureIdentifier NS_DESIGNATED_INITIALIZER;

/** 
 Initializes a record identifier for a locally created record.
 @param structureIdentifier The structure identifier for the record.
 @param parentIdentifier The parent identifier for the record. This property may be `nil` if the record does not have a parent.
 @return An initialized record ID object or `nil` if the object cannot be created.
 @discussion You should only use the initializer for locally created records. A `recordIdentifier` will automatically be assigned once the record has been saved.
 */
- (instancetype)initWithStructureID:(NSInteger)structureIdentifier parentIdentifier:(NSString *)parentIdentifier;



@end
