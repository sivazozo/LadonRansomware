#include "ladon.h"

static int json_parser_peek(json_parser_t *parser, int skip, char *c)
{
	int ret = parser->pointer < parser->data_size;
	if (ret) *c = parser->data[parser->pointer + skip];
	return ret;
}

static int json_parser_poke(json_parser_t *parser, char *c)
{
	return json_parser_peek(parser, 0, c) && ++parser->pointer;
}

static int json_parser_is_whitespace(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\r') || (c == '\n'));
}

static int
json_parser_is_numeric(char c, int base)
{
	return (((c == '0') || (c == '1'))
		|| ((base >= 10) && ((c >= '0') && (c <= '9')))
		|| ((base >= 16) && ((c >= 'a') && (c <= 'f')))
		|| ((c >= 'A') && (c <= 'F')));
}

static void
json_parser_skip_whitespace(json_parser_t *parser)
{
	char c;
	while (json_parser_peek(parser, 0, &c) && json_parser_is_whitespace(c))
		++parser->pointer;
}

static int
json_parser_ctoi(char c, int base)
{
	int value = -1;

	if ((base == 2) || (base == 10))
		value = (int)c - '0';
	else if (base == 16)
		value = (int)json_parser_is_numeric(c, 10)
		? (c - '0')
		: (c | 0x20) - 'a';

	return value;
}

json_item_t *
json_parse_number(json_parser_t *parser)
{
	json_number_t *number = NULL;
	float value = 0, exponent = 1;
	char digit, sign_hint, base_hint, hint;
	int sign = 1, base = 10, temp = 0;

	if (!json_parser_peek(parser, 0, &sign_hint))
		goto end_fail;

	if ((sign_hint == '+') || (sign_hint == '-'))
	{
		sign = (sign_hint == '-') ? -1 : 1;
		parser->pointer++;
	}

	if (!json_parser_peek(parser, 0, &base_hint))
		goto end_fail;

	/* peek failure is acceptable here because 0 is a possible number */
	if ((base_hint == '0') && json_parser_peek(parser, 2, &base_hint)
		&& ((base_hint == 'x') || (base_hint == 'b')))
	{
		base = (base_hint == 'x') ? 16 : 2;
		parser->pointer += 2;
	}

	while (json_parser_peek(parser, temp, &digit)
		&& json_parser_is_numeric(digit, base))
	{
		temp++;
		exponent *= base;
	}

	while (json_parser_peek(parser, 0, &digit)
		&& json_parser_is_numeric(digit, base))
	{
		json_parser_poke(parser, &digit);

		exponent /= base;
		value += (float)json_parser_ctoi(digit, base) * exponent;
	}

	if ((base == 10) && json_parser_peek(parser, 0, &hint) && (hint == '.'))
	{
		parser->pointer++;
		exponent /= base;

		while (json_parser_poke(parser, &digit)
			&& json_parser_is_numeric(digit, base))
		{
			exponent /= base;
			value += (float)json_parser_ctoi(digit, base) * exponent;
		}
	}

	number = (json_number_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*number));
	if (!number)
		goto end_fail;

	number->type = JSON_NUMBER;
	number->value = sign * value;

end_fail:
	return (json_item_t *)number;
}

