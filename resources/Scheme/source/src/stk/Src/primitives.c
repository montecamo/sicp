/*
 *
 * p r i m i t i v e s . c			-- List of STk subrs
 *
 * Copyright � 1993-1999 Erick Gallesio - I3S-CNRS/ESSI <eg@unice.fr>
 * 
 *
 * Permission to use, copy, modify, distribute,and license this
 * software and its documentation for any purpose is hereby granted,
 * provided that existing copyright notices are retained in all
 * copies and that this notice is included verbatim in any
 * distributions.  No written agreement, license, or royalty fee is
 * required for any of the authorized uses.
 * This software is provided ``AS IS'' without express or implied
 * warranty.
 *
 *           Author: Erick Gallesio [eg@kaolin.unice.fr]
 *    Creation date: ??????
 * Last file update:  3-Sep-1999 20:22 (eg)
 */


#include "stk.h"

struct Primitive {
  char *name;
  char type;
  PRIMITIVE (*fct)();
};

#ifdef USE_HASH
extern PRIMITIVE STk_init_hash(void);
#endif
#ifdef USE_SOCKET
extern PRIMITIVE STk_init_socket(void);
#endif
#ifdef USE_BLT
extern PRIMITIVE STk_init_blt(void);
#endif
#ifdef USE_REGEXP
extern PRIMITIVE STk_init_sregexp(void);
#endif
#ifdef USE_PROCESS
extern PRIMITIVE STk_init_process(void);
#endif
#ifdef USE_POSIX
extern PRIMITIVE STk_init_posix(void);
#endif
#ifdef USE_HTML
extern PRIMITIVE STk_init_html(void);
#endif
#ifdef USE_PIXMAP
extern PRIMITIVE STk_init_pixmap(void);
#endif
#ifdef USE_JPEG
extern PRIMITIVE STk_init_jpeg(void);
#endif
#ifdef USE_BASE64
extern PRIMITIVE STk_init_base64(void);
#endif
#ifdef USE_LOCALE
extern PRIMITIVE STk_init_locale(void);
#endif

#ifdef DEBUG_STK
static PRIMITIVE STk_test_proc(SCM l, int len)
{
  /* This procedure is a placeholder to make tests from the Scheme prompt */
  /* It does not appear in a non debug interpreter			 */


  return UNDEFINED;
}
#endif
  


static struct Primitive Scheme_primitives[] = { 

  /**** Section 4.1 ****/
  {"quote",		    tc_syntax,	    STk_syntax_quote},
  {"lambda",		    tc_syntax,	    STk_syntax_lambda},
  {"if",		    tc_syntax,	    STk_syntax_if},
  {"set!",		    tc_syntax,	    STk_syntax_setq},
  
  /**** Section 4.2 ****/
  {"cond",		    tc_syntax,	    STk_syntax_cond},
  {"and",		    tc_syntax,	    STk_syntax_and},
  {"or",		    tc_syntax,	    STk_syntax_or},
  {"let",		    tc_syntax,	    STk_syntax_let},
  {"let*",		    tc_syntax,	    STk_syntax_letstar},
  {"letrec",		    tc_syntax,	    STk_syntax_letrec},
  {"begin",		    tc_syntax,	    STk_syntax_begin},
  {"delay",		    tc_syntax,	    STk_syntax_delay},
  {"quasiquote",	    tc_syntax,	    STk_syntax_quasiquote},
  {"while",		    tc_fsubr,	    STk_while},		
  {"until",		    tc_fsubr,	    STk_until},		
  {"extend-environment",    tc_syntax,	    STk_syntax_extend_env},	/* + */


  /**** Section 5 ****/
  {"define",		    tc_syntax,	    STk_syntax_define},

  /**** Section 6.1 ****/
  {"boolean?",		    tc_subr_1,      STk_booleanp},
  {"not",		    tc_subr_1,      STk_not},

  /**** Section 6.2 ****/
  {"eq?",		    tc_subr_2,      STk_eq},
  {"eqv?",		    tc_subr_2,      STk_eqv},
  {"equal?",		    tc_subr_2,      STk_equal},

