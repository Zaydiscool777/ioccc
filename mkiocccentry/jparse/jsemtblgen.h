/*
 * jsemtblgen - generate JSON semantics table
 *
 * "Because specs w/o version numbers are forced to commit to their original design flaws." :-)
 *
 * This JSON parser was co-developed in 2022 by:
 *
 *	@xexyl
 *	https://xexyl.net		Cody Boone Ferguson
 *	https://ioccc.xexyl.net
 * and:
 *	chongo (Landon Curt Noll, http://www.isthe.com/chongo/index.html) /\oo/\
 *
 * "Because sometimes even the IOCCC Judges need some help." :-)
 *
 * The concept of the JSON semantics tables was developed by Landon Curt Noll.
 *
 * "Share and Enjoy!"
 *     --  Sirius Cybernetics Corporation Complaints Division, JSON spec department. :-)
 */

#if !defined(INCLUDE_JSEMTBLGEN_H)
#    define  INCLUDE_JSEMTBLGEN_H


#include <ctype.h>

/*
 * dbg - info, debug, warning, error, and usage message facility
 */
#if defined(INTERNAL_INCLUDE)
#include "../dbg/dbg.h"
#elif defined(INTERNAL_INCLUDE_2)
#include "dbg/dbg.h"
#else
#include <dbg.h>
#endif

/*
 * util - common utility functions for the JSON parser
 */
#include "util.h"

/*
 * dyn_array - dynamic array facility
 */
#if defined(INTERNAL_INCLUDE)
#include "../dyn_array/dyn_array.h"
#elif defined(INTERNAL_INCLUDE_2)
#include "dyn_array/dyn_array.h"
#else
#include <dyn_array.h>
#endif

/*
 * json_util - general JSON parser utility support functions
 */
#include "json_util.h"

/*
 * jparse - JSON parser
 */
#include "jparse.h"

/*
 * version - JSON parser API and tool version
 */
#include "version.h"


/*
 * json_sem - JSON semantics support
 */
#include "json_sem.h"

/*
 * official jsemtblgen version
 */
#define JSEMTBLGEN_VERSION "1.2.0 2024-10-09"		/* format: major.minor YYYY-MM-DD */

/*
 * jsemtblgen tool basename
 */
#define JSEMTBLGEN_BASENAME "jsemtblgen"


/*
 * static functions
 */
static void gen_sem_tbl(struct json *tree, unsigned int max_depth, ...);
static void vupdate_tbl(struct json *node, unsigned int depth, va_list ap);
static int sem_cmp(void const *a, void const *b);
static void print_sem_c_src(struct dyn_array *tbl, char *tbl_name, char *cap_tbl_name);
static void print_sem_h_src(struct dyn_array *tbl, char *tbl_name, char *cap_tbl_name);



#endif /* INCLUDE_JSEMTBLGEN_H */
