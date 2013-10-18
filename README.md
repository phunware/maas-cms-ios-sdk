MaaSCMS iOS SDK
================

Version 1.0.1

This is the iOS SDK for the MaaS Content Management System module. Visit http://maas.phunware.com/ for more details and to sign up.



Getting Started
---------------

- [Download MaaSCMS](https://github.com/phunware/maas-cms-ios-sdk/archive/master.zip) and run the included sample app.
- Continue reading below for installation and integration instructions.
- Be sure to read the [documentation](http://phunware.github.io/maas-cms-ios-sdk/) for additional details.



Installation
------------

The following frameworks are required:
````
MaaSCore.framework
````

MaaSCMS has a dependency on MaaSCore.framework which is available here: https://github.com/phunware/maas-core-ios-sdk

It's recommended that you add the MaaS framesworks to the 'Vendor/Phunware' directory. This directory should contain MaaSCore.framework and MaaSCMS.framework  as well as any other MaaS frameworks that you are using.



Documentation
------------

Documentation is included in the Documents folder in the repository as both HTML and .docset. You can also find the latest documentation here: http://phunware.github.io/maas-cms-ios-sdk/.



Overview
-----------

The MaaSCMS SDK allows developers to fetch and manage the various pieces of data in the Content Management System including containers, schemas, structure, and content. The CMS spans across your entire organization so different applications can potentially share the same content.


### Container

**Containers** hold a single structure. You can create any number of containers in MaaS Portal. You can also associate tags with containers to assist with fetching.

### Schema

**Schemas** are applied to **Structure** items and define what fields of data a particular structure item can contain.. You can create any number of schemas in MaaS Portal. You can also associate tags with schemas to assist with fetching.

### Structure

**Structure** items are used to build the structure and hierarchy of the data. Each **Structure** item that is defined as an object can also optionally be assigned a **Schema** that defines what content can be saved to those **Structure** items

### Content

The structure of the **Content** object relies completely on the structure of the menus and schemas.



Integration
-----------

The primary methods in MaaSCMS revolve fetching, creating, updating, and deleting content. You can also get structures, containers, and schemas.

### Getting Content

````objective-c
	// Get a specific piece of content for the specified content ID, container ID, and structure ID. The contents are always returned as an NSDictionary object. It's recommended that you parse the dictionary into a model object.
    [MaaSCMS getContentForContentID:@"CONTENT_ID" containerID:@"CONTAINER_ID" structureID:123 success:^(NSDictionary *content) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Updating Content

````objective-c
	// Update content for the specified content ID, container ID, and structure ID. Any fields that are ommitted will maintain their previous values.
    NSDictionary *updatedContent = @{@"user_name" : @"MaaS Test User"};
    
    [MaaSCMS updateContentForContentID:@"CONTENT_ID" containerID:@"CONTAINER_ID" structureID:123 updatedContent:updatedContent success:^{
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Creating Content

````objective-c
	// Add content to the specified container ID, structure ID, and parent content ID. Ideally the new content dictionary has all the fields as specified by the structure and schema. If not, the required fields will be created for you with empty values.
    NSDictionary *newContent = @{@"user_name" : @"MaaS Test User"};
    
    [MaaSCMS addContent:newContent containerID:@"CONTAINER_ID" structureID:123 parentContentID:@"PARENT_CONTENT_ID" success:^(NSString *newContentID) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Deleting Content

````objective-c
	// Delete content for the specified content ID as well as all content children
    [MaaSCMS deleteContentForContentID:@"CONTENT_ID" traverse:YES success:^{
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Delete all content children for the specified content ID
    [MaaSCMS deleteContentChildrenForContentID:@"CONTENT_ID" success:^{
        ...
    } failure:^(NSError *error) {
        ...
    }];

````

### Containers

````objective-c
	// Fetch all containers
    [MaaSCMS getAllContainersWithSuccess:^(NSArray *containers) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Fetch a specific container item
    [MaaSCMS getContainerWithContainerID:@"CONTAINER_ID" success:^(PWContainer *container) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Get an array of containers that match an array of tags
    [MaaSCMS getContainersContainingAnyTags:@[@"CONTAINER_TAG"] containingAllTags:nil success:^(NSArray *containers) {
        ...
    } failure:^(NSError *error) {
        ...
    }];

````

### Schemas

````objective-c
	// Fetch all schemas
    [MaaSCMS getAllSchemasWithSuccess:^(NSArray *schemas) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Fetch a specific schema item
    [MaaSCMS getSchemaWithSchemaID:@"SCHEMA_ID" success:^(PWSchema *schema) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Get an array of schemas that match an array of tags
    [MaaSCMS getSchemasContainingAnyTags:@[@"SCHEMA_TAG"] containingAllTags:nil success:^(NSArray *schemas) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````

### Structure

````objective-c
	// Get a structure with the specified stucture and container ID. In this example we want to traverse into all child structures but not include schema.
    [MaaSCMS getStructureWithID:123 containerID:@"CONTAINER_ID" depth:kMaaSCMSDepthFullHierarchy includeSchema:NO success:^(PWStructure *structure) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
    
    // Get an array of structures for the specified container ID. In this example we want to traverse into all child structures and include schema.
    [MaaSCMS getStructuresForContainerID:@"CONTAINER_ID" depth:kMaaSCMSDepthFullHierarchy includeSchema:YES success:^(NSArray *structures) {
        ...
    } failure:^(NSError *error) {
        ...
    }];
````



Requirements
------------

- MaaSCore v1.0.0 or greater.
- iOS 5.0 or greater
- Xcode 4.4 or greater