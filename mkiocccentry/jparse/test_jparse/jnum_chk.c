/*
 * jnum_chk - tool to check JSON number string conversions
 *
 * "Because specs w/o version numbers are forced to commit to their original design flaws." :-)
 *
 * Copyright (c) 2022-2025 by Cody Boone Ferguson and Landon Curt Noll. All
 * rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright, this permission notice and text
 * this comment, and the disclaimer below appear in all of the following:
 *
 *       supporting documentation
 *       source copies
 *       source works derived from this source
 *       binaries derived from this source or from derived source
 *
 * THE AUTHORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE OR JSON.
 *
 * This JSON parser, library and tools were co-developed in 2022-2025 by Cody Boone
 * Ferguson and Landon Curt Noll:
 *
 *  @xexyl
 *	https://xexyl.net		Cody Boone Ferguson
 *	https://ioccc.xexyl.net
 * and:
 *	chongo (Landon Curt Noll, http://www.isthe.com/chongo/index.html) /\oo/\
 *
 * "Because sometimes even the IOCCC Judges need some help." :-)
 *
 * "Share and Enjoy!"
 *     --  Sirius Cybernetics Corporation Complaints Division, JSON spec department. :-)
 */



/* special comments for the seqcexit tool */
/* exit code out of numerical order - ignore in sequencing - ooo */
/* exit code change of order - use new value in sequencing - coo */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <locale.h>

/*
 * jnum_chk - tool to check JSON number string conversions
 */
#include "jnum_chk.h"


/*
 * definitions
 */
#define REQUIRED_ARGS (0)	/* number of required arguments on the command line */

/*
 * usage message
 *
 * Use the usage() function to print the usage_msg([0-9]?)+ strings.
 */
static const char * const usage_msg =
    "usage: %s [-h] [-v level] [-J level] [-V] [-q] [-S]\n"
    "\n"
    "\t-h\t\tprint help message and exit\n"
    "\t-v level\tset verbosity level (def level: %d)\n"
    "\t-J level\tset JSON verbosity level (def level: %d)\n"
    "\t-V\t\tprint version strings and exit\n"
    "\t-q\t\tquiet mode (def: loud :-) )\n"
    "\t\t\t    NOTE: -q will also silence msg(), warn(), warnp() if -v 0\n"
    "\t-S\t\tstrict testing for all struct json_number elements\n"
    "\t\t\t    (def: test only 8, 16, 32, 64 bit and max size signed and unsigned integer types)\n"
    "\t\t\t    (def: test floating point with match to only 1 part in 4.1943E+06)\n"
    "\n"
    "\tNOTE: the -S mode is for informational purposes only, and may fail\n"
    "\t      on your system due to hardware and/or other system differences.\n"
    "\n"
    "Exit codes:\n"
    "    0\t\tall is OK\n"
    "    1\t\twithout -S given and JSON number conversion test suite failed\n"
    "    2\t\t-S given and JSON number conversion test suite failed\n"
    "    3\t\t-h and help string printed or -V and version strings printed\n"
    "    4\t\tcommand line error\n"
    "    >=10\tinternal error\n"
    "\n"
    "%s version: %s\n"
    "jparse utils version: %s\n"
    "jparse UTF-8 version: %s\n"
    "jparse library version: %s";

/*
 * forward declarations
 */
static void usage(int exitcode, char const *prog, char const *str) __attribute__((noreturn));

