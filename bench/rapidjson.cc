#define RAPIDJSON_SSE2
#include "../rapidjson/include/rapidjson/rapidjson.h"
#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/prettywriter.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "../rapidjson/include/rapidjson/filestream.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "bench.h"
#include <string>

using namespace rapidjson;

static void *rapidjson_bench_context_new()
{
    return (void *) new Document();
}

static void rapidjson_bench_context_delete(void *context)
{
    Document *doc = (Document *) context;
    delete doc;
}

static int rapidjson_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    Document &doc = *(Document *) root;
    SizeType index(0);
    const Value &a = doc[index];
    return a.HasMember(key);
}

static void rapidjson_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    Document &doc = *(Document *) root;
    SizeType index(0);
    Value &a = doc[index];
    a[key] = 1;
}

static my_json_object_t rapidjson_bench_parse(void *context, const char *text, size_t length)
{
    Document *doc = new Document();
    char buf[length+1];
    memcpy(buf, text, length);
    buf[length] = 0;
    doc->ParseInsitu<0>(buf);
    return (my_json_object_t) doc;
}

static void rapidjson_bench_tostr(void *context, my_json_object_t root)
{
    Document &doc = *(Document *) root;
    StringBuffer s(0, 2048*1024);
    Writer<StringBuffer> writer(s);
    doc.Accept(writer);
    const char *str = s.GetString();
    (void)str;
}

static void rapidjson_bench_destruct(void *context, my_json_object_t root)
{
    Document *doc = (Document *) root;
    delete doc;
}

extern "C" {
    DEFINE_BENCHMARK(rapidjson);
}
