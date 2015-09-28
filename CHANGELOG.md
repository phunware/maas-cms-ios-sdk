# PWCME Changelog

##2.0.0 BETA 2 (Thursday, February 26th, 2015)
 * Added method to `PWCMEQuery` that allows initialization with a structure ID: `- (instancetype)initWithFieldName:(NSString *)fieldName predicate:(NSPredicate *)predicate parentStructureID:(NSInteger)structureID;`
 * Disabled NSURLCache for all PWCMEOperations
 * Added `fetchAllSchemasOperation` method to `PWCMEFetchSchemasOperation` class.
 * Exposing `NSOperationQueue` associated with a `PWCMEContainer` object.
 * Added `attributes` field to `PWCMESchemaField` object that allows user to access attributes associated with a `PWCMESchemaField`
 * Fixed internal `AFNetworking` dependency which means it should no longer clash with application level dependencies


##2.0.0 BETA (Wednesday, January 14th, 2015)
 * Initial beta release of PWMCE. Native support for queries, records, and much more. Please see the GitHub Wiki for more information.

---

##1.3.0 (Friday, September 25th, 2015)
 * Updating CME to use PWCore v2.0.0
 * Renamed MaaSCMS to PWCME

##1.2.7 (Friday, March 13th, 2014)
 * Fixed issue where `deleteContentForContentID:traverse:success:failure:` would not actually delete the specified CME content.

##1.2.6 (Monday, November 3rd, 2014)
 * Enabled encryption support

##1.2.4 (Monday, May 19th, 2014)
 * Fixed issue with getContent integer parameters being passed as strings instead of numbers

##1.2.2 (Thursday, April 24th, 2014)
 * Adding limit and offset parameters back into getAllContentsForContainerID method.
 * Deprecated current implementation of getAllContentsForContainerID. This method will be removed  in a future release. 

##1.2.1 (Wednesday, March 26th, 2014)
 * Adding arm64 support

##1.1.0 (Monday, January 27th, 2014)
 * Removed tag calls for containers and schema
 * Added limit and offset parameters to getSchemas call

##1.0.1 (Wednesday, August 14th, 2013)
 * Fixed bug get getStructures call would only return the first level of structures instead of the entire structure hierarchy.

##1.0.0 (Wednesday, August 14th, 2013)
 * Initial release. See **README.md** for more information.

##0.9.9 (Friday, August 9th, 2013)
 * Provisional release