  /**** Section 6.3 ****/
  {"pair?",		    tc_subr_1,      STk_pairp},
  {"cons",		    tc_subr_2,      STk_cons},
  {"car",		    tc_subr_1,      STk_car},
  {"cdr",		    tc_subr_1,      STk_cdr},
  {"set-car!",		    tc_subr_2,      STk_setcar},
  {"set-cdr!",		    tc_subr_2,      STk_setcdr},
  {"caar",		    tc_subr_1,      STk_caar},
  {"cdar",		    tc_subr_1,      STk_cdar},
  {"cadr",		    tc_subr_1,      STk_cadr},
  {"cddr",		    tc_subr_1,      STk_cddr},
  {"caaar",		    tc_subr_1,      STk_caaar},
  {"cdaar",		    tc_subr_1,      STk_cdaar},
  {"cadar",		    tc_subr_1,      STk_cadar},
  {"cddar",		    tc_subr_1,      STk_cddar},
  {"caadr",		    tc_subr_1,      STk_caadr},
  {"cdadr",		    tc_subr_1,      STk_cdadr},
  {"caddr",		    tc_subr_1,      STk_caddr},
  {"cdddr",		    tc_subr_1,      STk_cdddr},
  {"caaaar",		    tc_subr_1,      STk_caaaar},
  {"cdaaar",		    tc_subr_1,      STk_cdaaar},
  {"cadaar",		    tc_subr_1,      STk_cadaar},
  {"cddaar",		    tc_subr_1,      STk_cddaar},
  {"caadar",		    tc_subr_1,      STk_caadar},
  {"cdadar",		    tc_subr_1,      STk_cdadar},
  {"caddar",		    tc_subr_1,      STk_caddar},
  {"cdddar",		    tc_subr_1,      STk_cdddar},
  {"caaadr",		    tc_subr_1,      STk_caaadr},
  {"cdaadr",		    tc_subr_1,      STk_cdaadr},
  {"cadadr",		    tc_subr_1,      STk_cadadr},
  {"cddadr",		    tc_subr_1,      STk_cddadr},
  {"caaddr",		    tc_subr_1,      STk_caaddr},
  {"cdaddr",		    tc_subr_1,      STk_cdaddr},
  {"cadddr",		    tc_subr_1,      STk_cadddr},
  {"cddddr",		    tc_subr_1,      STk_cddddr},
  {"null?",		    tc_subr_1,      STk_nullp},
  {"list?",		    tc_subr_1,      STk_listp},
  {"list",		    tc_lsubr,       STk_list},
  {"length",		    tc_subr_1,      STk_list_length},
  {"append",		    tc_lsubr,       STk_append},
  {"reverse",		    tc_subr_1,      STk_reverse},
  {"list-tail",		    tc_subr_2,      STk_list_tail},
  {"list-ref",		    tc_subr_2,      STk_list_ref},
  {"memq",		    tc_subr_2,      STk_memq},
  {"memv",		    tc_subr_2,      STk_memv},
  {"member",		    tc_subr_2,      STk_member},
  {"assq",		    tc_subr_2,      STk_assq},
  {"assv",		    tc_subr_2,      STk_assv},
  {"assoc",		    tc_subr_2,      STk_assoc},

  {"list*",		    tc_lsubr,       STk_liststar},		/* + */
  {"copy-tree",		    tc_subr_1,	    STk_copy_tree},		/* + */
  {"last-pair",		    tc_subr_1,	    STk_last_pair},		/* + */
  {"remq",		    tc_subr_2,	    STk_remq},			/* + */
  {"remv",		    tc_subr_2,	    STk_remv},			/* + */
  {"remove",		    tc_subr_2,	    STk_remove},		/* + */
  {"append!",		    tc_lsubr,       STk_dappend},		/* + */

  /**** Section 6.4 ****/
  {"symbol?",		    tc_subr_1,	    STk_symbolp},
  {"symbol->string",	    tc_subr_1,	    STk_symbol2string},
  {"string->symbol",	    tc_subr_1,	    STk_string2symbol},
  {"string->uninterned-symbol",						/* + */
   			    tc_subr_1,	    STk_string2usymbol},	

