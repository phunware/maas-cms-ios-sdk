//
//  PWCMEQuery.h
//  PWCME
//
//  Copyright (c) 2014 Phunware Inc. All rights reserved.
//

@import Foundation;

/**
 A `PWCMEQueryCursor` object is an opaque data object that marks the stopping point for a query and the starting point for retrieving the remaining results. You do not create instances of this class yourself. When fetching records using a `PWCMEQueryOperation` object, if the number of results exceeds the results limit value set for the query, the server will provide you with a query cursor object. Use that cursor object to initialize a new `PWCMEQueryOperation` and retrieve the next batch of results for the same query.
 
 For information about how to use a `PWCMEQueryCursor` object, see `PWCMEQueryOperation` Class Reference.
 */
@interface PWCMEQueryCursor : NSObject <NSCopying, NSSecureCoding>
/** NOTE: The standard initializer is not available. */
- (instancetype)init NS_UNAVAILABLE;
@end

@class PWCMEContainer;

/**
 A `PWCMEQuery` object manages the criteria to apply when searching for records in a container. You create a query object as the first step in the search process. The query object stores the search parameters, including the type of records to search, the match criteria (predicate) to apply and the sort parameters to apply to the results. The second step is to use the query object to initialize a `PWCMEQueryOperation` object, which you then execute to generate the results.
 
 Always designate a record type and predicate when you create a query object. The record type narrows the scope of the search to one type of record and the predicate defines the conditions for which records of that type are considered a match. Predicates usually compare one or more fields of a record to constant values, but you can create predicates that return all records of a given type or perform more nuanced searches.
 
 Because the record type and predicate cannot be changed later, you can use the same `PWCMEQuery` object to initialize multiple `PWCMEQueryOperation` objects, each of which targets a different container.
 */
@interface PWCMEQuery : NSObject

/**
 Declares which user-defined keys should be fetched and added to the resulting PWCMERecords. If set to `nil` (the default), declares the entire record should be downloaded. If set to an empty array, declares that no user fields should be downloaded.
 */
@property (nonatomic, copy) NSArray /* NSString */ *desiredKeys;

/**
 The record type to search. (read-only)
 @discussion Searches return only records of the specified field name. This property is set at initialization time and cannot be changed later.
 
 The record type is an app-specific string that you use to distinguish among the records of your app. The records of a given type all represent different instances of the same information. For example, an employee record type might store the employee’s name, phone number and a reference to the employee’s manager.
 */
@property (nonatomic, readonly, copy) NSString *fieldName;

/**
 The search criteria to use when matching records. (read-only).
 
 @discussion  `predicate` contains one or more expressions that evaluate to true or false. Expressions are often value-based comparisons, but predicates support other types of operators, including string comparisons and aggregate operations. For guidelines on how to construct predicates for your queries, see `Constructing a Predicate for a Query` in the Phunware documentation.
 
 This property is set at initialization time and cannot be changed later.
 */
@property (nonatomic, readonly, copy) NSPredicate *predicate;

/**
 The sort descriptors to use when organizing the query results.
 
 @discussion This property contains an array of NSSortDescriptor objects. You can add sort descriptors to a query object and change them later as needed. Each sort descriptor contains a field name of the intended record type and information about whether to sort values in that field in ascending or descending order. The default value of this property is `nil`, which means that records are returned in an indeterminate order.
 
 The order of the items in the array matches the order in which the sort descriptors are applied to the results. In other words, the first sort descriptor in the array is applied first, followed by the second sort descriptor if needed then the third (and so on).
 */
@property (nonatomic, copy) NSArray /* NSSortDescriptor */ *sortDescriptors;

/**
 Initializes and returns a query object with the specified parameters.
 @param fieldName The type of record to search. Specify the name of one of your app’s supported record types.
 
 This method throws an exception if this parameter is `nil`.
 @param predicate The search predicate to apply to the prospective records. Only records matching the predicate criteria are returned in the search results. This parameter can be `nil` if you wish to fetch all records for the specified field.
 @return An initialized query object.
 @discussion You cannot change the record type and predicate of a query object after you create it. If you want to search for a different set of records using a different set of search criteria, create a new query object. You can add sort descriptors to the query and change them later as needed. Note that this method ONLY works when querying against fields which reside at the root level of a container.
 */
- (instancetype)initWithFieldName:(NSString *)fieldName predicate:(NSPredicate *)predicate NS_DESIGNATED_INITIALIZER;

/**
 Initializes and returns a query object with the specified parameters. This method should be used when trying to query fields that don't exist at the root level of container.
 @param fieldName The type of record to search. Specify the name of one of your app’s supported record types.
 
 This method throws an exception if this parameter is `nil`.
 @param predicate The search predicate to apply to the prospective records. Only records matching the predicate criteria are returned in the search results. This parameter can be `nil` if you wish to fetch all records for the specified field.
 @param structureID The parent structure identifier that you wish to query against.
 @return An initialized query object.
 @discussion You cannot change the record type and predicate of a query object after you create it. If you want to search for a different set of records using a different set of search criteria, create a new query object. You can add sort descriptors to the query and change them later as needed.
 */
- (instancetype)initWithFieldName:(NSString *)fieldName predicate:(NSPredicate *)predicate parentStructureID:(NSInteger)structureID;

@end
