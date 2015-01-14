//
//  PWCMESchemaFieldTypes.h
//  PWCME
//
//  Copyright (c) 2014 Phunware Inc. All rights reserved.
//

/**
 Constants indicating the different field types supported by a schema.
 */

typedef NS_ENUM(NSInteger, PWCMESchemaFieldType) {
    /** The field type is unknown. */
    PWCMESchemaFieldTypeUnknown = NSNotFound,
    /** A single-line text input. If the value is meant to be an ID from a MongoDB store, use the "objectId" type instead. */
    PWCMESchemaFieldTypeTextSingle = 0,
    /** A multi-line text input. */
    PWCMESchemaFieldTypeTextMulti,
    /** A single-line HTML input. */
    PWCMESchemaFieldTypeHTMLSingle,
    /** A multi-line HTML input. */
    PWCMESchemaFieldTypeHTMLMulti,
    /** A single-select drop-down. */
    PWCMESchemaFieldTypeSelectSingle,
    /** A multi-select drop-down. */
    PWCMESchemaFieldTypeSelectMulti,
    /** A `BOOL` value. Value must be `YES or `NO`. */
    PWCMESchemaFieldTypeBoolean,
    /** A date (without time). Value must be a valid date formatted as RFC 3339. */
    PWCMESchemaFieldTypeDate,
    /**  A time (without date). Value must be the number of seconds since midnight UTC, with midnight being 0 and the max value being 86400. For instance, if the time should be set to 1:05:25am, the value would be 3925. */
    PWCMESchemaFieldTypeTime,
    /** A date and time. Value must be a valid date formatted as RFC 3339.*/
    PWCMESchemaFieldTypeDateTime,
    /** An uploaded file. */
    PWCMESchemaFieldTypeFile,
    /** A numeric value. This includes integers or decimals. */
    PWCMESchemaFieldTypeNumber,
    /** An integer (whole number). */
    PWCMESchemaFieldTypeInteger,
    /** A decimal (floating point) number. */
    PWCMESchemaFieldTypeDecimal,
    /** A 24-byte hex string. */
    PWCMESchemaFieldTypeObjectID
};