  /**** Section 6.5 ****/
  {"number?",		    tc_subr_1,	    STk_numberp},
  {"complex?",		    tc_subr_1,	    STk_numberp},
  {"real?",		    tc_subr_1,	    STk_numberp},
  {"rational?",		    tc_subr_1,	    STk_numberp},
  {"integer?",		    tc_subr_1,	    STk_integerp},
  {"exact?",		    tc_subr_1,	    STk_exactp},
  {"inexact?",		    tc_subr_1,	    STk_inexactp},
  {"=",			    tc_ssubr,	    STk_numequal},
  {"<",			    tc_ssubr,	    STk_lessp},	  
  {">",			    tc_ssubr,	    STk_greaterp},
  {"<=",		    tc_ssubr,	    STk_lessep},
  {">=",		    tc_ssubr,	    STk_greaterep},
  {"zero?",		    tc_subr_1,	    STk_zerop},
  {"negative?",		    tc_subr_1,	    STk_negativep},
  {"positive?",		    tc_subr_1,	    STk_positivep},
  {"odd?",		    tc_subr_1,	    STk_oddp},
  {"even?",		    tc_subr_1,	    STk_evenp},
  {"max",		    tc_ssubr,	    STk_max},
  {"min",		    tc_ssubr,	    STk_min},
  {"+",			    tc_ssubr,	    STk_plus},
  {"-",			    tc_ssubr,	    STk_difference},
  {"*",			    tc_ssubr,	    STk_times},
  {"/",			    tc_ssubr,	    STk_division},
  {"abs",		    tc_subr_1,	    STk_absolute},
  {"quotient",		    tc_subr_2,	    STk_quotient},
  {"remainder",		    tc_subr_2,	    STk_remainder},
  {"modulo",		    tc_subr_2,	    STk_modulo},
  {"gcd",		    tc_ssubr,	    STk_gcd},
  {"lcm",		    tc_ssubr,	    STk_lcm},
  {"floor",		    tc_subr_1,	    STk_floor},
  {"ceiling",		    tc_subr_1,	    STk_ceiling},
  {"truncate",		    tc_subr_1,	    STk_truncate},
  {"round",		    tc_subr_1,	    STk_round},
  {"exp",		    tc_subr_1,	    STk_exp},
  {"log",		    tc_subr_1,	    STk_log},
  {"sin",		    tc_subr_1,	    STk_sin},
  {"cos",		    tc_subr_1,	    STk_cos},
  {"tan",		    tc_subr_1,	    STk_tan},
  {"asin",		    tc_subr_1,	    STk_asin},
  {"acos",		    tc_subr_1,	    STk_acos},
  {"atan",		    tc_subr_1_or_2, STk_atan},
  {"sqrt",		    tc_subr_1,	    STk_sqrt},
  {"expt",		    tc_subr_2,	    STk_expt},
  {"exact->inexact",	    tc_subr_1,	    STk_exact2inexact},
  {"inexact->exact",	    tc_subr_1,	    STk_inexact2exact},
  {"string->number",	    tc_subr_1_or_2, STk_string2number},
  {"number->string",	    tc_subr_1_or_2, STk_number2string},
  {"bignum?",		    tc_subr_1,	    STk_bignump},		/* + */

  /**** Section 6.6 ****/
  {"char?",		    tc_subr_1,	    STk_charp},

  {"char=?",		    tc_subr_2,	    STk_chareq},
  {"char<?",		    tc_subr_2,	    STk_charless},
  {"char>?",		    tc_subr_2,	    STk_chargt},
  {"char<=?",		    tc_subr_2,	    STk_charlesse},
  {"char>=?",		    tc_subr_2,	    STk_chargte},

  {"char-ci=?",		    tc_subr_2,	    STk_chareqi},
  {"char-ci<?",		    tc_subr_2,	    STk_charlessi},
  {"char-ci>?",		    tc_subr_2,	    STk_chargti},
  {"char-ci<=?",	    tc_subr_2,	    STk_charlessei},
  {"char-ci>=?",	    tc_subr_2,	    STk_chargtei},
  
