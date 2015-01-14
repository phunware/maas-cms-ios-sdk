//
//  PWCMEError.h
//  PWCME
// 8/27/14.
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

@import Foundation;
#import <PWCME/PWCMEDefines.h>

/** The domain for PWCME errors. */
PWCME_EXTERN NSString * const PWCMEErrorDomain;

/**
 The key you use to retrieve partial error results. The value of this key is an NSDictionary that maps an item ID object to an error object. The type of each item ID object is dependent on where the partial error occurs. For example, if you receive a partial error when modifying `PWCMERecord` objects, each key is a `PWCMERecordID` object corresponding to a record that was not modified.
 */
PWCME_EXTERN NSString * const PWCMEPartialErrorsByItemIDKey;

/**
 The key you use to retrieve partial error results. The value of this key is an NSDictionary that maps an item object to an error object. The type of each item object is dependent on where the partial error occurs. For example, if you receive a partial error when modifying `PWCMERecord` objects, each key is a `PWCMERecord` object corresponding to a record that was not modified.
 */
PWCME_EXTERN NSString * const PWCMEPartialErrorsByItemKey;

/**
 Error codes that can be returned by Phunware CME.
 */
typedef NS_ENUM(NSInteger, PWCMEErrorCode) {
    /** PWCME.framework encountered an error.  This is a non-recoverable error. */
    PWCMEErrorInternalError             = 1,
    /** The overall operation succeeded but some items failed. */
    PWCMEErrorPartialFailure       = 2,
//    CKErrorNetworkUnavailable      = 3,  /* Network not available */
//    CKErrorNetworkFailure          = 4,  /* Network error (available but CFNetwork gave us an error) */
//    CKErrorBadContainer            = 5,  /* Un-provisioned or unauthorized container. Try provisioning the container before retrying the operation. */
//    CKErrorServiceUnavailable      = 6,  /* Service unavailable */
//    CKErrorRequestRateLimited      = 7,  /* Client is being rate limited */
//    CKErrorMissingEntitlement      = 8,  /* Missing entitlement */
//    CKErrorNotAuthenticated        = 9,  /* Not authenticated (writing without being logged in, no user record) */
//    CKErrorPermissionFailure       = 10, /* Access failure (save or fetch) */
    /** Record does not exist. */
    PWCMEErrorUnknownItem             = 11,
//    CKErrorInvalidArguments        = 12, /* Bad client request (bad record graph, malformed predicate) */
//    CKErrorResultsTruncated        = 13, /* Query results were truncated by the server */
//    CKErrorServerRecordChanged     = 14, /* The record was rejected because the version on the server was different */
//    CKErrorServerRejectedRequest   = 15, /* The server rejected this request.  This is a non-recoverable error */
//    CKErrorAssetFileNotFound       = 16, /* Asset file was not found */
//    CKErrorAssetFileModified       = 17, /* Asset file content was modified while being saved */
//    CKErrorIncompatibleVersion     = 18, /* App version is less than the minimum allowed version */
//    CKErrorConstraintViolation     = 19, /* The server rejected the request because there was a conflict with a unique field. */
//    CKErrorOperationCancelled      = 20, /* A CKOperation was explicitly cancelled */
//    CKErrorChangeTokenExpired      = 21, /* The previousServerChangeToken value is too old and the client must re-sync from scratch */
//    CKErrorBatchRequestFailed      = 22, /* One of the items in this batch operation failed in a zone with atomic updates, so the entire batch was rejected. */
//    CKErrorZoneBusy                = 23, /* The server is too busy to handle this zone operation. Try the operation again in a few seconds. */
//    CKErrorBadDatabase             = 24, /* Operation could not be completed on the given database. Likely caused by attempting to modify zones in the public database. */
//    CKErrorQuotaExceeded           = 25, /* Saving a record would exceed quota */
//    CKErrorZoneNotFound            = 26, /* The specified zone does not exist on the server */
//    CKErrorLimitExceeded           = 27, /* The request to the server was too large. Retry this request as a smaller batch. */
//    CKErrorUserDeletedZone         = 28, /* The user deleted this zone through the settings UI. Your client should either remove its local data or prompt the user before attempting to re-upload any data to this zone. */
};
