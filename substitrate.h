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

void *PSFindSymbolCallable(MSImageRef image, const char *name) __asm__("PSFindSymbolCallable");
void *PSFindSymbolReadable(MSImageRef image, const char *name) __asm__("PSFindSymbolReadable");
void *PSFindSymbolReadableCompat(const char *image, const char *name) __asm__("PSFindSymbolReadableCompat");
void *PSFindSymbolCallableCompat(const char *image, const char *name) __asm__("PSFindSymbolCallableCompat");

int PSHookFunction(void *func, void *replace, void **result) __asm__("PSHookFunction");
int PSHookFunction1(MSImageRef ref, const char *symbol, void *replace, void **result) __asm__("PSHookFunction1");
int PSHookFunction2(MSImageRef ref, const char *symbol, void *replace) __asm__("PSHookFunction2");
int PSHookFunction3(const char *image, const char *symbol, void *replace, void **result) __asm__("PSHookFunction3");
int PSHookFunction4(const char *image, const char *symbol, void *replace) __asm__("PSHookFunction4");

void *PSFindSymbolCompat(void *image, const char *symbol) __asm__("PSFindSymbolCompat");

#if TARGET_OS_SIMULATOR

#import "libSubstitrate.mm"

#endif

#define _PSHookFunction(ref, symbol, replace) PSHookFunction1(ref, symbol, (void *)replace, (void **)& _ ## replace)
#define _PSHookFunctionCompat(image, symbol, replace) PSHookFunction3(image, symbol, (void *)replace, (void **)& _ ## replace)

#endif