int
main(int argc, char *argv[])
{
    char const *program = NULL;	/* our name */
    extern char *optarg;	/* option argument */
    extern int optind;		/* argv index of the next arg */
    bool test = false;		/* true ==> JSON conversion test case result */
    bool error = false;		/* true ==> JSON conversion test suite error */
    bool strict = false;	/* true ==> strict testing for all struct integer element */
    struct json *node = NULL;	/* allocated JSON parser tree node */
    struct json_number *item = NULL;	/* JSON parser tree node for a JSON number */
    size_t len = 0;		/* length of str */
    int arg_count = 0;		/* number of args to process */
    int i;

    /*
     * use default locale based on LANG
     */
    (void) setlocale(LC_ALL, "");

    /*
     * parse args
     */
    program = argv[0];
    while ((i = getopt(argc, argv, ":hv:J:VqS")) != -1) {
	switch (i) {
	case 'h':		/* -h - print help to stderr and exit 0 */
	    usage(2, program, ""); /*ooo*/
	    not_reached();
	    break;
	case 'v':		/* -v verbosity */
	    /*
	     * parse verbosity
	     */
	    verbosity_level = parse_verbosity(optarg);
	    if (verbosity_level < 0) {
		usage(3, program, "invalid -v verbosity"); /*ooo*/
		not_reached();
	    }
	    break;
	case 'J':		/* -J json_verbosity */
	    /*
	     * parse JSON verbosity level
	     */
	    json_verbosity_level = parse_verbosity(optarg);
	    if (verbosity_level < 0) {
		usage(3, program, "invalid -J json_verbosity"); /*ooo*/
		not_reached();
	    }
	    break;
	case 'V':		/* -V - print version strings and exit */
	    print("%s version: %s\n", JNUM_CHK_BASENAME, JNUM_CHK_VERSION);
	    print("jparse utils version: %s\n", JPARSE_UTILS_VERSION);
	    print("jparse UTF-8 version: %s\n", JPARSE_UTF8_VERSION);
	    print("jparse library version: %s\n", JPARSE_LIBRARY_VERSION);
	    exit(2); /*ooo*/
	    not_reached();
	    break;
	case 'q':
	    quiet = true;
	    msg_warn_silent = true;
	    break;
	case 'S':		/* -S - strict mode */
	    strict = true;
	    break;
	case ':':   /* option requires an argument */
	case '?':   /* illegal option */
	default:    /* anything else but should not actually happen */
	    check_invalid_option(program, i, optopt);
	    usage(3, program, ""); /*ooo*/
	    not_reached();
	    break;
	}
    }
    arg_count = argc - optind;
    if (arg_count != REQUIRED_ARGS) {
	usage(3, program, "wrong number of arguments"); /*ooo*/
    }
    dbg(DBG_MED, "strict mode: %s", (strict == true) ? "enabled" : "disabled");

    /*
     * process each test case
     */
    for (i=0; i < test_count; ++i) {

	/*
	 * convert the test string
	 */
	node = json_conv_number_str(test_set[i], &len);
	if (node == NULL) {
	    warn(__func__, "json_conv_number_str(\"%s\", &%ju) returned NULL",
			   test_set[i], (uintmax_t)len);
	    error = true;
	    break;
	}
	if (node->type != JTYPE_NUMBER) {
	    err(10, program, "node->type for test %d: %s != %s", i, json_type_name(node->type), json_type_name(JTYPE_NUMBER));
	    not_reached();
	}
	item = &(node->item.number);

	/*
	 * compare conversion with test case
	 */
	test = chk_test(i, item, &test_result[i], len, strict);
	if (test == false) {
	    warn(__func__, "test: chk_test(%d, item, &test_result[%d], %ju, %s) failed",
			   i, i, (uintmax_t)len, (strict ? "true" : "false"));
	    error = true;
	}

	/*
	 * free converted node
	 */
	json_free(node, 0);
	if (node != NULL) {
	    free(node);
	    node = NULL;
	}
    }

    /*
     * All Done!!! All Done!!! -- Jessica Noll, Age 2
     */
    if (error == true) {
	if (strict == true) {
	    exit(2); /*ooo*/
	} else {
	    exit(1); /*ooo*/
	}
    }
    exit(0); /*ooo*/
}


