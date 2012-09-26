#include "../json-1.5/src/json.h"
#include "../json-1.5/src/json_helper.h"
#include "../json-1.5/src/json.c"
#include "../json-1.5/src/json_helper.c"
#include "bench.h"

static void *mjson_bench_context_new()
{
    return NULL;
}

static void  mjson_bench_context_delete(void *context)
{
}

static int mjson_bench_get(void *context, json_object_t root, const char *key, size_t keyLength)
{
    /* M's JSON parser do not support accessing to element with index' */
    return 0;
}

static void mjson_bench_set(void *context, json_object_t root, const char *key, size_t keyLength)
{
    /* M's JSON parser do not support accessing to element with index' */
}

static json_object_t mjson_bench_parse(void *context, const char *text, size_t length)
{
    json_t *json = NULL;
    json_parse_document(&json, text);
    return (json_object_t) json;
}

static void mjson_bench_tostr(void *context, json_object_t root)
{
    json_t *json = (json_t *) root;
    char *str;
    json_tree_to_string(json, &str);
    free(str);
}

static void mjson_bench_destruct(void *context, json_object_t root)
{
    json_t *json = (json_t *) root;
    json_free_value(&json);
}

DEFINE_BENCHMARK(mjson);
