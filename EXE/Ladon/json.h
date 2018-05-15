#ifndef JSON_H
#define JSON_H

#include "linked_list.h"
#include "hashmap.h"

typedef
enum json_type_t {
	JSON_NULL,
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_NUMBER,
	JSON_STRING
} json_type_t;

typedef
struct json_item_t {
	json_type_t type;
} json_item_t;

typedef
struct json_number_t {
	json_type_t type;
	float value;
} json_number_t;

typedef
struct json_string_t {
	json_type_t type;
	char *value;
} json_string_t;

typedef
struct json_array_t {
	json_type_t type;
	list_t value;
} json_array_t;

typedef
struct json_object_t {
	json_type_t type;
	hashmap_t *value;
} json_object_t;

typedef
struct json_parser_t {
	char *data;
	int data_size;
	int pointer;
} json_parser_t;

json_item_t *json_parse_item(json_parser_t *parser);
json_item_t *json_parse_number(json_parser_t *parser);
json_item_t *json_parse_string(json_parser_t *parser);
json_item_t *json_parse_object(json_parser_t *parser);
json_item_t *json_parse_array(json_parser_t *parser);
json_item_t *json_parse_null(json_parser_t *parser);
json_item_t *json_parse_item(json_parser_t *parser);
json_item_t *json_parse(char *json_str);
void json_free(json_item_t *item);

#endif /* JSON_H */