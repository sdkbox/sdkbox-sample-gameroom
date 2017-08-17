#ifndef FBG_PLATFORMVERSION_H
#define FBG_PLATFORMVERSION_H

// Conventional string-ification macro.
#if !defined(FBG_STRINGIZE)
#define FBG_STRINGIZEIMPL(x) #x
#define FBG_STRINGIZE(x)     FBG_STRINGIZEIMPL(x)
#endif

// Master version numbers
#define PLATFORM_PRODUCT_VERSION 0 // Product version doesn't participate in semantic versioning.
#define PLATFORM_MAJOR_VERSION   0 // If you change these values then you need to also make sure to change LibFBGPlatform.props in parallel.
#define PLATFORM_MINOR_VERSION   3
#define PLATFORM_PATCH_VERSION   0
#define PLATFORM_BUILD_NUMBER    0
#define PLATFORM_DRIVER_VERSION  0
// "Major.Minor.Patch.Build"
#if !defined(PLATFORM_VERSION_STRING)
#define PLATFORM_VERSION_STRING FBG_STRINGIZE(PLATFORM_MAJOR_VERSION.PLATFORM_MINOR_VERSION.PLATFORM_PATCH_VERSION.PLATFORM_BUILD_NUMBER)
#endif

// This appears in the user-visible file properties.  TeamCity builds will stamp PLATFORM_DESCRIPTION_STRING.
#if !defined(PLATFORM_DESCRIPTION_STRING)
#if defined(_DEBUG)
#define PLATFORM_DESCRIPTION_STRING "dev build debug"
#else
#define PLATFORM_DESCRIPTION_STRING "dev build"
#endif
#endif

#if !defined(FBG_JOIN)
#define FBG_JOIN(a, b)  FBG_JOIN1(a, b)
#define FBG_JOIN1(a, b) FBG_JOIN2(a, b)
#define FBG_JOIN2(a, b) a##b
#endif

#endif
