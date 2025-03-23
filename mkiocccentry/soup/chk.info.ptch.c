--- ref/info.reference.json.c	2025-02-22 23:11:48
+++ chk_sem_info.c	2025-02-22 23:55:51
@@ -39,17 +39,17 @@
 
 struct json_sem sem_info[SEM_INFO_LEN+1] = {
 /* depth    type        min     max   count   index  name_len validate  name    data */
-  { 5,	JTYPE_STRING,	1,	72,	72,	0,	0,	NULL,	NULL,	NULL },
+  { 5,	JTYPE_STRING,	10,	72,	72,	0,	0,	NULL,	NULL,	NULL },
   { 4,	JTYPE_MEMBER,	1,	1,	1,	1,	8,	chk_Makefile,	"Makefile",	NULL },
   { 4,	JTYPE_MEMBER,	1,	1,	1,	2,	9,	chk_auth_JSON,	"auth_JSON",	NULL },
   { 4,	JTYPE_MEMBER,	1,	1,	1,	3,	5,	chk_c_src,	"c_src",	NULL },
-  { 4,	JTYPE_MEMBER,	1,	31,	31,	4,	10,	chk_extra_file,	"extra_file",	NULL },
+  { 4,	JTYPE_MEMBER,	0,	31,	31,	4,	10,	chk_extra_file,	"extra_file",	NULL },
   { 4,	JTYPE_MEMBER,	1,	1,	1,	5,	9,	chk_info_JSON,	"info_JSON",	NULL },
   { 4,	JTYPE_MEMBER,	1,	1,	1,	6,	7,	chk_remarks,	"remarks",	NULL },
-  { 3,	JTYPE_OBJECT,	1,	36,	36,	7,	0,	NULL,	NULL,	NULL },
-  { 2,	JTYPE_NUMBER,	1,	7,	7,	8,	0,	NULL,	NULL,	NULL },
-  { 2,	JTYPE_STRING,	1,	50,	50,	9,	0,	NULL,	NULL,	NULL },
-  { 2,	JTYPE_BOOL,	1,	16,	16,	10,	0,	NULL,	NULL,	NULL },
+  { 3,	JTYPE_OBJECT,	5,	36,	36,	7,	0,	NULL,	NULL,	NULL },
+  { 2,	JTYPE_NUMBER,	7,	7,	7,	8,	0,	NULL,	NULL,	NULL },
+  { 2,	JTYPE_STRING,	50,	50,	50,	9,	0,	NULL,	NULL,	NULL },
+  { 2,	JTYPE_BOOL,	16,	16,	16,	10,	0,	NULL,	NULL,	NULL },
   { 2,	JTYPE_ARRAY,	1,	1,	1,	11,	0,	NULL,	NULL,	NULL },
   { 1,	JTYPE_MEMBER,	1,	1,	1,	12,	13,	chk_IOCCC_contest,	"IOCCC_contest",	NULL },
   { 1,	JTYPE_MEMBER,	1,	1,	1,	13,	16,	chk_IOCCC_contest_id,	"IOCCC_contest_id",	NULL },
