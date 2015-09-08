/*
 * bundle
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Contact: Jayoun Lee <airjany@samsung.com>, Sewook Park <sewook7.park@samsung.com>,
 * Jaeho Lee <jaeho81.lee@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#ifndef __BUNDLE_H__
#define __BUNDLE_H__

/**
 * @file bundle.h
 * @brief    This file declares has API of the bundle library
 */

/**
 * @addtogroup CORE_LIB_BUNDLE_MODULE
 * @{
 */

#include <errno.h>
#include <stddef.h>
#include <tizen_error.h>

#ifdef __cplusplus
extern "C" {
# endif

#define API	__attribute__((visibility("default")))
#define likely(x) __builtin_expect(x,1)
#define unlikely(x) __builtin_expect(x,0)

/**
 * @brief Enumeration for error code of Bundle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum
{
	BUNDLE_ERROR_NONE = TIZEN_ERROR_NONE,					/**< Successful */
	BUNDLE_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY,			/**< Out of memory */
	BUNDLE_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,		/**< Invalid parameter */
	BUNDLE_ERROR_KEY_NOT_AVAILABLE = TIZEN_ERROR_KEY_NOT_AVAILABLE,	/**< Required key not available */
	BUNDLE_ERROR_KEY_EXISTS = TIZEN_ERROR_BUNDLE | 0x01	/**< Key exists */
} bundle_error_e;

/**
 * @brief The bundle handle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef struct _bundle_t bundle;

/**
 * @brief The encoded data type.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @see bundle_encode()
 * @see bundle_decode()
 */
typedef unsigned char bundle_raw;


/**
 * @brief Enumeration for key-value pair types.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
enum bundle_type_property {
	BUNDLE_TYPE_ARRAY = 0x0100,	/**< Array type */
	BUNDLE_TYPE_PRIMITIVE = 0x0200,	/**< Primitive type */
	BUNDLE_TYPE_MEASURABLE = 0x0400	/**< Measurable type */
};

/**
 * @brief Enumeration for bundle types.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
enum bundle_type {
	BUNDLE_TYPE_NONE = -1,	/**< None */
	BUNDLE_TYPE_ANY = 0,	/**< Any type */
	BUNDLE_TYPE_STR = 1 | BUNDLE_TYPE_MEASURABLE,	/**< String type (Default) */
	BUNDLE_TYPE_STR_ARRAY = BUNDLE_TYPE_STR | BUNDLE_TYPE_ARRAY | BUNDLE_TYPE_MEASURABLE,	/**< String array type */
	BUNDLE_TYPE_BYTE = 2,	/**< Byte type */
	BUNDLE_TYPE_BYTE_ARRAY = BUNDLE_TYPE_BYTE | BUNDLE_TYPE_ARRAY	/**< Byte array type */
};

/**
 * @brief The key-value pair handle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @see bundle_iterator_t
 */
typedef struct keyval_t bundle_keyval_t;


/**
 * @brief Called for every key-value pair.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @see bundle_foreach()
 */
typedef void (*bundle_iterator_t) (
		const char *key,
		const int type,
		const bundle_keyval_t *kv,
		void *user_data
);


/**
 * @internal
 * @brief Called for every key-value pair.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks This type is obsolete. You must not use this type any more.
 * @see bundle_iterate()
 */
typedef void (*bundle_iterate_cb_t) (const char *key, const char *val, void *data);


/**
 * @brief Creates a bundle object.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @return	The bundle object
 * @retval	@c NULL - Failure
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @see			bundle_free()
 *
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_free(b); // free bundle
 @endcode
 */
API bundle*		bundle_create(void);

/**
 * @brief Frees the given bundle object with key-value pairs in it.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object to be freed
 * @return		The operation result;
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_create()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_free(b); // free bundle
 @endcode
 */
API int			bundle_free(bundle *b);

/**
 * @brief Adds a strings array type key-value pair into a given bundle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[in]	str_array The string type value; if @c NULL, an empty array is created; you can change an item with
 * @param[in]	len The length of the array
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_EXISTS	Key already exists
 * @retval BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_get_str_array()
 *
 @code
 #include <bundle.h>
 char *sa = { "aaa", "bbb", "ccc" };	// A string array of length 3
 bundle *b = bundle_create();
 bundle_add_str_array(b, "foo", sa, 3); // add a key-val pair
 bundle_free(b);
 @endcode
 */