  {"char-alphabetic?",	    tc_subr_1,	    STk_char_alphap},
  {"char-numeric?",	    tc_subr_1,	    STk_char_numericp},
  {"char-whitespace?",	    tc_subr_1,	    STk_char_whitep},
  {"char-upper-case?",	    tc_subr_1,	    STk_char_upperp},
  {"char-lower-case?",	    tc_subr_1,	    STk_char_lowerp},
  
  {"integer->char",	    tc_subr_1,	    STk_integer2char},
  {"char->integer",	    tc_subr_1,	    STk_char2integer},
  {"char-upcase",	    tc_subr_1,	    STk_char_upper},
  {"char-downcase",	    tc_subr_1,	    STk_char_lower},
 
  /**** Section 6.7 ****/
  {"string?",		    tc_subr_1,	    STk_stringp},

  {"make-string",	    tc_subr_1_or_2, STk_make_string},
  {"string",		    tc_lsubr,	    STk_lstring},
  {"string-length",	    tc_subr_1,	    STk_string_length},
  {"string-ref",	    tc_subr_2,	    STk_string_ref},
  {"string-set!",	    tc_subr_3,	    STk_string_set},

  {"string=?",		    tc_subr_2,	    STk_streq},
  {"string<?",		    tc_subr_2,	    STk_strless},
  {"string>?",		    tc_subr_2,	    STk_strgt},
  {"string<=?",		    tc_subr_2,	    STk_strlesse},
  {"string>=?",		    tc_subr_2,	    STk_strgte},

  {"string-ci=?",	    tc_subr_2,	    STk_streqi},
  {"string-ci<?",	    tc_subr_2,	    STk_strlessi},
  {"string-ci>?",	    tc_subr_2,	    STk_strgti},
  {"string-ci<=?",	    tc_subr_2,	    STk_strlessei},
  {"string-ci>=?",	    tc_subr_2,	    STk_strgtei},

  {"substring",		    tc_subr_3,	    STk_substring},
  {"string-append",	    tc_lsubr,	    STk_string_append},
  {"string->list",	    tc_subr_1,	    STk_string2list},
  {"list->string",	    tc_subr_1,	    STk_list2string},
  {"string-copy",	    tc_subr_1,	    STk_string_copy},
  {"string-fill!",	    tc_subr_2,	    STk_string_fill},

  {"string-find?",	    tc_subr_2,	    STk_string_findp},		/* + */
  {"string-index",	    tc_subr_2,	    STk_string_index},		/* + */
  {"string-lower",	    tc_subr_1,	    STk_string_lower},		/* + */
  {"string-upper",	    tc_subr_1,	    STk_string_upper},		/* + */
  {"split-string",	    tc_subr_1_or_2, STk_split_string},		/* + */

  /**** Section 6.8 ****/
  {"vector?",		    tc_subr_1,	    STk_vectorp},
  {"make-vector",	    tc_subr_1_or_2, STk_make_vector},
  {"vector",		    tc_lsubr,	    STk_vector},
  {"vector-length",	    tc_subr_1,	    STk_vector_length},
  {"vector-ref",	    tc_subr_2,	    STk_vector_ref},
  {"vector-set!",	    tc_subr_3,	    STk_vector_set},
  {"vector->list",	    tc_subr_1,	    STk_vector2list},
  {"list->vector",	    tc_subr_1,	    STk_list2vector},
  {"vector-fill!",	    tc_subr_2,	    STk_vector_fill},

  {"vector-copy",	    tc_subr_1,	    STk_vector_copy},		/* + */
  {"vector-resize",	    tc_subr_2,	    STk_vector_resize},		/* + */

  /**** Section 6.9 ****/
  {"procedure?",	    tc_subr_1,	    STk_procedurep},
  {"apply",		    tc_apply,	    NULL},
  {"map",		    tc_lsubr,	    STk_map},
  {"for-each",		    tc_lsubr,	    STk_for_each},
  {"force",		    tc_subr_1,	    STk_force},
  {"call-with-current-continuation",		
     			    tc_call_cc,	    NULL}, 
  {"values",		    tc_lsubr,	    STk_values},
  {"call-with-values",	    tc_subr_2,      STk_call_with_values},

