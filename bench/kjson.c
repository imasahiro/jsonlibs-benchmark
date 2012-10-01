#include "../kjson/kjson.c"
#include "bench.h"

static void *kjson_bench_context_new()
{
    JSONMemoryPool *jm = (JSONMemoryPool *) malloc(sizeof(*jm));
    JSONMemoryPool_Init(jm);
    return (void *) jm;
}

static void  kjson_bench_context_delete(void *context)
{
    JSONMemoryPool *jm = (JSONMemoryPool *) context;
    JSONMemoryPool_Delete(jm);
    free(jm);
}

static int kjson_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    JSON json = (JSON) root;
    JSON ary = JSONArray_get(json, 0);
    JSON val = JSON_get(ary, key, keyLength);
    return val.bits != 0;
}

static void kjson_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    JSONMemoryPool *jm = (JSONMemoryPool *) context;
    JSON json = (JSON) root;
    JSON ary = JSONArray_get(json, 0);
    JSONObject_set(jm, ary, JSONString_new(jm, key, keyLength), JSONNull_new());
}

static my_json_object_t kjson_bench_parse(void *context, const char *text, size_t length)
{
    JSONMemoryPool *jm = (JSONMemoryPool *) context;
    JSON json = parseJSON(jm, text, text + length);
    return (my_json_object_t) json.bits;
}

static void kjson_bench_tostr(void *context, my_json_object_t root)
{
    JSON json = (JSON) root;
    char *str = JSON_toString(json);
    free(str);
}

static void kjson_bench_destruct(void *context, my_json_object_t root)
{
    JSON json = (JSON) root;
    JSON_free(json);
}

DEFINE_BENCHMARK(kjson);