API int bundle_add_str_array(bundle *b, const char *key, const char **str_array, const int len);

/**
 * @internal
 * @brief Adds a string type key-value pair into a given bundle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[in]	val	The value
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_EXISTS	Key already exists
 * @retval BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_add_str()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add(b, "foo_key", "bar_val"); // add a key-val pair

 bundle_free(b);
 @endcode
 */
API int				bundle_add(bundle *b, const char *key, const char *val);

/**
 * @brief Deletes a key-value object with the given key.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The given key
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre			@a b must be a valid bundle object.
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair
 bundle_del(b, "foo_key"); // del "foo_key" from b

 bundle_free(b);
 @endcode
 */
API int				bundle_del(bundle *b, const char* key);

/**
 * @brief Gets a string array from a given key.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks 		You MUST NOT free or modify the returned string!
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[out]	len	The array length
 * @return		The pointer to the array of strings
 * @retval		@c NULL - Key not found
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @exception BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_add_str_array()
 @code
 #include <bundle.h>
 bundle *b = bundle_create();
 char *sa = { "aaa", "bbb", "ccc" };	// A string array of length 3
 bundle_add_str_array(b, "foo", sa, 3); // add a key-val pair

 char **str_array = NULL;
 int len_str_array = 0;

 str_array=bundle_get_str_array(b, "foo", &len_str_array);
 // str_array = { "aaa", "bbb", "ccc" }, and len_str_array = 3

 bundle_free(b);
 @endcode
 */
API const char** bundle_get_str_array(bundle *b, const char *key,int *len);

/**
 * @internal
 * @brief Gets a value with a given key.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks		You MUST NOT free or modify the returned string!
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @return		The pointer for the value string
 * @retval		@c NULL - Key not found
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @exception BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_get_str()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo", "bar"); //add a key-val pair
 char *val = bundle_get_val(b, "foo_key");	// val = "bar_val"

 bundle_free(b);	// After freeing b, val becomes a dangling pointer.
 val = NULL;
 @endcode
 */
API const char*		bundle_get_val(bundle *b, const char *key);

/**
 * @brief Gets the number of bundle items.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @return		The number of bundle items
 * @pre			@a b must be a valid bundle object.
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "key1", "val1"); //add a key-val pair
 int count = bundle_get_count(b);	// count=1
 bundle_add_str(b, "key2", "val2"); // add another key-val pair
 count = bundle_get_count(b); // count=2

 bundle_free(b);
 @endcode
 */
API int				bundle_get_count(bundle *b);

/**
 * @brief Gets the type of a value with a given key.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	b	A bundle
 * @param[in]	key	A key in the bundle
 * @return	The type of a key in @a b
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @exception BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre		@a b must be a valid bundle object.
 * @see		bundle_type_t
 @code
 @endcode
 */
API int bundle_get_type(bundle *b, const char *key);

/**
 * @internal
 * @brief Duplicates a given bundle object.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	b_from	the bundle object to be duplicated
 * @return		The new bundle object
 * @retval		@c NULL - Failure
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair
 bundle *b_dup = bundle_dup(b);	// duplicate b

 bundle_free(b);
 bundle_free(b_dup);
 @endcode
 */
API bundle *		bundle_dup(bundle *b_from);

/**
 * @internal
 * @brief Iterates a callback function for each key-value pairs in a given bundle.
 * @details (NOTE: Only BUNDLE_TYPE_STR type values come!)
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @remarks		This function is obsolete and does not give values whose types are not BUNDLE_TYPE_STR.
 * @param[in]	b	The bundle object
 * @param[in]	callback	The iteration callback function
 * @param[in]	cb_data	The data for callback function
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 @code
 #include <stdio.h>
 #include <bundle.h>
 void sample_cb(const char *k, const char *v, void *data) {
   printf("%s -> %s\n", k, v);
 }

 int main(void) {
	 bundle *b = bundle_create(); // Create new bundle object
	 bundle_add_str(b, "k1", "v1"); // add a key-val pair
	 bundle_add_str(b, "k2", "v2"); // add a key-val pair
	 bundle_add_str(b, "k3", "v3"); // add a key-val pair
	 bundle_iterate(b, sample_cb, NULL);	// iterate sample_cb() for each key/val
	 return 0;
 }
 @endcode
 */