/*
 * chk_test - check a given test
 *
 * When strict == true, we will compare every node->item.number element
 * with every *test element.  When strict == false, we will only compare
 * select struct json_number elements.
 *
 * given:
 *	testnum - test number being checked
 *	item	- pointer to struct json converted JSON number
 *	test	- pointer to test suite struct json_number
 *	len	- converted JSON number length
 *	strict	- true ==> compare all struct json_member elements,
 *		  false ==> compare only select struct json_member elements
 *
 * returns:
 *	true ==> check passed, no errors (under the given strict value) were found
 *	false ==> some check failed (under the given strict value), or
 *		  NULL pointer given, or len was incorrect
 */
static bool
chk_test(int testnum, struct json_number *item, struct json_number *test, size_t len, bool strict)
{
    bool test_error = false;	/* true ==> check failed */

    /*
     * firewall
     */
    if (item == NULL) {
	warn(__func__, "item is NULL");
	return false;
    }
    if (test == NULL) {
	warn(__func__, "test is NULL");
	return false;
    }
    if (len != test->number_len) {
	warn(__func__, "len: %ju != test->number_len: %ju", (uintmax_t)len, (uintmax_t)test->number_len);
	return false;
    }

    /*
     * test parsed boolean
     */
    if (test_result[testnum].parsed != item->parsed) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].parsed: %d != item.parsed: %d",
		       testnum, test_result[testnum].parsed, item->parsed);
	test_error = true;
    } else {
	dbg(DBG_VVHIGH, "test_result[%d].parsed: %d == item.parsed: %d",
			testnum, test_result[testnum].parsed, item->parsed);
    }

    /*
     * test converted boolean
     */
    if (test_result[testnum].converted != item->converted) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].converted: %d != item.converted: %d",
		       testnum, test_result[testnum].converted, item->converted);
	test_error = true;
    } else {
	dbg(DBG_VVHIGH, "test_result[%d].converted: %d == item.converted: %d",
			testnum, test_result[testnum].converted, item->converted);
    }

    /*
     * test NULL strings
     */
    if (test_result[testnum].as_str == NULL) {
	if (item->as_str != NULL) {
	    dbg(DBG_VHIGH, "ERROR: test_result[%d].as_str == NULL && item->as_str != NULL", testnum);
	    test_error = true;
	} else {
	    dbg(DBG_VVHIGH, "OK: test_result[%d].as_str == NULL && item->as_str == NULL", testnum);
	}
    } else {
	/*
	 * test non-NULL strings
	 */
	if (item->as_str != NULL) {
	    dbg(DBG_VVHIGH, "OK: test_result[%d].as_str != NULL && item->as_str != NULL", testnum);
	} else {
	    dbg(DBG_VHIGH, "ERROR: test_result[%d].as_str != NULL && item->as_str == NULL", testnum);
	    test_error = true;
	}
    }

    /*
     * test string lengths
     */
    if (test_result[testnum].as_str_len != item->as_str_len) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].as_str_len: %ju != item->as_str_len: %ju",
		       testnum, (uintmax_t)test_result[testnum].as_str_len, (uintmax_t)item->as_str_len);
	test_error = true;
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].as_str_len: %ju == item->as_str_len: %ju",
		        testnum, (uintmax_t)test_result[testnum].as_str_len, (uintmax_t)item->as_str_len);
    }
    if (test_result[testnum].number_len != item->number_len) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].number_len: %ju != item->number_len: %ju",
		       testnum, (uintmax_t)test_result[testnum].number_len, (uintmax_t)item->number_len);
	test_error = true;
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].number_len: %ju == item->number_len: %ju",
		        testnum, (uintmax_t)test_result[testnum].number_len, (uintmax_t)item->number_len);
    }

    /*
     * test: other top level booleans
     */
    if (test_result[testnum].is_negative != item->is_negative) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].is_negative: %d != item.is_negative: %d",
		       testnum, test_result[testnum].is_negative, item->is_negative);
	test_error = true;
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].is_negative: %d == item.is_negative: %d",
			testnum, test_result[testnum].is_negative, item->is_negative);
    }
    if (test_result[testnum].is_floating != item->is_floating) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].is_floating: %d != item.is_floating: %d",
		       testnum, test_result[testnum].is_floating, item->is_floating);
	test_error = true;
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].is_floating: %d == item.is_floating: %d",
			testnum, test_result[testnum].is_floating, item->is_floating);
    }
    if (test_result[testnum].is_e_notation != item->is_e_notation) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].is_e_notation: %d != item.is_e_notation: %d",
		       testnum, test_result[testnum].is_e_notation, item->is_e_notation);
	test_error = true;
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].is_e_notation: %d == item.is_e_notation: %d",
			testnum, test_result[testnum].is_e_notation, item->is_e_notation);
    }

    /*
     * perform tests for both strict and non-strict testing of integers
     */

    /* test: int8_t */
    check_val(&test_error, "int8", testnum,
			   test_result[testnum].int8_sized, item->int8_sized,
			   test_result[testnum].as_int8, item->as_int8);

    /* test: uint8_t */
    check_uval(&test_error, "uint8", testnum,
			    test_result[testnum].uint8_sized, item->uint8_sized,
			    test_result[testnum].as_uint8, item->as_uint8);

    /* test: int16_t */
    check_val(&test_error, "int16", testnum,
			   test_result[testnum].int16_sized, item->int16_sized,
			   test_result[testnum].as_int16, item->as_int16);

    /* test: uint16_t */
    check_uval(&test_error, "uint16", testnum,
			    test_result[testnum].uint16_sized, item->uint16_sized,
			    test_result[testnum].as_uint16, item->as_uint16);

    /* test: int32_t */
    check_val(&test_error, "int32", testnum,
			   test_result[testnum].int32_sized, item->int32_sized,
			   test_result[testnum].as_int32, item->as_int32);

    /* test: uint32_t */
    check_uval(&test_error, "uint32", testnum,
			    test_result[testnum].uint32_sized, item->uint32_sized,
			    test_result[testnum].as_uint32, item->as_uint32);

    /* test: int64_t */
    check_val(&test_error, "int64", testnum,
			   test_result[testnum].int64_sized, item->int64_sized,
			   test_result[testnum].as_int64, item->as_int64);

    /* test: uint64_t */
    check_uval(&test_error, "uint64", testnum,
			    test_result[testnum].uint64_sized, item->uint64_sized,
			    test_result[testnum].as_uint64, item->as_uint64);

    /*
     * tests for strict mode only of integers
     */
    if (strict == true) {

	/* test: int */
	check_val(&test_error, "int", testnum,
			       test_result[testnum].int_sized, item->int_sized,
			       test_result[testnum].as_int, item->as_int);

	/* test: unsigned int */
	check_uval(&test_error, "uint", testnum,
				test_result[testnum].uint_sized, item->uint_sized,
				test_result[testnum].as_uint, item->as_uint);

	/* test: long */
	check_val(&test_error, "long", testnum,
			       test_result[testnum].long_sized, item->long_sized,
			       test_result[testnum].as_long, item->as_long);

	/* test: unsigned long */
	check_uval(&test_error, "ulong", testnum,
				test_result[testnum].ulong_sized, item->ulong_sized,
				test_result[testnum].as_ulong, item->as_ulong);

	/* test: long long */
	check_val(&test_error, "longlong", testnum,
			       test_result[testnum].longlong_sized, item->longlong_sized,
			       test_result[testnum].as_longlong, item->as_longlong);

	/* test: unsigned long long */
	check_uval(&test_error, "ulonglong", testnum,
				test_result[testnum].ulonglong_sized, item->ulonglong_sized,
				test_result[testnum].as_ulonglong, item->as_ulonglong);

	/* test: ssize_t */
	check_val(&test_error, "ssize", testnum,
			       test_result[testnum].ssize_sized, item->ssize_sized,
			       test_result[testnum].as_ssize, item->as_ssize);

	/* test: size_t */
	check_uval(&test_error, "size", testnum,
				test_result[testnum].size_sized, item->size_sized,
				test_result[testnum].as_size, item->as_size);

	/* test: off_t */
	check_val(&test_error, "off", testnum,
			       test_result[testnum].off_sized, item->off_sized,
			       test_result[testnum].as_off, item->as_off);
    }

    /*
     * more tests for both strict and non-strict testing of integers
     */

    /* test: intmax_t */
    check_val(&test_error, "intmax", testnum,
			   test_result[testnum].maxint_sized, item->maxint_sized,
			   test_result[testnum].as_maxint, item->as_maxint);

    /* test: uintmax_t */
    check_uval(&test_error, "uintmax", testnum,
			    test_result[testnum].umaxint_sized, item->umaxint_sized,
			    test_result[testnum].as_umaxint, item->as_umaxint);

    /*
     * perform tests for both strict and non-strict testing of floating point
     */

    /* test: float */
    check_fval(&test_error, "float", testnum,
			    test_result[testnum].float_sized, item->float_sized,
			    (double)test_result[testnum].as_float, (double)item->as_float,
			    test_result[testnum].as_float_int, item->as_float_int, strict);

    /* test: double */
    check_fval(&test_error, "double", testnum,
			    test_result[testnum].double_sized, item->double_sized,
			    test_result[testnum].as_double, item->as_double,
			    test_result[testnum].as_double_int, item->as_double_int, strict);

    /* test: long double */
    check_fval(&test_error, "longdouble", testnum,
			    test_result[testnum].longdouble_sized, item->longdouble_sized,
			    test_result[testnum].as_longdouble, item->as_longdouble,
			    test_result[testnum].as_longdouble_int, item->as_longdouble_int, strict);

    /*
     * if this test failed, return false
     */
    if (test_error == true) {
	dbg(DBG_MED, "ERROR: test %d failed", testnum);
	return false;
    }
    dbg(DBG_HIGH, "OK: test %d passed", testnum);
    return true;
}