  {"promise?",	  	    tc_subr_1,	    STk_promisep},		/* + */
  {"continuation?",	    tc_subr_1,	    STk_continuationp},		/* + */
  {"dynamic-wind",	    tc_subr_3,	    STk_dynamic_wind},		/* + */
  {"catch",		    tc_fsubr,	    STk_catch},			/* + */
  {"procedure-body",	    tc_subr_1,	    STk_procedure_body},	/* + */

  /**** Section 6.10 ****/
  {"input-port?",	    tc_subr_1,	    STk_input_portp},
  {"output-port?",	    tc_subr_1,	    STk_output_portp},
  {"current-input-port",    tc_subr_0,	    STk_current_input_port},
  {"current-output-port",   tc_subr_0,	    STk_current_output_port},
  {"with-input-from-file",  tc_subr_2,	    STk_with_input_from_file},
  {"with-output-to-file",   tc_subr_2,	    STk_with_output_to_file},
  {"open-input-file",	    tc_subr_1,	    STk_open_input_file},
  {"open-output-file",	    tc_subr_1,	    STk_open_output_file},
  {"close-input-port",	    tc_subr_1,	    STk_close_input_port},
  {"close-output-port",	    tc_subr_1,	    STk_close_output_port},
  {"read",		    tc_subr_0_or_1, STk_read},
  {"read-char",             tc_subr_0_or_1, STk_read_char},
  {"peek-char",             tc_subr_0_or_1, STk_peek_char},
  {"eof-object?",	    tc_subr_1,	    STk_eof_objectp},
  {"char-ready?",	    tc_subr_0_or_1, STk_char_readyp},
  {"write",		    tc_subr_1_or_2, STk_write},
  {"display",		    tc_subr_1_or_2, STk_display},
  {"newline",		    tc_subr_0_or_1, STk_newline},
  {"write-char",	    tc_subr_1_or_2, STk_write_char},
  {"load",		    tc_subr_1_or_2, STk_load},

  {"input-file-port?",	    tc_subr_1,	    STk_input_file_portp},	/* + */
  {"output-file-port?",	    tc_subr_1,	    STk_output_file_portp},	/* + */
  {"with-input-from-port",  tc_subr_2,	    STk_with_input_from_port},	/* + */
  {"with-output-to-port",   tc_subr_2,	    STk_with_output_to_port},	/* + */
  {"with-error-to-port",    tc_subr_2,	    STk_with_error_to_port},	/* + */
  {"open-file",		    tc_subr_2,	    STk_open_file},		/* + */
  {"close-port",	    tc_subr_1,	    STk_close_port},		/* + */
  {"port-closed?",	    tc_subr_1,	    STk_port_closedp},		/* + */
  {"read-line",		    tc_subr_0_or_1, STk_read_line},		/* + */
  {"copy-port",		    tc_subr_2, 	    STk_copy_port},		/* + */
  {"flush",		    tc_subr_0_or_1, STk_flush},			/* + */
  {"try-load",		    tc_subr_1_or_2, STk_try_load},		/* + */
  {"autoload",		    tc_fsubr,	    STk_autoload},		/* + */
  {"autoload?",		    tc_subr_1_or_2, STk_autoloadp},		/* + */
#if defined(USE_TK) && !defined(WIN32)
  {"when-port-readable",    tc_subr_1_or_2, STk_when_port_readable},	/* + */
  {"when-port-writable",    tc_subr_1_or_2, STk_when_port_writable},	/* + */
#endif
  {"format",		    tc_lsubr,	    STk_format},		/* + */
  {"error",		    tc_lsubr,	    STk_error},			/* + */
  {"write*",		    tc_subr_1_or_2, STk_write_star},		/* + */
  {"input-string-port?",    tc_subr_1,	    STk_input_string_portp},	/* + */
  {"output-string-port?",   tc_subr_1,	    STk_output_string_portp},	/* + */
  {"with-error-to-file",    tc_subr_2,	    STk_with_error_to_file},	/* + */
  {"current-error-port",    tc_subr_0,	    STk_current_error_port},	/* + */
  {"open-input-string",	    tc_subr_1,	    STk_open_input_string},	/* + */
  {"open-output-string",    tc_subr_0,	    STk_open_output_string},	/* + */
  {"get-output-string",	    tc_subr_1,	    STk_get_output_string},	/* + */
  {"with-input-from-string",tc_subr_2,	    STk_with_input_from_string},/* + */
  {"with-output-to-string", tc_subr_1,	    STk_with_output_to_string}, /* + */
  {"with-error-to-string",  tc_subr_1,	    STk_with_error_to_string},  /* + */
  {"read-from-string",	    tc_subr_1,	    STk_read_from_string},	/* + */

