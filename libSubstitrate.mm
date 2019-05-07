#import "substitrate.h"

struct substitute_function_hook {
    void *function;
    void *replacement;
    void *old_ptr;
    int options;
};
struct substitute_function_hook_record;
int (*substitute_hook_functions)(const struct substitute_function_hook *hooks, size_t nhooks, struct substitute_function_hook_record **recordp, int options) = NULL;
void *(*SubFindSymbol)(void *image, const char *name) = NULL;
struct substitute_image *(*substitute_open_image)(const char *filename) = NULL;

static bool didFindSubstitute = false;

static void readDylib() {
    if (!didFindSubstitute) {
        MSImageRef ref = MSGetImageByName("/usr/lib/libsubstitute.dylib");
        if (ref) {
            substitute_hook_functions = (int (*)(const struct substitute_function_hook *, size_t, struct substitute_function_hook_record **, int))PSFindSymbolCallable(ref, "_substitute_hook_functions");
			HBLogDebug(@"substitute_hook_functions exists: %d", substitute_hook_functions != NULL);
            SubFindSymbol = (void *(*)(void *, const char *))_PSFindSymbolCallable(ref, "SubFindSymbol");
			HBLogDebug(@"SubFindSymbol exists: %d", SubFindSymbol != NULL);
			substitute_open_image = (struct substitute_image *(*)(const char *))_PSFindSymbolCallable(ref, "_substitute_open_image");
			HBLogDebug(@"substitute_open_image exists: %d", substitute_open_image != NULL);
        }
        didFindSubstitute = true;
    }
}

EXPORT
void *PSFindSymbolReadable(MSImageRef image, const char *name) {
	return _PSFindSymbolReadable(image, name);
}

EXPORT
void *PSFindSymbolCallable(MSImageRef image, const char *name) {
	return _PSFindSymbolCallable(image, name);
}

EXPORT
void *PSFindSymbolReadableCompat(const char *image, const char *symbol) {
	readDylib();
	if (SubFindSymbol && substitute_open_image) {
		if (image == NULL)
			return make_sym_readable(SubFindSymbol(NULL, symbol));
		dlopen(image, RTLD_LAZY);
		struct substitute_image *im = substitute_open_image(image);
		return make_sym_readable(SubFindSymbol(im, symbol));
	}
	return PSFindSymbolReadable(image ? MSGetImageByName(image) : NULL, symbol);
}

EXPORT
void *PSFindSymbolCallableCompat(const char *image, const char *symbol) {
	readDylib();
	if (SubFindSymbol && substitute_open_image) {
		if (image == NULL)
			return make_sym_callable(SubFindSymbol(NULL, symbol));
		dlopen(image, RTLD_LAZY);
		struct substitute_image *im = substitute_open_image(image);
		return make_sym_callable(SubFindSymbol(im, symbol));
	}
	return PSFindSymbolCallable(image ? MSGetImageByName(image) : NULL, symbol);
}

EXPORT
void PSHookFunction(void *symbol, void *replace, void **result) {
	readDylib();
	if (substitute_hook_functions) {
		struct substitute_function_hook hook = { symbol, replace, result };
#if DEBUG
		HBLogDebug(@"Substitute hook function return value: %d", substitute_hook_functions(&hook, 1, NULL, 1));
#else
		substitute_hook_functions(&hook, 1, NULL, 1);
#endif
	} else
		MSHookFunction(symbol, replace, result);
}

EXPORT
void PSHookFunction1(MSImageRef ref, const char *symbol, void *replace, void **result) {
	PSHookFunction(_PSFindSymbolCallable(ref, symbol), replace, result);
}

EXPORT
void PSHookFunction2(MSImageRef ref, const char *symbol, void *replace) {
	PSHookFunction1(ref, symbol, replace, NULL);
}

EXPORT
void PSHookFunction3(const char *image, const char *symbol, void *replace, void **result) {
	PSHookFunction(PSFindSymbolCallableCompat(image, symbol), replace, result);
}

EXPORT
void PSHookFunction4(const char *image, const char *symbol, void *replace) {
	PSHookFunction3(image, symbol, replace, NULL);
}

int main(int argc, char **argv, char **envp) {
	return 0;
}
