#include "../jsoncpp/include/json/json.h"
#include "../jsoncpp/src/lib_json/json_reader.cpp"
#include "../jsoncpp/src/lib_json/json_value.cpp"
#include "../jsoncpp/src/lib_json/json_writer.cpp"
#include "bench.h"
#include <string>

static void *jsoncpp_bench_context_new()
{
    return 0;
}

static void jsoncpp_bench_context_delete(void *context)
{
}

static int jsoncpp_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    Json::Value &val = *(Json::Value *) root;
    Json::Value &a = val[0U];
    return a[key].isNull();
}

static void jsoncpp_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    Json::Value &val = *(Json::Value *) root;
    Json::Value &a = val[0U];
    a[key] = 1;
}

static my_json_object_t jsoncpp_bench_parse(void *context, const char *text, size_t length)
{
    Json::Value *root = new Json::Value();
    Json::Reader reader;
    reader.parse(text, *root);
    return (my_json_object_t) root;
}

static void jsoncpp_bench_tostr(void *context, my_json_object_t root)
{
    Json::Value &val = *(Json::Value *) root;
    Json::FastWriter writer;
    std::string out = writer.write(val);
    (void)out.c_str();
}

static void jsoncpp_bench_destruct(void *context, my_json_object_t root)
{
    Json::Value *val = (Json::Value *) root;
    delete val;
}

extern "C" {
    DEFINE_BENCHMARK(jsoncpp);
}