  {"open-input-virtual",    tc_lsubr,	    STk_open_input_virtual},	/* + */
  {"open-output-virtual",   tc_lsubr,	    STk_open_output_virtual},	/* + */
  {"input-virtual-port?",   tc_subr_1,	    STk_input_virtual_portp},	/* + */
  {"output-virtual-port?",  tc_subr_1,	    STk_output_virtual_portp},	/* + */
 
  {"transcript-on",         tc_subr_1,	    STk_transcript_on},	/* + */
  {"transcript-off",        tc_subr_0,	    STk_transcript_off},	/* + */
  /**** Section 6.11 ****/
  {"keyword?",		    tc_subr_1,	    STk_keywordp},		/* + */
  {"make-keyword",	    tc_subr_1,	    STk_make_keyword},		/* + */
  {"keyword->string",	    tc_subr_1, 	    STk_keyword2string},	/* + */
  {"get-keyword",	    tc_subr_2_or_3, STk_get_keyword},		/* + */

  /**** Section 6.12 ****/
#ifdef USE_TK
  {"widget->string",	    tc_subr_1,	    STk_widget2string},		/* + */
  {"string->widget",	    tc_subr_1,	    STk_string2widget},		/* + */
  {"tk-command?",	    tc_subr_1,	    STk_tk_commandp},		/* + */
  {"widget-name",	    tc_subr_1,	    STk_widget_name},		/* + */
  {"get-widget-data",	    tc_subr_1,	    STk_get_widget_data},	/* + */
  {"set-widget-data!",	    tc_subr_2,	    STk_set_widget_data},	/* + */
#endif

  /**** Section 6.13 ****/
  {"environment?",	    tc_subr_1,	    STk_environmentp},		/* + */
  {"the-environment",	    tc_fsubr,	    STk_the_environment},	/* + */
  {"parent-environment",    tc_subr_1,	    STk_parent_environment},	/* + */
  {"global-environment",    tc_subr_0,	    STk_global_environment},	/* + */
  {"environment->list",	    tc_subr_1,	    STk_environment2list},	/* + */
  {"procedure-environment", tc_subr_1,	    STk_procedure_environment},	/* + */
  {"symbol-bound?",	    tc_subr_1_or_2, STk_symbol_boundp},		/* + */
  {"eval",		    tc_subr_1_or_2, STk_user_eval},		/* + */
  {"eval-hook",		    tc_subr_3,	    STk_eval_hook},		/* + */
  
  {"define-module",	    tc_fsubr,	    STk_define_module},		/* + */
  {"module?",		    tc_subr_1,	    STk_modulep},		/* + */
  {"with-module",	    tc_fsubr,	    STk_with_module},		/* + */
  {"import",		    tc_fsubr,	    STk_import},		/* + */
  {"export-symbol",	    tc_subr_2,	    STk_export_symbol},		/* + */
  {"export-all-symbols",    tc_subr_0,	    STk_export_all_symbols},	/* + */
  {"select-module",	    tc_fsubr, 	    STk_select_module},		/* + */
  {"current-module",	    tc_fsubr,	    STk_current_module},	/* + */
  {"find-module",	    tc_subr_1_or_2, STk_find_module},		/* + */
  {"module-name",	    tc_subr_1,	    STk_module_name},		/* + */
  {"module-imports",	    tc_subr_1,	    STk_module_imports},	/* + */
  {"module-exports",	    tc_subr_1,	    STk_module_exports},	/* + */
  {"module-environment",    tc_subr_1,	    STk_module_env},		/* + */
  {"module-symbols",	    tc_subr_1,	    STk_module_symbols},	/* + */
  {"all-modules",	    tc_subr_0,	    STk_all_modules},		/* + */
  {"%get-module",	    tc_subr_1,	    STk_get_module},		/* Undoc */

