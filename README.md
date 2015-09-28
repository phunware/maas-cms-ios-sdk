Phunware Content Management SDK for iOS
================

Version 1.3.0

This is Phunware's iOS SDK for the Content Management module. Visit http://maas.phunware.com/ for more details and to sign up.


Requirements
------------

- PWCore v2.0.0 or greater
- iOS 7.0 or greater
- Xcode 6 or greater



Getting Started
---------------

- [Download Phunware Content Management](https://github.com/phunware/maas-content-management-ios-sdk/archive/master.zip) and run the included sample app.
- Continue reading below for installation and integration instructions.
- Be sure to read the [documentation](http://phunware.github.io/maas-content-management-ios-sdk/) for additional details.



Installation
------------

The following frameworks are required:
````
PWCore.framework
````

Phunware Content Management has a dependency on PWCore.framework, which is available here: https://github.com/phunware/maas-core-ios-sdk

It's recommended that you add the MaaS frameworks to the 'Vendor/Phunware' directory. This directory should contain PWCore.framework and PWCME.framework  as well as any other MaaS frameworks that you are using.



Documentation
------------

Documentation is included in the Documents folder in the repository as both HTML and as a .docset. You can also find the latest documentation here: http://phunware.github.io/maas-content-management-ios-sdk/



Overview
-----------

The Phunware Content Management SDK allows developers to fetch and manage the various pieces of data in the Content Management module, including containers, schemas, structure and content. Content Management spans across your entire organization, so different applications can potentially share the same content.


### Container

**Containers** hold a single structure. You can create any number of containers in the Phunware portal. You can also associate tags with containers to assist with fetching.

### Schema

**Schemas** are applied to **structure** items and define what fields of data a particular structure item can contain. You can create any number of schemas in the Phunware portal. You can also associate tags with schemas to assist with fetching.

### Structure

**Structure** items are used to build the structure and hierarchy of the data. Each **structure** item that is defined as an object can also optionally be assigned a **schema** that defines what content can be saved to **structure** items.

### Content

The structure of the **content** object relies completely on the structure of the menus and schemas.



Integration
-----------

The primary methods in Content Management revolve fetching, creating, updating and deleting content. You can also GET structures, containers and schemas.

### Getting Content

````objective-c
	// Get a specific piece of content for the specified content ID, container ID and structure ID. The contents are always returned as an NSDictionary object. It's recommended that you parse the dictionary into a model object.
    [PWCME getContentForContentID:@"CONTENT_ID" containerID:@"CONTAINER_ID" structureID:123 success:^(NSDictionary *content) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Updating Content

````objective-c
	// Update content for the specified content ID, container ID and structure ID. Any omitted fields will maintain their previous values.
    NSDictionary *updatedContent = @{@"user_name" : @"MaaS Test User"};
    
    [PWCME updateContentForContentID:@"CONTENT_ID" containerID:@"CONTAINER_ID" structureID:123 updatedContent:updatedContent success:^{
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Creating Content

````objective-c
	// Add content to the specified container ID, structure ID and parent content ID. Ideally, the new content dictionary has all the fields as specified by the structure and schema. If not, the required fields will be created for you with empty values.
    NSDictionary *newContent = @{@"user_name" : @"MaaS Test User"};
    
    [PWCME addContent:newContent containerID:@"CONTAINER_ID" structureID:123 parentContentID:@"PARENT_CONTENT_ID" success:^(NSString *newContentID) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Deleting Content

````objective-c
	// Delete content for the specified content ID, as well as all content children.
    [PWCME deleteContentForContentID:@"CONTENT_ID" traverse:YES success:^{
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Delete all content children for the specified content ID.
    [PWCME deleteContentChildrenForContentID:@"CONTENT_ID" success:^{
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Containers

````objective-c
	// Fetch all containers.
    [PWCME getAllContainersWithSuccess:^(NSArray *containers) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Fetch a specific container item.
    [PWCME getContainerWithContainerID:@"CONTAINER_ID" success:^(PWContainer *container) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Get an array of containers that match an array of tags.
    [PWCME getContainersContainingAnyTags:@[@"CONTAINER_TAG"] containingAllTags:nil success:^(NSArray *containers) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Schemas

````objective-c
	// Fetch all schemas.
    [PWCME getAllSchemasWithSuccess:^(NSArray *schemas) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Fetch a specific schema item.
    [PWCME getSchemaWithSchemaID:@"SCHEMA_ID" success:^(PWSchema *schema) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Get an array of schemas with the specificed pagination parameters
    [PWCME getSchemasWithLimit:10 offset:0 success:^(NSArray *schemas, PWPagination *pagination, BOOL pagingEnabled) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Structure

````objective-c
	// Fetch a specific structure item with the specified stucture and container ID. In this example, we want to traverse into all child structures and exclude schemata.
    [PWCME getStructureWithID:123 containerID:@"CONTAINER_ID" depth:kPWCMEDepthFullHierarchy includeSchema:NO success:^(PWStructure *structure) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Get an array of structures for the specified container ID. In this example, we want to traverse into all child structures and include schemata.
    [PWCME getStructuresForContainerID:@"CONTAINER_ID" depth:kPWCMEDepthFullHierarchy includeSchema:YES success:^(NSArray *structures) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````
