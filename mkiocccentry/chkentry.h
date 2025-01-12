/*
 * chkentry - check JSON files in an IOCCC submission
 *
 * "Because grammar and syntax alone do not make a complete language." :-)
 *
 * This tool and the JSON parser were co-developed in 2022-2024 by Cody Boone
 * Ferguson and Landon Curt Noll:
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


#if !defined(INCLUDE_CHKENTRY_H)
#    define  INCLUDE_CHKENTRY_H


/*
 * dbg - info, debug, warning, error, and usage message facility
 */
#include "dbg/dbg.h"

/*
 * jparse - the parser
 */
#include "jparse/jparse.h"

/*
 * jparse/version - JSON parser API and tool version
 */
#include "jparse/version.h"


/*
 * soup - some delicious IOCCC soup recipes :-)
 */
#include "soup/soup.h"

/*
 * foo - bar
 */
#include "soup/foo.h"

/*
 * macros
 */

/*
 * chkentry tool basename
 */
#define CHKENTRY_BASENAME "chkentry"

/*
 * externals
 */

/*
 * function prototypes
 */

#endif /* INCLUDE_CHKENTRY_H */
