
#ifndef RUBY_SFCC_NATIVE
#define RUBY_SFCC_NATIVE

#include <assert.h>

#include <cimc/cimc.h>
#include <cimc/cimcdt.h>
#include <cimc/cimcft.h>
        
#include <ruby.h>
#ifdef HAVE_RUBY_ST_H
# include <ruby/st.h>
#else
# include <st.h>
#endif
#if HAVE_RUBY_THREAD_H /* New threading model */
#include <ruby/thread.h>
#endif

#include <unistd.h>
#include <stdlib.h>

extern const char *to_charptr(VALUE v);
extern VALUE mSfcc;
extern VALUE mSfccCim;
extern CIMCEnv *cimcEnv;
extern char *cimcEnvType;

#define CIMSTR_2_RUBYSTR(x) (x ? (x->ft->getCharPtr(x, NULL) ? rb_str_new2(x->ft->getCharPtr(x, NULL)) : Qnil) : Qnil)

/**
 * raises a ruby exception if the status is an error
 * whenever possible, adds the custom message if not null
 */
void sfcc_rb_raise_if_error(CIMCStatus status, const char *msg, ...);

/**
 * allocates a string array where each string points to the
 * str pointer of the value
 *
 * you need to deallocate the array yourself. But don't deallocate
 * the elements.
 */
char ** sfcc_value_array_to_string_array(VALUE array);

/**
 * converts a CIMCArray to rbArray
 */
VALUE sfcc_cimcarray_to_rubyarray(CIMCArray *array, VALUE client);

/**
 * converts a ruby hash to a CIM args object
 */
CIMCArgs* sfcc_hash_to_cimargs(VALUE hash);

/**
 * converts a CIM args object to a hash
 */
VALUE sfcc_cimargs_to_hash(CIMCArgs *args, VALUE client);

/**
 * allocates a new cimcarray and fills it with converted values of ruby array
 *
 * all elements of array must have the same type,
 *   otherwise TypeError is raised
 * @param type will contain type of array
 *
 * @note nested arrays are not supported
 */
CIMCArray * sfcc_rubyarray_to_cimcarray(VALUE array, CIMCType *type);

/**
 * converts CIMCData to ruby VALUE
 */
VALUE sfcc_cimdata_to_value(CIMCData *data, VALUE client);

/**
 * convert ruby VALUE to CIMCData
 */
CIMCData sfcc_value_to_cimdata(VALUE value);

/**
 * @param v, can be Integer or Float
 * @return ruby String created from ruby number
 */
VALUE sfcc_numeric_to_str(VALUE v);

#endif
