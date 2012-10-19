#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include "bench.h"

#define USE_BENCH_PARSE 1
//#define USE_BENCH_TOSTR 1
//#define USE_BENCH_GET0  1
//#define USE_BENCH_GET1  1
//#define USE_BENCH_SET   1
static struct timeval g_timer;
static void reset_timer()
{
    gettimeofday(&g_timer, NULL);
}

static void show_timer(const char *s)
{
    struct timeval endtime;
    gettimeofday(&endtime, NULL);
    double sec = (endtime.tv_sec - g_timer.tv_sec)
        + (double)(endtime.tv_usec - g_timer.tv_usec) / 1000 / 1000;
    printf("%s, %f, ", s, sec);
    reset_timer();
}

static char *loadFile(const char *file, size_t *length)
{
    char pathbuf[1024];
    snprintf(pathbuf, 1024, "%s", file);
    FILE *fp = fopen(pathbuf, "rb");
    if (!fp) {
        snprintf(pathbuf, 1024, "../%s", file);
        fp = fopen(pathbuf, "rb");
    }
    assert(fp != 0);
    fseek(fp, 0, SEEK_END);
    size_t len = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *json = (char*)calloc(1, len + 1);
    if (len != fread(json, 1, len, fp)) {
        exit(EXIT_FAILURE);
    }
    json[len] = '\0';
    fclose(fp);
    *length = len;
    return json;
}

static void *nop_bench_context_new()
{
    return 0;
}

static void nop_bench_context_delete(void *context)
{
}

static int nop_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    return 0;
}

static void nop_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
}

static my_json_object_t nop_bench_parse(void *context, const char *text, size_t length)
{
    return 0;
}

static void nop_bench_tostr(void *context, my_json_object_t root)
{
}

static void nop_bench_destruct(void *context, my_json_object_t root)
{
}

DEFINE_BENCHMARK(nop);

int iteration = 16;
#define PARSER_ITR  64
#define GETTER_SETTER_ITR (1024*128)
void benchmark(struct benchmark *bench)
{
    int i, j;
    my_json_object_t root;
    my_json_object_t objects[PARSER_ITR*iteration];
    size_t length;
    const char *text;
#if 1
    text = loadFile("twitter_public.json", &length);
#else
    text = "[{\"a\" : 1000}]";
    length = strlen(text);
#endif
    printf("\n%s, ", bench->NAME);
    bench->context = bench->fn_context_new();
    root = bench->fn_parse(bench->context, text, length);

#ifdef USE_BENCH_PARSE
    reset_timer();
    for (i = 0; i < iteration; i++) {
        for (j = 0; j < PARSER_ITR; j++) {
            objects[PARSER_ITR*i+j] = bench->fn_parse(bench->context, text, length);
        }
    }
    show_timer("JSON.parse");
#endif

#ifdef USE_BENCH_TOSTR
    for (i = 0; i < iteration; i++) {
        for (j = 0; j < PARSER_ITR; j++) {
            bench->fn_tostr(bench->context, objects[PARSER_ITR*i+j]);
        }
    }
    show_timer("JSON.toString");
#endif

#ifdef USE_BENCH_GET0
    const char *key0 = "in_reply_to_status_id";
    size_t len0 = strlen("in_reply_to_status_id");
    for (i = 0; i < iteration*GETTER_SETTER_ITR; i++) {
        bench->fn_get(bench->context, root, key0, len0);
    }
    show_timer("JSON.get[Found]");
#endif

#ifdef USE_BENCH_GET1
    const char *key1 = "_______NOT_FOUND_______";
    size_t len1 = strlen("_______NOT_FOUND_______");
    for (i = 0; i < iteration*GETTER_SETTER_ITR; i++) {
        bench->fn_get(bench->context, root, key1, len1);
    }
    show_timer("JSON.get[NotFound]");
#endif

#ifdef USE_BENCH_SET
    const char *key2 = "_______NEW KEY_______";
    size_t len2 = strlen("_______NEW KEY_______");
    for (i = 0; i < iteration*GETTER_SETTER_ITR; i++) {
        bench->fn_set(bench->context, root, key2, len2);
    }
    show_timer("JSON.set");
#endif

    bench->fn_tostr(bench->context, root);
    bench->fn_context_delete(bench->context);
}

int main(int argc, char* argv[])
{
#define RUN(NAME) do {\
    extern struct benchmark benchmark_##NAME;\
    benchmark(&benchmark_##NAME);\
} while (0)
    int i;
#define N 32
    for (i = 0; i < N; i++) {
#define BENCH_ALL
#ifndef BENCH_ALL
        RUN(kjson);
#else
        //RUN(nop);
        //RUN(kjson);
        RUN(rapidjson);
        //RUN(cJSON);
        //RUN(yajl);
        //RUN(jansson);
        //RUN(json_c);
        //RUN(jsoncpp);
        //RUN(picojson);
        //RUN(ultrajson);
        //RUN(pficommon);
#endif
        printf("\n");
    }
#undef RUN
    return 0;
}
