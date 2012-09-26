#include "../kjson/kjson.c"
#include "bench.h"

static void *kjson_bench_context_new()
{
    return NULL;
}

static void  kjson_bench_context_delete(void *context)
{
}

static int kjson_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    JSON json = (JSON) root;
    JSON ary = JSONArray_get(json, 0);
    JSON val = JSON_get(ary, key);
    return val.bits != 0;
}

static void kjson_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    JSON json = (JSON) root;
    JSON ary = JSONArray_get(json, 0);
    JSONObject_set(ary, JSONString_new(key, keyLength), JSONInt_new(1));
}

static my_json_object_t kjson_bench_parse(void *context, const char *text, size_t length)
{
    JSON json = parseJSON(text, text + length);
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