/*
 * check_val - test an aspect of conversion into struct json_number for signed integer
 *
 * If the reference matches the converted for a given test aspect, this
 * function just returns, else *testp is false.
 *
 * given:
 *	testp	- pointer to set to false if aspect of conversion fails
 *	type	- test aspect name type
 *	testnum	- test number
 *	size_a	- reference (test_result[i]) conversion into type boolean
 *	size_b	- converted (item->) type boolean
 *	val_a	- signed reference (test_result[i]) conversion into type value
 *	val_b	- signed reference (item->) conversion into type value
 *
 * NOTE: This function will warn with a very high debug level on error.
 */
static void
check_val(bool *testp, char const *type, int testnum, bool size_a, bool size_b, intmax_t val_a, intmax_t val_b)
{
    /*
     * firewall
     */
    if (testp == NULL) {
	warn(__func__, "testp is NULL");
	return;
    }
    if (type == NULL) {
	warn(__func__, "type is NULL");
	return;
    }

    /*
     * compare booleans
     */
    if (size_a != size_b) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].%s_sized: %s != item->%s_sized: %s",
		       testnum,
		       type, booltostr(size_a),
		       type, booltostr(size_b));
	*testp = true; /* test failed */
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].%s_sized: %s == item->%s_sized: %s",
		        testnum,
		        type, booltostr(size_a),
		        type, booltostr(size_b));
    }

    /*
     * compare values
     */
    if (size_a == true && val_a != val_b) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].as_%s: %jd != item->as_%s: %jd",
		       testnum,
		       type, val_a,
		       type, val_b);
	*testp = true; /* test failed */
    } else if (size_a == true) {
	dbg(DBG_VVHIGH, "OK: test_result[%d].as_%s: %jd == item->as_%s: %jd",
		        testnum,
		        type, val_a,
		        type, val_b);
    }
    return;
}


