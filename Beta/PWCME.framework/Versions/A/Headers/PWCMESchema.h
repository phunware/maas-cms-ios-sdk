//
//  PWCMESchema.h
//  PWCME
// 8/28/14.
//  Copyright (c) 2014 Phunware Inc. All rights reserved.
//

#import <PWCME/PWCMEObject.h>

@class PWCMERecord;

/**
 The schema object defines what content can be associated with a record. You can modify `PWSchema` values in the MaaS portal. `PWSchema` conforms to the `NSCoding` and `NSCopying` protocol.
 */

@interface PWCMESchema : PWCMEObject <NSSecureCoding, NSCopying>

/** 
 The unique string that identifies the app’s container. (read-only)
 @discussion Use the value in this property to distinguish between different container schemas in your app.
 */
@property (nonatomic, readonly) NSString *schemaIdentifier;

/** The human-readable description of the schema. (read-only) */
@property (nonatomic, readonly) NSString *schemaDescription;

/** The name of the container. (read-only) */
@property (nonatomic, readonly) NSString *name;

/** An array of `PWSchemaField` objects associated with the schema. */
@property (nonatomic, readonly) NSArray *fields;

/** An array of attributes associated with the schema. */
@property (nonatomic, readonly) NSDictionary *attributes;

@end
