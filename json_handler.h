#ifndef JSON_HANDLER
#define JSON_HANDLER
#include<json-c/json.h>

struct json_object *parse_json_file(const char *);
int save_json_file(struct json_object *,const char *);


#endif