API void			bundle_iterate(bundle *b, bundle_iterate_cb_t callback, void *cb_data);

/**
 * @brief Iterates a callback function for each key-value pair in a given bundle.
 * @details Supports all types of values.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @remarks		This function supports all types.
 * @param[in]	b	The bundle object
 * @param[in]	iter	The iteration callback function
 * @param[in]	user_data	The data for the callback function
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_keyval_get_type()
 * @see			bundle_keyval_type_is_array()
 * @see			bundle_keyval_get_basic_val()
 * @see			bundle_keyval_get_array_val()
 @code
 #include <stdio.h>
 #include <bundle.h>
 void sample_cb(const char *key, const int type, const bundle_keyval_t *kv, void *user_data) {
   void *basic_val = NULL;
   size_t basic_size = 0;
   void **array_val = NULL;
   int array_len = 0;
   size_t *array_elem_size = NULL;

   printf("Key:%s, Type:%d\n", key, type);
   if(bundle_keyval_type_is_array(kv)) {
     bundle_keyval_get_array_val(kv, &array_val, &array_len, &array_elem_size);
	 // Do something...
   }
   else {
     bundle_keyval_get_basic_val(kv, &basic_val, &basic_size);
	 // Do something...
   }
 }

 int main(void) {
	 bundle *b = bundle_create(); // Create new bundle object
	 bundle_add_str(b, "k1", "v1"); // add a key-val pair
	 bundle_add_byte(b, "k2", "v2", 3); // add a key-val pair
	 char *s_arr[] = {"abc", "bcd", "cde"};
	 bundle_add_str_array(b, "k3", s_arr, 3); // add a key-val pair
	 bundle_foreach(b, sample_cb, NULL);	// iterate sample_cb() for each key/val
	 return 0;
 }
 @endcode
 */
API void			bundle_foreach(bundle *b, bundle_iterator_t iter, void *user_data);

/**
 * @brief Gets the type of a key-value pair.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	kv	A bundle_keyval_t object
 * @return	The type of @a kv
 * @retval	@c -1 - Failure
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre		@a kv must be a valid bundle_keyval_t object.
 * @see		bundle_foreach()
 */
API int bundle_keyval_get_type(bundle_keyval_t *kv);

/**
 * @brief Determines whether the  type of a key-value pair is array.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	kv	A bundle_keyval_t object
 * @return		The operation result
 * @retval		@c 1 - @a kv is an array
 * @retval		@c 0 - @a kv is not an array
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre		@a kv must be a valid bundle_keyval_t object.
 * @see		bundle_foreach()
 */
API int bundle_keyval_type_is_array(bundle_keyval_t *kv);

/**
 * @internal
 * @brief Determines whether the type of a key-value pair is measurable.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	kv	A bundle_keyval_t object
 * @return		The operation result
 * @retval		@c 1 - @a kv is an measurable
 * @retval		@c 0 - @a kv is not an measurable
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre		@a kv must be a valid bundle_keyval_t object.
 * @see		bundle_foreach()
 */
API int bundle_keyval_type_is_measurable(bundle_keyval_t *kv);

/**
 * @brief Gets the value and size of the value from a key-value pair of basic type.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks	You must not free @a val.
 * @param[in]	kv		A bundle_keyval_t object
 * @param[out]	val		The value
 * @param[out]	size	The size of @a val
 * @return	The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre		@a kv must be a valid bundle_keyval_t object.
 * @post	@a val and @a size are set.
 * @see		bundle_foreach()
 */
API int bundle_keyval_get_basic_val(bundle_keyval_t *kv, void **val, size_t *size);

/**
 * @brief Gets the value array, length of the array, and size of each array item.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	kv		A bundle_keyval_t object
 * @param[out]	array_val	The array pointer of values
 * @param[out]	array_len	The length of @a array_val
 * @param[out]	array_element_size	The array of size of each array element
 * @return	The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre		@a kv must be a valid bundle_keyval_t object.
 * @post	@a array_val, @a array_len, @a array_item_size are set.
 * @see		bundle_foreach()
 */
API int bundle_keyval_get_array_val(bundle_keyval_t *kv, void ***array_val, unsigned int *array_len, size_t **array_element_size);

