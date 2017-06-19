#ifndef MACRO_H
#define MACRO_H

#define ERROR_CODE -1


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
		return ERROR_CODE; \
	} \


#define _ENUM_TO_STRING_UNIT(val) #val,
	
#define DECLARE_ENUM_TO_STRING(TYPE) \
	char * TYPE##_enum_to_string(enum TYPE); \

#define DEFINE_ENUM_TO_STRING(TYPE, LIST) \
	static char * TYPE##_string_array [] = { \
		LIST(_ENUM_TO_STRING_UNIT) \
	}; \
	char * TYPE##_enum_to_string(enum TYPE x){ \
		return TYPE##_string_array[x]; \
	} \

#endif