#ifndef SUBSTITRATE_H
#define SUBSTITRATE_H

struct substitute_image {
#ifdef __APPLE__
    intptr_t slide;
    void *dlhandle;
    const void *image_header;
#endif
};

struct substitute_function_hook {
    void *function;
    void *replacement;
    void *old_ptr;
    int options;
};
struct substitute_function_hook_record;

#import <dlfcn.h>
#import <substrate.h>
#import "../PS.h"

#define EXPORT __attribute__ ((visibility("default")))

EXPORT void *PSFindSymbolCallable(MSImageRef image, const char *name) __asm__("PSFindSymbolCallable");
EXPORT void *PSFindSymbolReadable(MSImageRef image, const char *name) __asm__("PSFindSymbolReadable");
EXPORT void *PSFindSymbolReadableCompat(const char *image, const char *name) __asm__("PSFindSymbolReadableCompat");
EXPORT void *PSFindSymbolCallableCompat(const char *image, const char *name) __asm__("PSFindSymbolCallableCompat");

EXPORT int PSHookFunction(void *func, void *replace, void **result) __asm__("PSHookFunction");
EXPORT int PSHookFunction1(MSImageRef ref, const char *symbol, void *replace, void **result) __asm__("PSHookFunction1");
EXPORT int PSHookFunction2(MSImageRef ref, const char *symbol, void *replace) __asm__("PSHookFunction2");
EXPORT int PSHookFunction3(const char *image, const char *symbol, void *replace, void **result) __asm__("PSHookFunction3");
EXPORT int PSHookFunction4(const char *image, const char *symbol, void *replace) __asm__("PSHookFunction4");

EXPORT void *PSFindSymbolCompat(void *image, const char *symbol) __asm__("PSFindSymbolCompat");

#define _PSHookFunction(ref, symbol, replace) PSHookFunction1(ref, symbol, (void *)replace, (void **)& _ ## replace)
#define _PSHookFunctionCompat(image, symbol, replace) PSHookFunction3(image, symbol, (void *)replace, (void **)& _ ## replace)

#endif