/**
 * @brief Encodes a bundle to the bundle_raw format (uses base64 format).
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[out]	r	The returned bundle_raw data(byte data)
 *					@a r MUST BE FREED by free(r)
 * @param[out]	len	The size of @a r (in bytes)
 * @return	The size of the raw data
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair
 bundle_raw *r;
 int len;
 bundle_encode(b, &r, &len);	// encode b

 bundle_free(b);
 @endcode
 */
API int				bundle_encode(bundle *b, bundle_raw **r, int *len);

/**
 * @internal
 * @brief Frees the encoded rawdata.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	r	The rawdata
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre		@a r is a valid rawdata generated by bundle_encode().
 * @see		bundle_encode()
 */
API int				bundle_free_encoded_rawdata(bundle_raw **r);

/**
 * @brief Deserializes bundle_raw and gets the bundle object.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	r	The bundle_raw data to be converted to bundle object
 * @param[in]	len	The size of @a r
 * @return	The bundle object
 * @retval	@c NULL - Failure
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair

 bundle_raw *encoded_b;
 int len;
 bundle_encode(b, &encoded_b, &len);	// encode b

 bundle *b_dup;
 b_dup = bundle_decode(encoded_b, len);	// decoded bundle object

 bundle_free(b);
 free(encoded_b);
 bundle_free(b_dup);
 @endcode
 */
API bundle *		bundle_decode(const bundle_raw *r, const int len);

/**
 * @internal
 * @brief Encodes a bundle to the bundle_raw format.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[out]	r	The returned bundle_raw data(byte data)
 *					@a r MUST BE FREED by free(r)
 * @param[out]	len	The size of @a r (in bytes)
 * @return	The size of the raw data
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre			@a b must be a valid bundle object.
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair
 bundle_raw *r;
 int len;
 bundle_encode_raw(b, &r, &len);	// encode b

 bundle_free(b);
 @endcode
 */
API int				bundle_encode_raw(bundle *b, bundle_raw **r, int *len);

/**
 * @internal
 * @brief Deserializes bundle_raw and gets a bundle object.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	r	The bundle_raw data to be converted to a bundle object
 * @param[in]	len	The size of @a r
 * @return	The bundle object
 * @retval	@c NULL - Failure
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair

 bundle_raw *encoded_b;
 int len;
 bundle_encode(b, &encoded_b, &len);	// encode b

 bundle *b_dup;
 b_dup = bundle_decode_raw(encoded_b, len);	// decoded bundle object

 bundle_free(b);
 free(encoded_b);
 bundle_free(b_dup);
 @endcode
 */
API bundle *		bundle_decode_raw(const bundle_raw *r, const int len);

/**
 * @internal
 * @brief Exports bundle to @a argv.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	b	The bundle object
 * @param[out]	argv	The pointer of the string array; \n
 *                      This array has NULL values for the first and last item; \n
 *                      First NULL is for argv[0], and last NULL is a terminator for execv() \n
 * @return	The number of item in @a argv. This value is equal to the actual count of argv - 1. (Last NULL terminator is not counted.)
 * @retval	@c -1 - Failure
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @exception BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre		@a b is a valid bundle object.
 * @post	@a argv is a pointer of newly allocated memory. It must be freed.
 *          Each item of @a argv points to the string in the bundle object @a b. If @a b is freed, @a argv will have garbage pointers. DO NOT FREE @a b BEFORE ACCESSING @a argv!!
 * @see		bundle_import_from_argv()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair

 int argc = 0;
 char **argv = NULL;
 argc = bundle_export_to_argv(b, &argv);	// export to argv
 if(0 > argc) error("export failure");

 int i;
 for(i=0; i < argc; i++) {
   printf("%s\n", argv[i]);		// print argv
 }
 bundle_free_exported_argv(argc, argv);	// argv must be freed after being used.

 bundle_free(b);
 @endcode
 */
API int				bundle_export_to_argv(bundle *b, char ***argv);

/**
 * @internal
 * @brief Frees the exported @a argv.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks	You must not use this API when you use global @a argv.
 * @param[in]	argc	The number of args, which is the return value of bundle_export_to_argv()
 * @param[in]	argv The array from bundle_export_to_argv()
 * @return	The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre		@a argv is a valid string array generated from bundle_export_to_argv().
 * @see		bundle_export_to_argv()
 @code
 bundle *b = bundle_create();
 bundle_add_str(b, "foo", "bar");

 int argc = 0;
 char **argv = NULL;
 argc = bundle_export_to_argv(b, &argv);
 if(0 > argc) error("export failure");

 // Use argv...

 bundle_free_exported_argv(argc, argv);
 argv = NULL;

 bundle_free(b);
 @endcode
 */
