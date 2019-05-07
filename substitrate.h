#ifndef SUBSTITRATE_H
#define SUBSTITRATE_H

struct substitute_image {
#ifdef __APPLE__
    intptr_t slide;
    void *dlhandle;
    const void *image_header;
#endif
};

#import <dlfcn.h>
#import <substrate.h>
#import "../PS.h"

#define EXPORT __attribute__ ((visibility("default")))

void *PSFindSymbolCallable(MSImageRef image, const char *name) __asm__("PSFindSymbolCallable");
void *PSFindSymbolReadable(MSImageRef image, const char *name) __asm__("PSFindSymbolReadable");
void *PSFindSymbolReadableCompat(const char *image, const char *name) __asm__("PSFindSymbolReadableCompat");
void *PSFindSymbolCallableCompat(const char *image, const char *name) __asm__("PSFindSymbolCallableCompat");

void PSHookFunction(void *symbol, void *replace, void **result) __asm__("PSHookFunction");
void PSHookFunction1(MSImageRef ref, const char *symbol, void *replace, void **result) __asm__("PSHookFunction1");
void PSHookFunction2(MSImageRef ref, const char *symbol, void *replace) __asm__("PSHookFunction2");
void PSHookFunction3(const char *image, const char *symbol, void *replace, void **result) __asm__("PSHookFunction3");
void PSHookFunction4(const char *image, const char *symbol, void *replace) __asm__("PSHookFunction4");

void *PSFindSymbolCompat(void *image, const char *symbol) __asm__("PSFindSymbolCompat");

#define _PSHookFunction(ref, symbol, replace) PSHookFunction1(ref, symbol, (void *)replace, (void **)& _ ## replace)
#define _PSHookFunctionCompat(image, symbol, replace) PSHookFunction3(image, symbol, (void *)replace, (void **)& _ ## replace)

#endif