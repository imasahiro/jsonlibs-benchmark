#include "picojson.h"
#include "bench.h"

using namespace picojson;

static void *picojson_bench_context_new()
{
    return 0;
}

static void picojson_bench_context_delete(void *context)
{
}

static int picojson_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    value &doc = *(value *) root;
    const value &obj = doc.get(0);
    return obj.get(key);
}

static void picojson_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    /*TODO*/
}

static my_json_object_t picojson_bench_parse(void *context, const char *text, size_t length)
{
    value *doc = new value();
    std::string err = parse(*doc, text, text + length);
    return (my_json_object_t) doc;
}

static void picojson_bench_tostr(void *context, my_json_object_t root)
{
    value &doc = *(value *) root;
    const char *str = doc.serialize().c_str();
    asm volatile("" ::: "memory");
    (void)str;
}

static void picojson_bench_destruct(void *context, my_json_object_t root)
{
    value *doc = (value *) root;
    delete doc;
}

extern "C" {
    DEFINE_BENCHMARK(picojson);
}
