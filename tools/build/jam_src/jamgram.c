/* A Bison parser, made from jamgram.y
   by GNU bison 1.32.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	_BANG	257
# define	_BANG_EQUALS	258
# define	_AMPERAMPER	259
# define	_LPAREN	260
# define	_RPAREN	261
# define	_PLUS_EQUALS	262
# define	_COLON	263
# define	_SEMIC	264
# define	_LANGLE	265
# define	_LANGLE_EQUALS	266
# define	_EQUALS	267
# define	_RANGLE	268
# define	_RANGLE_EQUALS	269
# define	_QUESTION_EQUALS	270
# define	_LBRACKET	271
# define	_RBRACKET	272
# define	ACTIONS	273
# define	BIND	274
# define	CASE	275
# define	DEFAULT	276
# define	ELSE	277
# define	EXISTING	278
# define	FOR	279
# define	IF	280
# define	IGNORE	281
# define	IN	282
# define	INCLUDE	283
# define	LOCAL	284
# define	MODULE	285
# define	ON	286
# define	PIECEMEAL	287
# define	QUIETLY	288
# define	RETURN	289
# define	RULE	290
# define	SWITCH	291
# define	TOGETHER	292
# define	UPDATED	293
# define	WHILE	294
# define	_LBRACE	295
# define	_BARBAR	296
# define	_RBRACE	297
# define	ARG	298
# define	STRING	299

#line 93 "jamgram.y"

#include "jam.h"

#include "lists.h"
#include "parse.h"
#include "scan.h"
#include "compile.h"
#include "newstr.h"

# define F0 (LIST *(*)(PARSE *, FRAME *))0
# define P0 (PARSE *)0
# define S0 (char *)0

# define pappend( l,r )    	parse_make( compile_append,l,r,P0,S0,S0,0 )
# define pfor( s,l,r,x )    	parse_make( compile_foreach,l,r,P0,s,S0,x )
# define pif( l,r,t )	  	parse_make( compile_if,l,r,t,S0,S0,0 )
# define pwhile( l,r )	  	parse_make( compile_while,l,r,P0,S0,S0,0 )
# define pincl( l )       	parse_make( compile_include,l,P0,P0,S0,S0,0 )
# define plist( s )	  	parse_make( compile_list,P0,P0,P0,s,S0,0 )
# define plocal( l,r,t )  	parse_make( compile_local,l,r,t,S0,S0,0 )
# define pmodule( l,r )	  	parse_make( compile_module,l,r,P0,S0,S0,0 )
# define pnull()	  	parse_make( compile_null,P0,P0,P0,S0,S0,0 )
# define prule( s,p )     	parse_make( compile_rule,p,P0,P0,s,S0,0 )
# define prules( l,r )	  	parse_make( compile_rules,l,r,P0,S0,S0,0 )
# define pset( l,r,a )          parse_make( compile_set,l,r,P0,S0,S0,a )
# define psetmodule( l,r,a ) 	parse_make( compile_set_module,l,r,P0,S0,S0,a )
# define pset1( l,r,t,a )	parse_make( compile_settings,l,r,t,S0,S0,a )
# define psetc( s,p,a,l )     	parse_make( compile_setcomp,p,a,P0,s,S0,l )
# define psete( s,l,s1,f ) 	parse_make( compile_setexec,l,P0,P0,s,s1,f )
# define pswitch( l,r )   	parse_make( compile_switch,l,r,P0,S0,S0,0 )

# define pnode( l,r )    	parse_make( F0,l,r,P0,S0,S0,0 )
# define pcnode( c,l,r )	parse_make( F0,l,r,P0,S0,S0,c )
# define psnode( s,l )     	parse_make( F0,l,P0,P0,s,S0,0 )

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		143
#define	YYFLAG		-32768
#define	YYNTBASE	46

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 299 ? yytranslate[x] : 67)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     3,     5,     7,     9,    12,    18,    19,
      22,    24,    28,    29,    31,    32,    36,    40,    44,    49,
      55,    62,    66,    75,    81,    87,    93,    99,   107,   113,
     114,   115,   125,   127,   129,   131,   134,   136,   140,   144,
     148,   152,   156,   160,   164,   167,   171,   175,   179,   180,
     183,   188,   190,   194,   196,   197,   200,   202,   207,   208,
     211,   213,   215,   217,   219,   221,   223,   224
};
static const short yyrhs[] =
{
      -1,    48,     0,    49,     0,    48,     0,    53,     0,    53,
      48,     0,    30,    61,    50,    10,    47,     0,     0,    13,
      61,     0,    49,     0,     6,    60,     7,     0,     0,    30,
       0,     0,    41,    47,    43,     0,    29,    61,    10,     0,
      44,    60,    10,     0,    63,    56,    61,    10,     0,    31,
      30,    61,    50,    10,     0,    63,    32,    61,    56,    61,
      10,     0,    35,    61,    10,     0,    25,    52,    44,    28,
      61,    41,    47,    43,     0,    37,    61,    41,    58,    43,
       0,    26,    57,    41,    47,    43,     0,    31,    61,    41,
      47,    43,     0,    40,    57,    41,    47,    43,     0,    26,
      57,    41,    47,    43,    23,    53,     0,    52,    36,    44,
      51,    53,     0,     0,     0,    19,    64,    44,    66,    41,
      54,    45,    55,    43,     0,    13,     0,     8,     0,    16,
       0,    22,    13,     0,    63,     0,    63,    13,    63,     0,
      63,     4,    63,     0,    63,    11,    63,     0,    63,    12,
      63,     0,    63,    14,    63,     0,    63,    15,    63,     0,
      63,    28,    61,     0,     3,    57,     0,    57,     5,    57,
       0,    57,    42,    57,     0,     6,    57,     7,     0,     0,
      59,    58,     0,    21,    44,     9,    47,     0,    61,     0,
      61,     9,    60,     0,    62,     0,     0,    62,    63,     0,
      44,     0,    17,    44,    60,    18,     0,     0,    64,    65,
       0,    39,     0,    38,     0,    27,     0,    34,     0,    33,
       0,    24,     0,     0,    20,    61,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   132,   134,   145,   147,   151,   153,   155,   159,   163,
     165,   169,   171,   175,   177,   181,   183,   185,   187,   189,
     191,   193,   195,   197,   199,   201,   203,   205,   207,   209,
     209,   209,   221,   223,   225,   227,   235,   237,   239,   241,
     243,   245,   247,   249,   251,   253,   255,   257,   267,   269,
     273,   282,   284,   294,   298,   300,   304,   306,   316,   318,
     322,   324,   326,   328,   330,   332,   341,   343
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "_BANG", "_BANG_EQUALS", "_AMPERAMPER", 
  "_LPAREN", "_RPAREN", "_PLUS_EQUALS", "_COLON", "_SEMIC", "_LANGLE", 
  "_LANGLE_EQUALS", "_EQUALS", "_RANGLE", "_RANGLE_EQUALS", 
  "_QUESTION_EQUALS", "_LBRACKET", "_RBRACKET", "ACTIONS", "BIND", "CASE", 
  "DEFAULT", "ELSE", "EXISTING", "FOR", "IF", "IGNORE", "IN", "INCLUDE", 
  "LOCAL", "MODULE", "ON", "PIECEMEAL", "QUIETLY", "RETURN", "RULE", 
  "SWITCH", "TOGETHER", "UPDATED", "WHILE", "_LBRACE", "_BARBAR", 
  "_RBRACE", "ARG", "STRING", "run", "block", "rules", "null", 
  "assign_list_opt", "arglist_opt", "local_opt", "rule", "@1", "@2", 
  "assign", "cond", "cases", "case", "lol", "list", "listp", "arg", 
  "eflags", "eflag", "bindlist", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    46,    46,    47,    47,    48,    48,    48,    49,    50,
      50,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      55,    53,    56,    56,    56,    56,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      59,    60,    60,    61,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    65,    65,    65,    66,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     1,     1,     1,     1,     2,     5,     0,     2,
       1,     3,     0,     1,     0,     3,     3,     3,     4,     5,
       6,     3,     8,     5,     5,     5,     5,     7,     5,     0,
       0,     9,     1,     1,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     0,     2,
       4,     1,     3,     1,     0,     2,     1,     4,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     2
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,    58,    14,     0,    54,    54,    54,    54,    54,
       0,     8,    56,     2,     0,     5,     0,    54,     0,    13,
       0,     0,     0,    56,     0,    36,     0,    53,     8,    54,
       0,     0,     0,     0,     0,     4,     3,     0,    51,     0,
       6,    33,    32,    34,     0,    54,    54,     0,    65,    62,
      64,    63,    61,    60,    66,    59,     0,    44,     0,     0,
       8,     0,     0,     0,     0,     0,     0,     0,    54,    16,
      55,    54,    10,     0,     8,     8,    21,    48,     8,    15,
      17,    54,    12,    35,     0,     0,    57,    54,     0,    54,
      47,    45,     0,    46,    38,    39,    40,    37,    41,    42,
      43,     9,     8,     0,     0,     0,     0,    48,     0,    52,
      54,    14,    54,    18,    67,    29,     0,    24,     7,    19,
      25,     0,    23,    49,    26,     0,    28,     0,     0,     8,
      14,     8,    11,    20,    30,     0,    27,    50,     0,    22,
      31,     0,     0,     0
};

static const short yydefgoto[] =
{
     141,    34,    35,    36,    73,   111,    14,    15,   128,   138,
      46,    24,   106,   107,    37,    38,    27,    16,    18,    55,
      88
};

static const short yypact[] =
{
      75,   -34,-32768,   -16,     6,-32768,   -21,   -10,-32768,-32768,
       6,    75,    20,-32768,    -3,    75,   121,-32768,   127,-32768,
     -18,     6,     6,-32768,    11,   135,    25,    -6,    23,-32768,
      -2,    33,     3,    26,     4,-32768,-32768,    38,    49,    15,
  -32768,-32768,-32768,-32768,    47,-32768,-32768,    43,-32768,-32768,
  -32768,-32768,-32768,-32768,    42,-32768,    44,-32768,    14,     6,
      75,     6,    -6,    -6,    -6,    -6,    -6,    -6,-32768,-32768,
  -32768,-32768,-32768,    61,    23,    75,-32768,    53,    75,-32768,
  -32768,-32768,    69,-32768,    57,    67,-32768,-32768,    39,-32768,
  -32768,-32768,    50,    76,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,    75,    85,    54,    52,    56,    53,    59,-32768,
  -32768,   101,-32768,-32768,-32768,-32768,    62,    86,-32768,-32768,
  -32768,    99,-32768,-32768,-32768,   106,-32768,   104,    72,    75,
     101,    75,-32768,-32768,-32768,    78,-32768,-32768,    79,-32768,
  -32768,   123,   124,-32768
};

static const short yypgoto[] =
{
  -32768,   -53,    27,   -20,    51,-32768,   125,   -98,-32768,-32768,
      60,    -4,    28,-32768,   -12,    -5,-32768,    24,-32768,-32768,
  -32768
};


#define	YYLAST		171


static const short yytable[] =
{
      26,    28,    30,    31,    32,    47,    33,    92,    72,    21,
      17,     1,    22,   126,    19,   -13,    59,    57,    58,    59,
      29,    90,   104,     1,    74,   108,    56,    13,    25,   -54,
     -54,    59,   136,    39,    25,    69,    71,   -54,    23,    75,
      84,    85,    40,    76,    77,    25,    25,    79,    80,   118,
      23,    70,    60,    61,    72,    91,    61,    93,    81,    82,
      83,    86,    87,   100,   -54,    41,   101,    78,    61,   109,
      42,   102,    89,    43,   105,   110,   135,   113,   137,    44,
     115,    59,   114,    25,   116,    25,    94,    95,    96,    97,
      98,    99,     1,   117,     2,   119,   121,   120,   125,   122,
       3,     4,   124,   129,     5,     6,     7,   127,   131,   130,
       8,   -14,     9,   132,   133,    10,    11,   134,     1,    12,
       2,   139,   140,   142,   143,   103,     3,     4,    20,    41,
       5,    19,     7,     0,    42,   123,     8,    43,     9,    62,
       0,    10,    11,    44,   112,    12,    63,    64,    65,    66,
      67,    48,     0,    45,    49,     0,     0,     0,     0,     0,
      50,    51,     0,    68,     0,    52,    53,     0,     0,     0,
       0,    54
};

static const short yycheck[] =
{
       5,     6,     7,     8,     9,    17,    10,    60,    28,     3,
      44,    17,     6,   111,    30,    36,     5,    21,    22,     5,
      30,     7,    75,    17,    29,    78,    44,     0,     4,     9,
      10,     5,   130,    36,    10,    10,    13,    17,    44,    41,
      45,    46,    15,    10,    41,    21,    22,    43,    10,   102,
      44,    27,    41,    42,    74,    59,    42,    61,     9,    44,
      13,    18,    20,    68,    44,     8,    71,    41,    42,    81,
      13,    10,    28,    16,    21,     6,   129,    10,   131,    22,
      41,     5,    87,    59,    89,    61,    62,    63,    64,    65,
      66,    67,    17,    43,    19,    10,    44,    43,   110,    43,
      25,    26,    43,    41,    29,    30,    31,   112,     9,    23,
      35,    36,    37,     7,    10,    40,    41,    45,    17,    44,
      19,    43,    43,     0,     0,    74,    25,    26,     3,     8,
      29,    30,    31,    -1,    13,   107,    35,    16,    37,     4,
      -1,    40,    41,    22,    84,    44,    11,    12,    13,    14,
      15,    24,    -1,    32,    27,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    28,    -1,    38,    39,    -1,    -1,    -1,
      -1,    44
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#ifdef __cplusplus
# define YYSTD(x) std::x
#else
# define YYSTD(x) x
#endif

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
#  define YYSIZE_T YYSTD (size_t)
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#    define YYSIZE_T YYSTD (size_t)
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  ifdef __cplusplus
#   include <cstdlib> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T std::size_t
#  else
#   ifdef __STDC__
#    include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#    define YYSIZE_T size_t
#   endif
#  endif
#  define YYSTACK_ALLOC YYSTD (malloc)
#  define YYSTACK_FREE YYSTD (free)
# endif

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Relocate the TYPE STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Type, Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	yymemcpy ((char *) yyptr, (char *) (Stack),			\
		  yysize * (YYSIZE_T) sizeof (Type));			\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (Type) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# ifdef __cplusplus
#  include <cstddef> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T std::size_t
# else
#  ifdef __STDC__
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  ifdef __cplusplus
#   include <cstdio>  /* INFRINGES ON USER NAME SPACE */
#  else
#   include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYFPRINTF YYSTD (fprintf)
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#if ! defined (yyoverflow) && ! defined (yymemcpy)
# if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#  define yymemcpy __builtin_memcpy
# else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
#  if defined (__STDC__) || defined (__cplusplus)
yymemcpy (char *yyto, const char *yyfrom, YYSIZE_T yycount)
#  else
yymemcpy (yyto, yyfrom, yycount)
     char *yyto;
     const char *yyfrom;
     YYSIZE_T yycount;
