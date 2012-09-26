#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>
#include "bench.h"

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
    printf("%20s: %f sec\n", s, sec);
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
    printf("%s\n", bench->NAME);
    bench->context = bench->fn_context_new();
    root = bench->fn_parse(bench->context, text, length);

    reset_timer();
    for (i = 0; i < iteration; i++) {
        for (j = 0; j < PARSER_ITR; j++) {
            objects[PARSER_ITR*i+j] = bench->fn_parse(bench->context, text, length);
        }
    }
    show_timer("JSON.parse");

    for (i = 0; i < iteration; i++) {
        for (j = 0; j < PARSER_ITR; j++) {
            bench->fn_tostr(bench->context, objects[PARSER_ITR*i+j]);
        }
    }
    show_timer("JSON.toString");

    const char *key0 = "in_reply_to_status_id";
    size_t len0 = strlen("in_reply_to_status_id");
    for (i = 0; i < iteration*GETTER_SETTER_ITR; i++) {
        bench->fn_get(bench->context, root, key0, len0);
    }
    show_timer("JSON.get[Found]");

    const char *key1 = "_______NOT_FOUND_______";
    size_t len1 = strlen("_______NOT_FOUND_______");
    for (i = 0; i < iteration*GETTER_SETTER_ITR; i++) {
        bench->fn_get(bench->context, root, key1, len1);
    }
    show_timer("JSON.get[NotFound]");

    const char *key2 = "_______NEW KEY_______";
    size_t len2 = strlen("_______NEW KEY_______");
    for (i = 0; i < iteration*GETTER_SETTER_ITR; i++) {
        bench->fn_set(bench->context, root, key2, len2);
    }
    show_timer("JSON.set");

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
    for (i = 0; i < 1; i++) {
        RUN(kjson);
        RUN(rapidjson);
        //RUN(cJSON);
        //RUN(yajl);
        RUN(jansson);
        RUN(json_c);
        RUN(ultrajson);
        RUN(pficommon);
    }
#undef RUN
    return 0;
}