json_item_t *
json_parse_string(json_parser_t *parser)
{
	json_string_t *string = NULL;
	unsigned int allocated = 1, size = 0;
	char *value = NULL, *value_temp = NULL;
	char end_char, c, temp1, temp2;

	if (!json_parser_poke(parser, &end_char))
		goto end_fail;

	value = (char*)_HeapAlloc(_GetProcessHeap(), 0, allocated);
	if (!value)
		goto end_fail;

	while (json_parser_peek(parser, 0, &c) && (c != end_char))
	{
		parser->pointer++;

		if ((size + 1) >= allocated)
		{
			allocated *= 2;
// fix this.....
			value_temp = (char*)_HeapReAlloc(_GetProcessHeap(), 0, value, allocated);
			if (!value_temp) {
				_HeapFree(_GetProcessHeap(), 0, value);
				goto end_fail;
			}
			else {
				value = value_temp;
			}
		}

		if (c == '\\')
		{
			if (!json_parser_poke(parser, &c))
			{
				_HeapFree(_GetProcessHeap(), 0, value);
				goto end_fail;
			}

			switch (c)
			{
			case 'x':
				if (!(json_parser_peek(parser, 0, &c)
					&& json_parser_is_numeric(c, 16)
					&& json_parser_peek(parser, 1, &c)
					&& json_parser_is_numeric(c, 16)))
				{
					_HeapFree(_GetProcessHeap(), 0, value);
					goto end_fail;
				}

				json_parser_poke(parser, &temp1);
				json_parser_poke(parser, &temp2);

				value[size] = ((char)json_parser_ctoi(temp1, 16) * 16
					+ (char)json_parser_ctoi(temp2, 16));
				break;
			case '\'':
				value[size] = '\'';
				break;
			case '\"':
				value[size] = '\"';
				break;
			case '\\':
				value[size] = '\\';
				break;
			case 'n':
				value[size] = '\n';
				break;
			case 'r':
				value[size] = '\r';
				break;
			case 't':
				value[size] = '\t';
				break;
			case 'b':
				value[size] = '\b';
				break;
			case 'f':
				value[size] = '\f';
				break;
			case 'v':
				value[size] = '\v';
				break;
			case '0':
				value[size] = '\0';
				break;
			default:
				value[size] = c;
			}
		}
		else {
			value[size] = c;
		}

		size++;
	}

	value[size] = '\0';

	if (!json_parser_poke(parser, &c) || (c != end_char))
	{
		_HeapFree(_GetProcessHeap(), 0, value);
		goto end_fail;
	}

	string = (json_string_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*string));
	if (!string)
	{
		_HeapFree(_GetProcessHeap(), 0, value);
		goto end_fail;
	}

	string->type = JSON_STRING;
	string->value = value;

end_fail:
	return (json_item_t *)string;
}

json_item_t *
json_parse_object(json_parser_t *parser)
{
	json_string_t *key;
	json_item_t *json_item;
	json_object_t *object = NULL;
	list_item_t *list_item;
	hashmap_t *value;
	char c;

	value = hashmap_new(4);
	if (!value)
		goto end_fail;

	if (!(json_parser_poke(parser, &c) && (c == '{')))
	{
		hashmap_free(value);
		goto end_fail;
	}

	json_parser_skip_whitespace(parser);

#define FREE_MAP_ITEMS() \
  for (size_t i = 0; i < value->nbuckets; i++) \
    for (list_item = value->buckets[i].head; list_item \
        ; list_item = list_item->next) \
      json_free ((json_item_t *) ((hashmap_entry_t *) list_item->value)->value);

	while (json_parser_peek(parser, 0, &c) && (c != '}'))
	{
		key = (json_string_t *)json_parse_string(parser);
		if (!key)
		{
			FREE_MAP_ITEMS();
			hashmap_free(value);
			goto end_fail;
		}

		json_parser_skip_whitespace(parser);

		if (!(json_parser_poke(parser, &c) && (c == ':')))
		{
			FREE_MAP_ITEMS();
			hashmap_free(value);
			goto end_fail;
		}

		json_parser_skip_whitespace(parser);

		json_item = json_parse_item(parser);
		if (!json_item)
		{
			FREE_MAP_ITEMS();
			hashmap_free(value);
			goto end_fail;
		}

		json_parser_skip_whitespace(parser);

		hashmap_put(value, key->value, json_item);
		json_free((json_item_t *)key);

		if (!json_parser_peek(parser, 0, &c) || (c != ','))
			break;

		parser->pointer++;
		json_parser_skip_whitespace(parser);
	}

	json_parser_skip_whitespace(parser);

	if (!(json_parser_poke(parser, &c) && (c == '}')))
	{
		FREE_MAP_ITEMS();
		hashmap_free(value);
		goto end_fail;
	}

	object = (json_object_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*object));
	if (!object)
	{
		FREE_MAP_ITEMS();
		hashmap_free(value);
		goto end_fail;
	}

#undef FREE_MAP_ITEMS

	object->type = JSON_OBJECT;
	object->value = value;
end_fail:
	return (json_item_t *)object;
}

