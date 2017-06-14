#ifndef MACRO_H
#define MACRO_H

#define MATCH_ERROR -1

#define _ENUM_UNIT(val) val,

#define DECLARE_ENUM(TYPE, LIST) \
	enum TYPE { \
		LIST(_ENUM_UNIT) \
	}; \

#define _STRING_TO_ENUM_UNIT(val) if(!strcmp(s, #val)) return val;

#define DECLARE_STRING_TO_ENUM(TYPE) \
	int TYPE##_string_to_enum(char *);	\

#define DEFINE_STRING_TO_ENUM(TYPE, LIST) \
	int TYPE##_string_to_enum(char * s) { \
		LIST(_STRING_TO_ENUM_UNIT) \
		return MATCH_ERROR; \
	} \

#endif