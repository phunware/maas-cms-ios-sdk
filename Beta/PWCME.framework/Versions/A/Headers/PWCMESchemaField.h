//
//  PWCMESchemaField.h
//  PWCME
// 9/22/14.
//  Copyright (c) 2014 Phunware Inc. All rights reserved.
//

#import <PWCME/PWCMEObject.h>
#import <PWCME/PWCMESchemaFieldTypes.h>

/**
 `PWSchemaField` objects define the fields that are specified for a `PWSchema` object. A `PWSchemaField` object has a few base parameters and can be extended to support additional key-value pairs. Additional key-value pairs are available in the `customKeys` property. You can modify `PWSchemaField` values in the Phunware portal. `PWSchemaField` conforms to the `NSCoding` and `NSCopying` protocol.
 */

@interface PWCMESchemaField : PWCMEObject <NSSecureCoding, NSCopying>

/** A string describing the field key. */
@property (nonatomic, readonly) NSString *field;

/** A string describing the field label. */
@property (nonatomic, readonly) NSString *label;

/** A string describing the field type. */
@property (nonatomic, readonly) PWCMESchemaFieldType type;

/** A `BOOL` value that indicates whether or not this field is required. */
@property (nonatomic, readonly) BOOL required;

/** A string describing the field. */
@property (nonatomic, readonly) NSString *fieldDescription;

@end
