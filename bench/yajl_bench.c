#include "api/yajl_common.h"
#include "api/yajl_gen.h"
#include "api/yajl_parse.h"
#include "api/yajl_tree.h"
#include "yajl_alloc.h"
#include "yajl_buf.h"
#include "yajl_bytestack.h"
#include "yajl_encode.h"
#include "yajl_lex.h"
#include "yajl_parser.h"
#include "yajl.c"
#include "yajl_alloc.c"
#include "yajl_buf.c"
#include "yajl_encode.c"
#include "yajl_gen.c"
#include "yajl_lex.c"
#include "yajl_parser.c"
#include "yajl_tree.c"
#include "yajl_version.c"


#include "bench.h"

static void *yajl_bench_context_new()
{
    return 0;
}

static void  yajl_bench_context_delete(void *context)
{
}

static int yajl_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    /* TODO(imasahiro) */
    return 0;
}

static void yajl_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    /* TODO(imasahiro) */
}

static my_json_object_t yajl_bench_parse(void *context, const char *text, size_t length)
{
    yajl_val json = yajl_tree_parse(text, NULL, 0);
    return (my_json_object_t) json;
}

static void yajl_bench_tostr(void *context, my_json_object_t root)
{
    /*TODO(imasahiro)*/
}

static void yajl_bench_destruct(void *context, my_json_object_t root)
{
    yajl_val json = (yajl_val) root;
    yajl_tree_free(json);
}

DEFINE_BENCHMARK(yajl);
