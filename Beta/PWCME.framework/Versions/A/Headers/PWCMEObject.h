//
//  PWCMEObject.h
//  PWCME
//
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

@import Foundation;

/**
 A `PWCMEObject` is the base class for many Phunware CME related objects and contains basic information, such as the creation date and last updated date of a CME object.
 
 `PWCMEObject` is not meant to be subclassed.
 */

@interface PWCMEObject : NSObject <NSSecureCoding, NSCopying>

/**
 The time when the record was first saved to the server. (read-only)
 @discussion The creation date reflects the time at which a record with the current record’s ID was created on the server. For new instances of this class, the value of this property is initially set to `nil`. When you save the record to the server, the value is updated with the appropriate creation date for the record.
 */
@property (nonatomic, readonly) NSDate *creationDate;

/**
 The time when the record was last saved to the server. (read-only)
 @discussion The modification date reflects the time at which a record with the current record’s ID was last saved to the server. For new instances of this class, the value of this property is initially set to `nil`. When you save the record to the server, the value is updated with the appropriate modification date for the record.
 */
@property (nonatomic, readonly) NSDate *modificationDate;

@end