json_item_t *
json_parse_array(json_parser_t *parser)
{
	json_array_t *array = NULL;
	json_item_t *item;
	list_item_t *list_item;
	list_t value = list_new();
	char c;

	if (!(json_parser_poke(parser, &c) && (c == '[')))
	{
		list_free(&value);
		goto end_fail;
	}

	json_parser_skip_whitespace(parser);

#define FREE_LIST_ITEMS() \
  for (list_item = value.head; list_item; list_item = list_item->next) \
    json_free ((json_item_t *) list_item->value);

	while (json_parser_peek(parser, 0, &c) && (c != ']'))
	{
		item = json_parse_item(parser);
		if (!(item && list_put(&value, item)))
		{
			FREE_LIST_ITEMS();
			list_free(&value);
			goto end_fail;
		}

		json_parser_skip_whitespace(parser);

		if (!json_parser_peek(parser, 0, &c) || (c != ','))
			break;

		parser->pointer++;
		json_parser_skip_whitespace(parser);
	}

	json_parser_skip_whitespace(parser);

	if (!(json_parser_poke(parser, &c) && (c == ']')))
	{
		FREE_LIST_ITEMS();
		list_free(&value);
		goto end_fail;
	}

	array = (json_array_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*array));
	if (!array)
	{
		FREE_LIST_ITEMS();
		list_free(&value);
		goto end_fail;
	}

#undef FREE_LIST_ITEMS

	array->type = JSON_ARRAY;
	array->value = value;
end_fail:
	return (json_item_t *)array;
}

json_item_t *
json_parse_null(json_parser_t *parser)
{
	json_item_t *item = NULL;
	char c;

	if (!((json_parser_peek(parser, 0, &c) && (c == 'n'))
		&& (json_parser_peek(parser, 1, &c) && (c == 'u'))
		&& (json_parser_peek(parser, 2, &c) && (c == 'l'))
		&& (json_parser_peek(parser, 3, &c) && (c == 'l'))))
		goto end_fail;

	parser->pointer += 4;

	item = (json_item_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*item));
	if (!item)
		goto end_fail;

	item->type = JSON_NULL;

end_fail:
	return item;
}

json_item_t *
json_parse_item(json_parser_t *parser)
{
	json_item_t *item = NULL;
	char hint;

	json_parser_skip_whitespace(parser);

	if (!(json_parser_peek(parser, 0, &hint)))
		goto end_fail;

	switch (hint)
	{
	case '{':
		item = json_parse_object(parser);
		break;
	case '[':
		item = json_parse_array(parser);
		break;
	case '\"':
	case '\'':
		item = json_parse_string(parser);
		break;
	default:
		if (json_parser_is_numeric(hint, 16) || (hint == '.'))
			item = json_parse_number(parser);
		else if (hint == 'n')
			item = json_parse_null(parser);
		break;
	}

	json_parser_skip_whitespace(parser);

end_fail:
	return item;
}

json_item_t *
json_parse(char *json_str)
{
	json_parser_t parser;
	parser.data = json_str;
	parser.data_size = (int)_lstrlen(json_str);
	parser.pointer = 0;

	return json_parse_item(&parser);
}

void
json_free(json_item_t *item)
{
	list_item_t *list_item;

	switch (item->type)
	{
	case JSON_STRING:
		_HeapFree(_GetProcessHeap(), 0, ((json_string_t *)item)->value);

		break;
	case JSON_OBJECT:
	{
		json_object_t *as_obj = (json_object_t *)item;

		for (size_t i = 0; i < as_obj->value->nbuckets; i++)
		{
			list_item = as_obj->value->buckets[i].head;
			for (; list_item; list_item = list_item->next)
				json_free((json_item_t*)((hashmap_entry_t*)list_item->value)->value);
		}

		hashmap_free(as_obj->value);
	}
	break;
	case JSON_ARRAY:
		list_item = ((json_array_t *)item)->value.head;

		for (; list_item; list_item = list_item->next)
			json_free((json_item_t *)list_item->value);

		list_free(&((json_array_t *)item)->value);
		break;
	default:
		break;
	}

	_HeapFree(_GetProcessHeap(), 0, item);
}