#  endif
{
  register const char *yyf = yyfrom;
  register char *yyt = yyto;
  register YYSIZE_T yyi = yycount;

  while (yyi-- != 0)
    *yyt++ = *yyf++;
}
# endif
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 341 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# ifdef __cplusplus
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else /* !__cplusplus */
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif /* !__cplusplus */
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (short, yyss);
	YYSTACK_RELOCATE (YYSTYPE, yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (YYLTYPE, yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 2:
#line 135 "jamgram.y"
{ parse_save( yyvsp[0].parse ); }
    break;
case 3:
#line 146 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
case 4:
#line 148 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
case 5:
#line 152 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
case 6:
#line 154 "jamgram.y"
{ yyval.parse = prules( yyvsp[-1].parse, yyvsp[0].parse ); }
    break;
case 7:
#line 156 "jamgram.y"
{ yyval.parse = plocal( yyvsp[-3].parse, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 8:
#line 160 "jamgram.y"
{ yyval.parse = pnull(); }
    break;
case 9:
#line 164 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; yyval.number = ASSIGN_SET; }
    break;
case 10:
#line 166 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; yyval.number = ASSIGN_APPEND; }
    break;
case 11:
#line 170 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 12:
#line 172 "jamgram.y"
{ yyval.parse = P0; }
    break;
case 13:
#line 176 "jamgram.y"
{ yyval.number = 1; }
    break;
case 14:
#line 178 "jamgram.y"
{ yyval.number = 0; }
    break;
case 15:
#line 182 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 16:
#line 184 "jamgram.y"
{ yyval.parse = pincl( yyvsp[-1].parse ); }
    break;
case 17:
#line 186 "jamgram.y"
{ yyval.parse = prule( yyvsp[-2].string, yyvsp[-1].parse ); }
    break;
case 18:
#line 188 "jamgram.y"
{ yyval.parse = pset( yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-2].number ); }
    break;
case 19:
#line 190 "jamgram.y"
{ yyval.parse = psetmodule( yyvsp[-2].parse, yyvsp[-1].parse, yyvsp[-1].number ); }
    break;
case 20:
#line 192 "jamgram.y"
{ yyval.parse = pset1( yyvsp[-5].parse, yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-2].number ); }
    break;
case 21:
#line 194 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 22:
#line 196 "jamgram.y"
{ yyval.parse = pfor( yyvsp[-5].string, yyvsp[-3].parse, yyvsp[-1].parse, yyvsp[-6].number ); }
    break;
case 23:
#line 198 "jamgram.y"
{ yyval.parse = pswitch( yyvsp[-3].parse, yyvsp[-1].parse ); }
    break;
case 24:
#line 200 "jamgram.y"
{ yyval.parse = pif( yyvsp[-3].parse, yyvsp[-1].parse, pnull() ); }
    break;
case 25:
#line 202 "jamgram.y"
{ yyval.parse = pmodule( yyvsp[-3].parse, yyvsp[-1].parse ); }
    break;
case 26:
#line 204 "jamgram.y"
{ yyval.parse = pwhile( yyvsp[-3].parse, yyvsp[-1].parse ); }
    break;
case 27:
#line 206 "jamgram.y"
{ yyval.parse = pif( yyvsp[-5].parse, yyvsp[-3].parse, yyvsp[0].parse ); }
    break;
case 28:
#line 208 "jamgram.y"
{ yyval.parse = psetc( yyvsp[-2].string, yyvsp[0].parse, yyvsp[-1].parse, yyvsp[-4].number ); }
    break;
case 29:
#line 210 "jamgram.y"
{ yymode( SCAN_STRING ); }
    break;
case 30:
#line 212 "jamgram.y"
{ yymode( SCAN_NORMAL ); }
    break;
case 31:
#line 214 "jamgram.y"
{ yyval.parse = psete( yyvsp[-6].string,yyvsp[-5].parse,yyvsp[-2].string,yyvsp[-7].number ); }
    break;
case 32:
#line 222 "jamgram.y"
{ yyval.number = ASSIGN_SET; }
    break;
case 33:
#line 224 "jamgram.y"
{ yyval.number = ASSIGN_APPEND; }
    break;
case 34:
#line 226 "jamgram.y"
{ yyval.number = ASSIGN_DEFAULT; }
    break;
case 35:
#line 228 "jamgram.y"
{ yyval.number = ASSIGN_DEFAULT; }
    break;
case 36:
#line 236 "jamgram.y"
{ yyval.parse = pcnode( COND_EXISTS, yyvsp[0].parse, pnull() ); }
    break;
case 37:
#line 238 "jamgram.y"
{ yyval.parse = pcnode( COND_EQUALS, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 38:
#line 240 "jamgram.y"
{ yyval.parse = pcnode( COND_NOTEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 39:
#line 242 "jamgram.y"
{ yyval.parse = pcnode( COND_LESS, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 40:
#line 244 "jamgram.y"
{ yyval.parse = pcnode( COND_LESSEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 41:
#line 246 "jamgram.y"
{ yyval.parse = pcnode( COND_MORE, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 42:
#line 248 "jamgram.y"
{ yyval.parse = pcnode( COND_MOREEQ, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 43:
#line 250 "jamgram.y"
{ yyval.parse = pcnode( COND_IN, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 44:
#line 252 "jamgram.y"
{ yyval.parse = pcnode( COND_NOT, yyvsp[0].parse, P0 ); }
    break;
case 45:
#line 254 "jamgram.y"
{ yyval.parse = pcnode( COND_AND, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 46:
#line 256 "jamgram.y"
{ yyval.parse = pcnode( COND_OR, yyvsp[-2].parse, yyvsp[0].parse ); }
    break;
case 47:
#line 258 "jamgram.y"
{ yyval.parse = yyvsp[-1].parse; }
    break;
case 48:
#line 268 "jamgram.y"
{ yyval.parse = P0; }
    break;
case 49:
#line 270 "jamgram.y"
{ yyval.parse = pnode( yyvsp[-1].parse, yyvsp[0].parse ); }
    break;
case 50:
#line 274 "jamgram.y"
{ yyval.parse = psnode( yyvsp[-2].string, yyvsp[0].parse ); }
    break;
case 51:
#line 283 "jamgram.y"
{ yyval.parse = pnode( P0, yyvsp[0].parse ); }
    break;
case 52:
#line 285 "jamgram.y"
{ yyval.parse = pnode( yyvsp[0].parse, yyvsp[-2].parse ); }
    break;
case 53:
#line 295 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; yymode( SCAN_NORMAL ); }
    break;
case 54:
#line 299 "jamgram.y"
{ yyval.parse = pnull(); yymode( SCAN_PUNCT ); }
    break;
case 55:
#line 301 "jamgram.y"
{ yyval.parse = pappend( yyvsp[-1].parse, yyvsp[0].parse ); }
    break;
case 56:
#line 305 "jamgram.y"
{ yyval.parse = plist( yyvsp[0].string ); }
    break;
case 57:
#line 307 "jamgram.y"
{ yyval.parse = prule( yyvsp[-2].string, yyvsp[-1].parse ); }
    break;
case 58:
#line 317 "jamgram.y"
{ yyval.number = 0; }
    break;
case 59:
#line 319 "jamgram.y"
{ yyval.number = yyvsp[-1].number | yyvsp[0].number; }
    break;
case 60:
#line 323 "jamgram.y"
{ yyval.number = EXEC_UPDATED; }
    break;
case 61:
#line 325 "jamgram.y"
{ yyval.number = EXEC_TOGETHER; }
    break;
case 62:
#line 327 "jamgram.y"
{ yyval.number = EXEC_IGNORE; }
    break;
case 63:
#line 329 "jamgram.y"
{ yyval.number = EXEC_QUIETLY; }
    break;
case 64:
#line 331 "jamgram.y"
{ yyval.number = EXEC_PIECEMEAL; }
    break;
case 65:
#line 333 "jamgram.y"
{ yyval.number = EXEC_EXISTING; }
    break;
case 66:
#line 342 "jamgram.y"
{ yyval.parse = pnull(); }
    break;
case 67:
#line 344 "jamgram.y"
{ yyval.parse = yyvsp[0].parse; }
    break;
}

#line 727 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 348 "jamgram.y"