API int				bundle_free_exported_argv(int argc, char ***argv);

/**
 * @internal
 * @brief Imports a bundle from @a argv.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in Exception section.
 * @param[in]	argc	The argument count
 * @param[in]	argv	The argument vector
 * @return	The new bundle object
 * @retval	@c NULL - Failure
 * @exception BUNDLE_ERROR_NONE	Success
 * @exception BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @exception BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre		@a argv is a valid string array, which is created by bundle_export_to_argv().
 * @post	The returned bundle @a b must be freed.
 * @see		bundle_export_to_argv()
 @code
 #include <bundle.h>

 int main(int argc, char **argv) {
   bundle *b = bundle_import_from_argv(argc, argv); // import from argc+argv
   char *val = bundle_get_val(b, "foo_key");	// value for "foo_key"
   // ......
   bundle_free(b);	// After freeing b, val becomes a dangling pointer.
   val = NULL;
 }
 @endcode
 */
API bundle *		bundle_import_from_argv(int argc, char **argv);

/**
 * @brief Adds a string type key-value pair into a bundle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[in]	str The string type value
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_EXISTS	Key already exists
 * @retval BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_get_str()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo", "bar"); // add a key-val pair

 bundle_free(b);
 @endcode
 */
API int bundle_add_str(bundle *b, const char *key, const char *str);

/**
 * @internal
 * @brief Sets a value of string array elements.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[in]	idx The index of the array element to be changed
 * @param[in]	val The string type value; if @c NULL, an empty array is created; you can change an item with
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_add_str_array()
 * @see			bundle_get_str_array()
 @code
 #include <bundle.h>
 bundle *b = bundle_create();
 bundle_add_str_array(b, "foo", NULL, 3); // add a key-val pair
 bundle_set_str_array_element(b, "foo", 0, "aaa");
 bundle_set_str_array_element(b, "foo", 1, "bbb");
 bundle_set_str_array_element(b, "foo", 2, "ccc");

 char **str_array = NULL;
 int len_str_array = 0;

 str_array=bundle_get_str_array(b, "foo", &len_str_array);
 // str_array = { "aaa", "bbb", "ccc" }, and len_str_array = 3

 bundle_free(b);
 @endcode
 */
API int bundle_set_str_array_element(bundle *b, const char *key, const unsigned int idx, const char *val);

/**
 * @brief Adds a byte type key-value pair into a bundle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[in]	byte The string type value
 * @param[in]	size The size of @a byte
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_EXISTS	Key already exists
 * @retval BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_get_byte()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_byte(b, "foo", "bar\0", 4); // add a key-val pair

 int number = 12345;
 bundle_add_byte(b, "number", &number, sizeof(int));

 bundle_free(b);
 @endcode
 */
API int bundle_add_byte(bundle *b, const char *key, const void *byte, const size_t size);

/**
 * @internal
 * @brief Adds a byte array type key-value pair into a bundle.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[in]	byte_array  Not used
 * @param[in]	len The length of the array to be created
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_EXISTS	Key already exists
 * @retval BUNDLE_ERROR_OUT_OF_MEMORY	Out of memory
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_get_byte_array()
 * @see			bundle_set_byte_array_element()
 @code
 #include <bundle.h>
 bundle *b = bundle_create();
 bundle_add_byte_array(b, "foo", NULL, 3); // add a byte-array with length 3

 bundle_set_byte_array_element(b, "foo", 0, "aaa\0", 4);	array[0] = "aaa\0"
 bundle_set_byte_array_element(b, "foo", 1, "bbb\0", 4);	array[1] = "bbb\0"
 bundle_set_byte_array_element(b, "foo", 2, "ccc\0", 4);	array[2] = "ccc\0"

 bundle_free(b);
 @endcode
 */
API int bundle_add_byte_array(bundle *b, const char *key, void **byte_array, const unsigned int len);

/**
 * @internal
 * @brief Sets the value of the byte array element.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[in]	idx The index of the array element to be changed
 * @param[in]	val The string type value; if @c NULL, an empty array is created; you can change an item with
 * @param[in]	size The size of the value in bytes
 * @return		Operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_add_byte_array()
 * @see			bundle_get_byte_array()
 @code
 #include <bundle.h>
 bundle *b = bundle_create();
 bundle_add_byte_array(b, "foo", NULL, 3); // add a key-val pair

 bundle_set_byte_array_element(b, "foo", 0, "aaa\0", 4);
 bundle_set_byte_array_element(b, "foo", 1, "bbb\0", 4);
 bundle_set_byte_array_element(b, "foo", 2, "ccc\0", 4);

 unsigned char **byte_array = NULL;
 int len_byte_array = 0;

 bundle_get_byte_array(b, "foo", &byte_array, &len_byte_array, &size_byte_array);
 // byte_array = { "aaa\0", "bbb\0", "ccc\0" }, and len_byte_array = 3

 bundle_free(b);
 @endcode
 */
API int bundle_set_byte_array_element(bundle *b, const char *key, const unsigned int idx, const void *val, const size_t size);

/**
 * @brief Gets the string value with the given key.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks		You must not free str!
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[out]	str The returned value
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_add_str()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_str(b, "foo_key", "bar_val"); // add a key-val pair

 char *v = NULL;
 bundle_get_str(b, "foo_key", &v);	// v = "bar_val"

 bundle_free(b);	// After freeing b, v becomes a dangling pointer.
 v = NULL;
 @endcode
 */
API int bundle_get_str(bundle *b, const char *key, char **str);

/**
 * @brief Gets the byte value with the given key.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks		You must not free @a byte!
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[out]	byte The returned value
 * @param[out]	size The size of the byte
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_add_byte()
 @code
 #include <bundle.h>
 bundle *b = bundle_create(); // Create new bundle object
 bundle_add_byte(b, "foo", "bar\0", 4); // add string to bundle
 int number = 12345;
 bundle_add_byte(b, "number", (const void**)&number, sizeof(int)); // add integer to bundle

 unsigned char *v = NULL;
 size_t v_size;
 bundle_get_byte(b, "foo", (void**)&v, &v_size);    // v = "bar\0"
 int *n = NULL;
 size_t n_size;
 bundle_get_byte(b, "number", (void**)&n, &n_size); // number = 12345

 bundle_free(b);	// After freeing b, v and n becomes a dangling pointer.
 @endcode
 */
API int bundle_get_byte(bundle *b, const char *key, void **byte, size_t *size);

/**
 * @internal
 * @brief Gets the byte array value with the given key.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @remarks		You must not free str!
 * @param[in]	b	The bundle object
 * @param[in]	key	The key
 * @param[out]	byte_array The returned value
 * @param[out]	len	The array length
 * @param[out]	array_element_size	an array of sizes of each @a byte_array element
 * @return		The operation result
 * @retval BUNDLE_ERROR_NONE	Success
 * @retval BUNDLE_ERROR_INVALID_PARAMETER	Invalid parameter
 * @retval BUNDLE_ERROR_KEY_NOT_AVAILABLE	Key not available
 * @pre			@a b must be a valid bundle object.
 * @see			bundle_add_byte_array()
 * @see			bundle_set_byte_array_element()
 @code
 #include <bundle.h>
 bundle *b = bundle_create();
 bundle_add_byte_array(b, "foo", NULL, 3);
 bundle_set_byte_array_element(b, "foo", 0, "aaa\0", 4);
 bundle_set_byte_array_element(b, "foo", 1, "bbb\0", 4);
 bundle_set_byte_array_element(b, "foo", 2, "ccc\0", 4);

 char **byte_array = NULL;
 int len_byte_array = 0;
 size_t *size_byte_array = NULL;

 bundle_get_byte_array(b, "foo", &byte_array, &len_byte_array, &size_byte_array);
 // byte_array = { "aaa\0", "bbb\0", "ccc\0" }, len_byte_array = 3, and size_byte_array = { 4, 4, 4 }

 bundle_free(b);
 @endcode
 */
API int bundle_get_byte_array(bundle *b, const char *key, void ***byte_array, unsigned int *len, unsigned int **array_element_size);


#ifdef __cplusplus
}
#endif

/**
 * @}
 * @}
 */

#endif	/* __BUNDLE_H__ */