/*
 * check_uval - test an aspect of conversion into struct json_number for unsigned integer
 *
 * If the reference matches the converted for a given test aspect, this
 * function just returns, else *testp is false.
 *
 * given:
 *	testp	- pointer to set to false if aspect of conversion fails
 *	type	- test aspect name type
 *	testnum	- test number
 *	size_a	- reference (test_result[i]) conversion into type boolean
 *	size_b	- converted (item->) type boolean
 *	val_a	- unsigned reference (test_result[i]) conversion into type value
 *	val_b	- unsigned reference (item->) conversion into type value
 *
 * NOTE: This function will warn with a very high debug level on error.
 */
static void
check_uval(bool *testp, char const *type, int testnum, bool size_a, bool size_b, uintmax_t val_a, uintmax_t val_b)
{
    /*
     * firewall
     */
    if (testp == NULL) {
	warn(__func__, "testp is NULL");
	return;
    }
    if (type == NULL) {
	warn(__func__, "type is NULL");
	return;
    }

    /*
     * compare booleans
     */
    if (size_a != size_b) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].%s_sized: %s != item->%s_sized: %s",
		       testnum,
		       type, booltostr(size_a),
		       type, booltostr(size_b));
	*testp = true; /* test failed */
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].%s_sized: %s == item->%s_sized: %s",
		        testnum,
		        type, booltostr(size_a),
		        type, booltostr(size_b));
    }

    /*
     * compare values
     */
    if (size_a == true && val_a != val_b) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].as_%s: %ju != item->as_%s: %ju",
		       testnum,
		       type, val_a,
		       type, val_b);
	*testp = true; /* test failed */
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].as_%s: %ju == item->as_%s: %ju",
		        testnum,
		        type, val_a,
		       type, val_b);
    }
    return;
}


