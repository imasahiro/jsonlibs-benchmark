#include <stdio.h>
#ifndef JANSSON_CONFIG_H
#define JANSSON_CONFIG_H
#ifdef __cplusplus
#define JSON_INLINE inline
#else
#define JSON_INLINE inline
#endif
#define JSON_INTEGER_IS_LONG_LONG 1
#define JSON_HAVE_LOCALECONV 1
#endif

#include "../jansson/src/jansson.h"
#include "../jansson/src/jansson_private.h"
#include "../jansson/src/strbuffer.h"
#include "../jansson/src/utf.h"
#include "../jansson/src/hashtable.h"
#include "../jansson/src/dump.c"
#include "../jansson/src/error.c"
#include "../jansson/src/hashtable.c"
#include "../jansson/src/load.c"
#include "../jansson/src/memory.c"
#include "../jansson/src/pack_unpack.c"
#include "../jansson/src/strbuffer.c"
#include "../jansson/src/strconv.c"
#include "../jansson/src/utf.c"
#include "../jansson/src/value.c"
#include "bench.h"

static void *jansson_bench_context_new()
{
    return NULL;
}

static void  jansson_bench_context_delete(void *context)
{
}

static int jansson_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    json_t *json = (json_t *) root;
    json_t *obj = json_array_get(json, 0);
    json_t *val = json_object_get(obj, key);
    return val != 0;
}

static void jansson_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    json_t *json = (json_t *) root;
    json_t *obj = json_array_get(json, 0);
    json_object_set_new(obj, key, json_null());
}

static my_json_object_t jansson_bench_parse(void *context, const char *text, size_t length)
{
    json_error_t error;
    json_t *json = json_loadb(text, length, 0, &error);
    json_incref(json);
    return (my_json_object_t) json;
}

static void jansson_bench_tostr(void *context, my_json_object_t root)
{
    json_t *json = (json_t *) root;
    char *str = json_dumps(json, 0);
    free(str);
}

static void jansson_bench_destruct(void *context, my_json_object_t root)
{
    json_t *json = (json_t *) root;
    json_decref(json);
}

DEFINE_BENCHMARK(jansson);
