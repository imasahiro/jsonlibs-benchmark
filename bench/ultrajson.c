#include "../ultrajson/lib/ultrajson.h"
#undef FASTCALL_ATTR
#define FASTCALL_ATTR
#include "../ultrajson/lib/ultrajsondec.c"
#include "../ultrajson/lib/ultrajsonenc.c"
#include "bench.h"

static void *ultrajson_bench_context_new()
{
    return NULL;
}

static void  ultrajson_bench_context_delete(void *context)
{
}

static int ultrajson_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    return 0;
}

static void ultrajson_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
}

static unsigned dummy = 0;
static void Object_objectAddKey(JSOBJ obj, JSOBJ name, JSOBJ value) {}
static void Object_arrayAddItem(JSOBJ obj, JSOBJ value) {}
static JSOBJ Object_newString(wchar_t *start, wchar_t *end) { return &dummy; }
static JSOBJ Object_newTrue(void)            { return &dummy; }
static JSOBJ Object_newFalse(void)           { return &dummy; }
static JSOBJ Object_newNull(void)            { return &dummy; }
static JSOBJ Object_newObject(void)          { return &dummy; }
static JSOBJ Object_newArray(void)           { return &dummy; }
static JSOBJ Object_newInteger(JSINT32 value){ return &dummy; }
static JSOBJ Object_newLong(JSINT64 value)   { return &dummy; }
static JSOBJ Object_newDouble(double value)  { return &dummy; }
static void Object_releaseObject(JSOBJ obj) {}

static my_json_object_t ultrajson_bench_parse(void *context, const char *text, size_t length)
{
    static JSONObjectDecoder decoder = {
        Object_newString,
        Object_objectAddKey,
        Object_arrayAddItem,
        Object_newTrue,
        Object_newFalse,
        Object_newNull,
        Object_newObject,
        Object_newArray,
        Object_newInteger,
        Object_newLong,
        Object_newDouble,
        Object_releaseObject,
        malloc,
        free,
        realloc
    };

    decoder.errorStr = NULL;
    decoder.errorOffset = NULL;
    void *ret = JSON_DecodeObject(&decoder, text, length);
    (void) ret;
}

static void ultrajson_bench_tostr(void *context, my_json_object_t root)
{
}

static void ultrajson_bench_destruct(void *context, my_json_object_t root)
{
}

DEFINE_BENCHMARK(ultrajson);