/*
 * check_fval - test an aspect of conversion into struct json_number for floating point value
 *
 * If the reference matches the converted for a given test aspect, this
 * function just returns, else *testp is false.
 *
 * given:
 *	testp	- pointer to set to false if aspect of conversion fails
 *	type	- test aspect name type
 *	testnum	- test number
 *	size_a	- reference (test_result[i]) conversion into type boolean
 *	size_b	- converted (item->) type boolean
 *	val_a	- signed reference (test_result[i]) conversion into type value
 *	val_b	- signed reference (item->) conversion into type value
 *	int_a	- reference (test_result[i]) is an integer
 *	int_b	- reference (item->) is an integer
 *	strict	- test for strict match
 *
 * NOTE: This function will warn with a very high debug level on error.
 */
static void
check_fval(bool *testp, char const *type, int testnum, bool size_a, bool size_b,
	  long double val_a, long double val_b, bool int_a, bool int_b, bool strict)
{
    long double diff;		/* absolute difference between val_a and val_b */
    long double diff_part;	/* absolute difference between val_a and val_b as one part of val_a */

    /*
     * firewall
     */
    if (testp == NULL) {
	warn(__func__, "testp is NULL");
	return;
    }
    if (type == NULL) {
	warn(__func__, "type is NULL");
	return;
    }

    /*
     * compare booleans
     */
    if (size_a != size_b) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].%s_sized: %s != item->%s_sized: %s",
		       testnum,
		       type, booltostr(size_a),
		       type, booltostr(size_b));
	*testp = true; /* test failed */
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].%s_sized: %s == item->%s_sized: %s",
		        testnum,
		        type, booltostr(size_a),
		        type, booltostr(size_b));
    }
    if (int_a != int_b) {
	dbg(DBG_VHIGH, "ERROR: test_result[%d].%s_int: %s != item->%s_int: %s",
		       testnum,
		       type, int_a ? "true" : "false",
		       type, int_b ? "true" : "false");
	*testp = true; /* test failed */
    } else {
	dbg(DBG_VVHIGH, "OK: test_result[%d].%s_int: %s == item->%s_int: %s",
		        testnum,
		        type, int_a ? "true" : "false",
		        type, int_b ? "true" : "false");
    }

    /*
     * compare values only if size_a is true
     */
    if (size_a == true) {

	/*
	 * case strict: test for exact match
	 */
	if (strict == true) {
	    if ((intmax_t)val_a != (intmax_t)val_b) {
		dbg(DBG_VHIGH, "ERROR: test_result[%d].as_%s: %.22Lg != item->as_%s: %.22Lg",
			       testnum,
			       type, val_a,
			       type, val_b);
		*testp = true; /* test failed */
	    } else {
		dbg(DBG_VVHIGH, "OK: test_result[%d].as_%s: %.22Lg == item->as_%s: %.22Lg",
				testnum,
				type, val_a,
				type, val_b);
	    }

	/*
	 * case non-strict: test for match to 1 part in MATCH_PRECISION
	 */
	} else {

	    /* determine the difference */
	    diff = fabsl(val_a - val_b);

	    /* determine the difference as part of the whole */
	    if ((intmax_t)val_a != (intmax_t)0.0) {
		diff_part = fabsl(diff / val_a);
	    } else {
		diff_part = diff;	/* zero value special case */
	    }

	    /* compare difference as part of the whole */
	    if (islessequal(diff_part, 1.0L/MATCH_PRECISION)) {
		dbg(DBG_VVHIGH, "OK: test_result[%d].as_%s: %.22Lg similar to item->as_%s: %.22Lg",
				testnum,
				type, val_a,
				type, val_b);
		dbg(DBG_VVHIGH, "OK: test_result[%d].as_%s: diff precision: %.22Lg <= 1.0/MATCH_PRECISION: %.22Lg",
			       testnum,
			       type, diff_part, 1.0L/MATCH_PRECISION);

	    } else {
		dbg(DBG_VHIGH, "ERROR: test_result[%d].as_%s: %.22Lg not similar to item->as_%s: %.22Lg",
			       testnum,
			       type, val_a,
			       type, val_b);
		dbg(DBG_VHIGH, "ERROR: test_result[%d].as_%s: diff precision: %.22Lg > 1.0/MATCH_PRECISION: %.22Lg",
			       testnum,
			       type, diff_part, 1.0L/MATCH_PRECISION);
		*testp = true; /* test failed */
	    }
	}
    }
    return;
}


