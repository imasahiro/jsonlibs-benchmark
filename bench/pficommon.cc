#include "../pficommon/src/text/json.h"
#include "../pficommon/src/text/json/parser.cpp"
#include "../pficommon/src/data/string/ustring.cpp"
#include "bench.h"

using namespace std;
using namespace pfi::lang;
using namespace pfi::text::json;
using namespace pfi::data::serialization;

void f() {
  string s="{\"title\": \"坊ちゃん\"}";
  istringstream ss(s);
  json j; ss>>j;
}


static void *pficommon_bench_context_new()
{
    return 0;
}

static void pficommon_bench_context_delete(void *context)
{
}

static int pficommon_bench_get(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    json &doc = *(json *) root;
    json &obj = doc[0];
    return (int)obj[key].type();
}

static void pficommon_bench_set(void *context, my_json_object_t root, const char *key, size_t keyLength)
{
    json &doc = *(json *) root;
    json &obj = doc[0];
    obj[key] = json(new json_integer(1));
}

static my_json_object_t pficommon_bench_parse(void *context, const char *text, size_t length)
{
    json *doc = new json();
    string s(text);
    istringstream ss(s);
    ss>> (*doc);
    return (my_json_object_t) doc;
}

static void pficommon_bench_tostr(void *context, my_json_object_t root)
{
    ostringstream oss;
    json &doc = *(json *) root;
    oss << doc;
    (void)oss.str();
}

static void pficommon_bench_destruct(void *context, my_json_object_t root)
{
    json *doc = (json *) root;
    delete doc;
}

extern "C" {
    DEFINE_BENCHMARK(pficommon);
}
