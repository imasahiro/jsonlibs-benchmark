#include <stdio.h>
#include <stdint.h>
#include "../json-c/json.h"
#include "../json-c/json_object.h"
#include "../json-c/arraylist.c"
#include "../json-c/debug.c"
#include "../json-c/json_object.c"
#include "../json-c/json_tokener.c"
#include "../json-c/json_util.c"
#include "../json-c/linkhash.c"
#include "../json-c/printbuf.c"


#include "bench.h"

static void *json_c_bench_context_new()
{
    return NULL;
}

static void  json_c_bench_context_delete(void *context)
{
}

static int json_c_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    json_object *json = (json_object *) root;
    json_object *obj = json_object_array_get_idx(json, 0);
    json_object *val = json_object_object_get(obj, key);
    return val != 0;
}

static void json_c_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    json_object *json = (json_object *) root;
    json_object *obj = json_object_array_get_idx(json, 0);
    json_object_object_add(obj, key, json_object_new_int(1));
}

static my_json_object_t json_c_bench_parse(void *context, const char *text, size_t length)
{
    json_object *json = json_tokener_parse(text);
    _json_object_get(json);
    return (my_json_object_t) json;
}

static void json_c_bench_tostr(void *context, my_json_object_t root)
{
    json_object *json = (json_object *) root;
    char *str = json_object_to_json_string(json);
    free(str);
}

static void json_c_bench_destruct(void *context, my_json_object_t root)
{
    json_object *json = (json_object *) root;
    json_object_put(json);
}

DEFINE_BENCHMARK(json_c);