/*
 * usage - print usage to stderr
 *
 * Example:
 *      usage(3, "missing required argument(s), program: %s", program);
 *
 * given:
 *	exitcode        value to exit with
 *	prog		our program name
 *	str		top level usage message
 *	expected	>= 0 ==> expected args, < 0 ==> ignored
 *	argc		>= 0 ==> argument count, < 0 ==> ignored
 *
 * NOTE: We warn with extra newlines to help internal fault messages stand out.
 *       Normally one should NOT include newlines in warn messages.
 *
 * This function does not return.
 */
static void
usage(int exitcode, char const *prog, char const *str)
{
    /*
     * firewall
     */
    if (prog == NULL) {
	prog = JNUM_CHK_BASENAME;
	warn(__func__, "\nin usage(): prog was NULL, forcing it to be: %s\n", prog);
    }
    if (str == NULL) {
	str = "((NULL str))";
	warn(__func__, "\nin usage(): str was NULL, forcing it to be: %s\n", str);
    }

    if (*str != '\0') {
	fprintf_usage(DO_NOT_EXIT, stderr, "%s", str);
    }
    fprintf_usage(exitcode, stderr, usage_msg, prog, DBG_DEFAULT, JSON_DBG_DEFAULT, JNUM_CHK_BASENAME, JNUM_CHK_VERSION,
	    JPARSE_UTILS_VERSION, JPARSE_UTF8_VERSION, JPARSE_LIBRARY_VERSION);
    exit(exitcode); /*ooo*/
    not_reached();
}
