/* employe operations header */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<json-c/json.h>

int query(struct json_object *root, const char *id);
int add(struct json_object *root);
int modify(struct json_object *root, const char *id);
int delete_employee(struct json_object *root, const char *id);

#endif