  /**** Section 6.14 ****/
  {"macro",		    tc_fsubr,	    STk_macro},			/* + */
  {"macro?",		    tc_subr_1,	    STk_macrop},		/* + */
  {"macro-expand",	    tc_fsubr,	    STk_macro_expand},		/* + */
  {"macro-expand-1",	    tc_fsubr,	    STk_macro_expand_1},	/* + */
  {"macro-body",	    tc_subr_1,	    STk_macro_body},		/* + */
  {"%macro-r5",		    tc_fsubr,	    STk_macro_R5},		/* Undoc */

  /**** Section 6.15 ****/
  {"address-of",	    tc_subr_1,	    STk_address_of},		/* + */
  {"address?",		    tc_subr_1,	    STk_addressp},		/* + */

  /**** Section 6.16 ****/
  /* Added by brg */
  {"alarm",	    tc_subr_1,	    STk_alarm},		/* + */
  {"try-arbiter",	    tc_subr_1,	    STk_try_arbiter},		/* + */
  {"make-arbiter",	    tc_subr_1,	    STk_make_arbiter},		/* + */
  {"release-arbiter",	    tc_subr_1,	    STk_release_arbiter},	/* + */
  {"set-signal-handler!",   tc_subr_2,	    STk_set_signal_handler},	/* + */
  {"add-signal-handler!",   tc_subr_2, 	    STk_add_signal_handler},	/* + */
  {"get-signal-handlers",   tc_subr_0_or_1, STk_get_signal_handlers},	/* + */
  {"send-signal",	    tc_subr_1,	    STk_send_signal},		/* + */

  /**** Section 6.17 ****/
  {"getcwd",		    tc_subr_0,	    STk_getcwd},		/* + */
  {"chdir",		    tc_subr_1,	    STk_chdir},			/* + */
  {"getpid",		    tc_subr_0,	    STk_getpid},		/* + */
  {"expand-file-name",	    tc_subr_1,	    STk_expand_file_name},	/* + */
  {"canonical-path",	    tc_subr_1,	    STk_canonical_path},	/* + */
  {"system",		    tc_subr_1,	    STk_system},		/* + */
  {"getenv",		    tc_subr_1,	    STk_getenv},		/* + */
  {"setenv!",		    tc_subr_2,	    STk_setenv},		/* + */
  {"file-is-directory?",    tc_subr_1,	    STk_file_is_directoryp},	/* + */
  {"file-is-regular?",      tc_subr_1,	    STk_file_is_regularp},	/* + */
  {"file-is-readable?",     tc_subr_1,	    STk_file_is_readablep},	/* + */
  {"file-is-writable?",     tc_subr_1,	    STk_file_is_writablep},	/* + */
  {"file-is-executable?",   tc_subr_1,	    STk_file_is_executablep},	/* + */
  {"file-exists?",	    tc_subr_1,	    STk_file_existp},		/* + */
  {"glob",		    tc_lsubr,	    STk_file_glob},		/* + */
  {"remove-file",	    tc_subr_1,	    STk_remove_file},		/* + */
  {"rename-file",	    tc_subr_2,	    STk_rename_file},		/* + */
  {"temporary-file-name",   tc_subr_0,	    STk_temporary_file_name},	/* + */


  /**** Section 6.23 (FFI) ****/
  {"%call-external",	    tc_lsubr,	    STk_call_external},		/* Undoc */
  {"%external-exists?",	    tc_subr_2, 	    STk_external_existsp},	/* Undoc */
  {"c-string->string",	    tc_subr_1, 	    STk_cstring2string},	/* + */

