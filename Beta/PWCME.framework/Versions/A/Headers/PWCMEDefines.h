//
//  PWCMEDefines.h
//  PWCME
// 8/27/14.
//  Copyright (c) 2014 Phunware, Inc. All rights reserved.
//

#ifndef PWCME_EXTERN
#ifdef __cplusplus
#define PWCME_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define PWCME_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif