#include <stdio.h>
#include "../cJSON/cJSON.h"
#include "../cJSON/cJSON.c"
#include "bench.h"

static void *cJSON_bench_context_new()
{
    return NULL;
}

static void  cJSON_bench_context_delete(void *context)
{
}

static int cJSON_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    cJSON *json = (cJSON *) root;
    cJSON *obj = cJSON_GetArrayItem(json, 0);
    cJSON *val = cJSON_GetObjectItem(obj, key);
    return val != 0;
}

static void cJSON_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    /* cJSON's setter is totally slow. */
#if 0
    cJSON *json = (cJSON *) root;
    cJSON *obj = cJSON_GetArrayItem(json, 0);
    cJSON_AddItemToObject(obj, key, cJSON_CreateNull());
#endif
}

static my_json_object_t cJSON_bench_parse(void *context, const char *text, size_t length)
{
    cJSON *json = cJSON_Parse(text);
    return (my_json_object_t) json;
}

static void cJSON_bench_tostr(void *context, my_json_object_t root)
{
    cJSON *json = (cJSON *) root;
    char *str = cJSON_Print(json);
    free(str);
}

static void cJSON_bench_destruct(void *context, my_json_object_t root)
{
    cJSON *json = (cJSON *) root;
    cJSON_Delete(json);
}

DEFINE_BENCHMARK(cJSON);