  /**** Section 6.24 (Misc) ****/
  {"eval-string",	    tc_subr_1_or_2, STk_eval_string},		/* + */
  {"gc",		    tc_subr_0,	    STk_gc},			/* + */
  {"gc-stats",		    tc_subr_0,	    STk_gc_stats},		/* + */
  {"expand-heap",	    tc_subr_1,	    STk_expand_heap},		/* + */
  {"version",		    tc_subr_0,	    STk_version},		/* + */
  {"machine-type",	    tc_subr_0,	    STk_machine_type},		/* + */
  {"random",		    tc_subr_1,	    STk_random},		/* + */
  {"set-random-seed!",	    tc_subr_1,	    STk_set_random_seed},	/* + */
  {"sort",		    tc_subr_2,	    STk_sort},			/* + */
  {"dump",		    tc_subr_1,	    STk_dump},			/* + */
  {"get-internal-info",	    tc_subr_0,	    STk_get_internal_info},	/* + */
  {"time",		    tc_fsubr,	    STk_time},			/* + */
  {"uncode",		    tc_subr_1,	    STk_uncode},		/* + */
  {"exit",		    tc_subr_0_or_1, STk_quit_interpreter},	/* + */
#ifdef USE_TK
  {"trace-var",		    tc_subr_2,	    STk_trace_var},		/* + */
  {"untrace-var",	    tc_subr_1,	    STk_untrace_var},		/* + */
#endif

  /**** Undocumented primitives */
  {"%get-eval-stack",	    tc_subr_0,	    STk_user_get_eval_stack},	/* Undoc */
  {"%get-environment-stack",tc_subr_0,	    STk_get_env_stack},		/* Undoc */
  {"%library-location",	    tc_subr_0,	    STk_library_location},	/* Undoc */
  {"%procedure-arity",	    tc_subr_1,	    STk_procedure_arity},	/* Undoc */
  {"%get-selected-module",  tc_subr_0,	    STk_get_selected_module},	/* Undoc */
#ifdef USE_TK
  {"%change-standard-ports",tc_subr_3,	    STk_change_standard_ports},	/* Undoc */
#endif
#ifdef DEBUG_STK
  {"%find-cells",	    tc_subr_1,	    STk_find_cells},     /* for debug */
  {"%get-environment",	    tc_subr_1,	    STk_get_environment},/* for debug */
  {"%test-proc",	    tc_lsubr,	    STk_test_proc},	 /* for debug */
#endif


#ifdef USE_STKLOS
  {"%init-stklos",	    tc_subr_0,	    STk_init_STklos},
#endif

#ifdef USE_HASH
  {"%init-hash",	    tc_subr_0,	    STk_init_hash},
#endif
#ifdef USE_SOCKET
  {"%init-socket",	    tc_subr_0,	    STk_init_socket},
#endif
#ifdef USE_BLT
 {"%init-blt",	    	    tc_subr_0,	    STk_init_blt},
#endif 
#ifdef USE_REGEXP
 {"%init-regexp",    	    tc_subr_0,	    STk_init_sregexp},
#endif 
#ifdef USE_PROCESS
 {"%init-process",    	    tc_subr_0,	    STk_init_process},
#endif
#ifdef USE_POSIX
 {"%init-posix",    	    tc_subr_0,	    STk_init_posix},
#endif 
#ifdef USE_HTML
  {"%init-html",	    tc_subr_0,	    STk_init_html},
#endif
#if defined(USE_TK) && defined(USE_PIXMAP)
  {"%init-pixmap",	    tc_subr_0,	    STk_init_pixmap},
#endif
#if defined(USE_TK) && defined(USE_JPEG)
  {"%init-jpeg",	    tc_subr_0,	    STk_init_jpeg},
#endif
#ifdef USE_BASE64
  {"%init-base64",	    tc_subr_0,	    STk_init_base64},
#endif
#ifdef USE_locale
  {"%init-locale",	    tc_subr_0,	    STk_init_locale},
#endif
  { "%clear-recursive-error", tc_subr_0,    STk_clear_recursive_error},
  { "", 0, (SCM (*)()) NULL }
};

void STk_init_primitives(void)
{
  register struct Primitive *p;
  register SCM var, z;

  for (p = Scheme_primitives; *p->name; p++) {
    /* Create a subr cell and store it in both the STk and Scheme modules */
    NEWCELL(z, p->type);
    z->storage_as.subr.name = p->name;
    z->storage_as.subr0.f   = p->fct;

    /* Normal calls should be 
     *    STk_define_variable(p->name, z, STk_scheme_module);
     *    STk_define_variable(p->name, z, NIL);
     * but it sucks; use low level access instead.
     */
    var = Intern(p->name);
    STk_define_public_var(STk_scheme_module, var, z);
    VCELL(var) =  z;
  }
}
