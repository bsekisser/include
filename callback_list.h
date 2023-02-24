#pragma once

typedef int (*callback_fn)(void* param);

typedef struct callback_list_elem_t* callback_list_elem_p;
typedef struct callback_list_elem_t {
	callback_fn fn;
	void* param;
}callback_list_elem_t;

typedef struct callback_list_t* callback_list_p;
typedef struct callback_list_t {
	int limit;
	callback_list_elem_t cble[16];
}callback_list_t;

void callback_list_init(callback_list_p cbl, int additional);
void callback_list_process(callback_list_p cbl);
void callback_list_register_callback(callback_list_p cbl, callback_fn fn, void* param);

#define DEFN_CALLBACK_REGISTER_FN(_name, _type, _what, _llist) \
	void _name ## _callback_ ## _llist(_type _what, callback_fn fn, void* param)

#define DECL_CALLBACK_REGISTER_FN(_name, _type, _what, _llist) \
	DEFN_CALLBACK_REGISTER_FN(_name, _type, _what, _llist) { \
		callback_list_register_callback(&_what->_llist ## _list, fn, param); \
	};
