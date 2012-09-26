#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t my_json_object_t;
struct benchmark {
    void *context;
    my_json_object_t root;
    void *(*fn_context_new)();
    void  (*fn_context_delete)(void *context);
    int   (*fn_get)(void *context, my_json_object_t root, const char *key, size_t keyLength);
    void (*fn_set)(void *context, my_json_object_t root, const char *key, size_t keyLength);
    my_json_object_t (*fn_parse)(void *context, const char *text, size_t length);
    void (*fn_tostr)(void *context, my_json_object_t root);
    void (*fn_destruct)(void *context, my_json_object_t root);
    const char *NAME;
};

#define DEFINE_BENCHMARK(NAME)\
    struct benchmark benchmark_##NAME = {0, 0,\
        NAME##_bench_context_new,\
        NAME##_bench_context_delete,\
        NAME##_bench_get,\
        NAME##_bench_set,\
        NAME##_bench_parse,\
        NAME##_bench_tostr,\
        NAME##_bench_destruct,\
        #NAME\
    }

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* end of include guard */
