//
//  PWCMEStructure.h
//  PWCME2
// 8/28/14.
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

#import <PWCME/PWCMEObject.h>

@class PWCMESchema;

/**
 This enum indicates the type of structure.
 */

typedef NS_ENUM(NSInteger, PWCMEStructureType) {
    /** The structure is unknown. */
    PWCMEStructureTypeUnknown = -1,
    /** The structure is an object. */
    PWCMEStructureTypeObject,
    /** The structure an array and holds other structures and/or objects. */
    PWCMEStructureTypeArray
};

/**
 `PWCMEStructure` items are used to build the structure and hierarchy of the data. Each structure item that is defined as an object can also optionally be assigned a schema that defines what content can be saved to those structure items. All values in a `PWCMEStructure` object are immutable on the client. You can modify `PWCMEStructure` values in the MaaS portal. `PWCMEStructure` conforms to the `NSCoding` and `NSCopying` protocol.
 */

@interface PWCMEStructure : PWCMEObject <NSSecureCoding, NSCopying>

/** An integer that is used to identify the structure identifier. */
@property (nonatomic, readonly) NSUInteger structureIdentifier;

/** An integer that is used to identify the parent identifier. */
@property (nonatomic, readonly) NSUInteger parentIdentifier;

/** A string used to identify the container identifier. */
@property (nonatomic, readonly) NSString *containerIdentifier;

/** A string used to identify the schema identifier. */
@property (nonatomic, readonly) NSString *schemaIdentifier;

/** A string used to identify the structure name. */
@property (nonatomic, readonly) NSString *name;

/** The type of structure. */
@property (nonatomic, readonly) PWCMEStructureType type;

/** A string used to identify the structure field. */
@property (nonatomic, readonly) NSString *field;

/** A string used to identify the structure name. */
@property (nonatomic, readonly) NSString *structureDescription;

/** An `NSComparisonResults` that is used to identify the structure sort order. */
@property (nonatomic, readonly) NSComparisonResult sortOrder;

/** An `BOOL` used to identify whether the structure is active. */
@property (nonatomic, readonly, getter=isActive) BOOL active;

/** The `PWCMESchema` object associated with the current structure, if one exists. */
@property (nonatomic, readonly) PWCMESchema *schema;

/** Depending on the API method, child `PWStructure` items may be return as well. */
@property (nonatomic, readonly) NSArray *children;

@end
