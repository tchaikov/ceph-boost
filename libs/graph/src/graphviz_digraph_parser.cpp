/* A Bison parser, made from graphviz_parser.y
   by GNU bison 1.33.  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse bgl_dir_parse
#define bgl_dir_lex bgl_dir_lex
#define bgl_dir_error bgl_dir_error
#define bgl_dir_lval bgl_dir_lval
#define bgl_dir_char bgl_dir_char
#define bgl_dir_debug bgl_dir_debug
#define bgl_dir_nerrs bgl_dir_nerrs
# define	GRAPH_T	257
# define	NODE_T	258
# define	EDGE_T	259
# define	DIGRAPH_T	260
# define	EDGEOP_T	261
# define	SUBGRAPH_T	262
# define	ID_T	263

#line 1 "graphviz_parser.y"

//=======================================================================
// Copyright 2001 University of Notre Dame.
// Author: Lie-Quan Lee
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, University of Notre Dame, Notre
// Dame, IN 46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <boost/config.hpp>
#include <boost/graph/graphviz.hpp>

#if defined BOOST_NO_STRINGSTREAM 
  //#include <strstream> //We cannot use it since there is a bug in strstream  
#include <stdlib.h>
#else
#include <sstream>
#endif

#ifndef GRAPHVIZ_GRAPH
#error Need to define the GRAPHVIZ_GRAPH macro to either GraphvizGraph or GraphvizDigraph.
#endif 

#define YYPARSE_PARAM g

#include "yystype.h"

  extern void bgl_dir_error(char* str);
  extern void bgl_dir_restart(FILE* str);
  extern int bgl_dir_lex(YYSTYPE* lvalp);

  enum AttrState {GRAPH_GRAPH_A, GRAPH_NODE_A, GRAPH_EDGE_A, NODE_A, EDGE_A};

  using boost::GraphvizAttrList;

  namespace graphviz {

    typedef boost::graph_traits<GRAPHVIZ_GRAPH>::vertex_descriptor Vertex;
    typedef boost::graph_traits<GRAPHVIZ_GRAPH>::edge_descriptor   Edge;
    typedef GRAPHVIZ_GRAPH Subgraph;

    static Vertex current_vertex;
    static Edge   current_edge;
    static Subgraph* current_graph = NULL;
    static Subgraph* previous_graph = NULL;

    static std::vector< std::pair<void*, bool>* > vlist;//store a list of rhs 

    static std::map<std::string,std::string> attributes;//store attributes temporarily
    static AttrState attribute_state;

    static std::map<std::string, Subgraph*> subgraphs;  //store the names of subgraphs
    static std::map<std::string, Vertex> nodes;         //store the names of nodes

    typedef std::map<std::string, Subgraph*>::iterator It; 
    typedef std::map<std::string, Vertex>::iterator Iter; 

    static const std::string& get_graph_name(const Subgraph& g) {
      const boost::graph_property<Subgraph, boost::graph_name_t>::type&
	name = boost::get_property(g, boost::graph_name);
      return name; 
    }

    static std::pair<Iter, bool> lookup(const std::string& name) {
      //lookup in the top level
      Iter it = nodes.find(name);
      bool found = (it != nodes.end() );
      return std::make_pair(it, found);
    }
    
    static Vertex add_name(const std::string& name, GRAPHVIZ_GRAPH& g) {
      Vertex v = boost::add_vertex(*current_graph);
      v = current_graph->local_to_global(v);

      //set the label of vertex, it could be overwritten later.
      boost::property_map<GRAPHVIZ_GRAPH, boost::vertex_attribute_t>::type
	va = boost::get(boost::vertex_attribute, g); 
      va[v]["label"] = name; 
      
      //add v into the map so next time we will find it.
      nodes[name] = v; 
      return v;
    }

    static std::pair<It, bool> lookup_subgraph(const std::string& name) {
      It it = subgraphs.find(name);
      bool found = (it != subgraphs.end() );
      return std::make_pair(it, found);
    }
    
    static Subgraph* create_subgraph(const std::string& name) { 

      Subgraph* new_subgraph = &(current_graph->create_subgraph()); 

      subgraphs[name]        = new_subgraph;
      return new_subgraph;
    }

    
    static void set_attribute(GraphvizAttrList& p,
			      const GraphvizAttrList& attr) {
      GraphvizAttrList::const_iterator i, end;
      for ( i=attr.begin(), end=attr.end(); i!=end; ++i)
	p[i->first]=i->second;
    }
  
    static void set_attribute(Subgraph& g,
			      AttrState s, bool clear_attribute = true) {
      typedef Subgraph Graph;
      switch ( s ) {
      case GRAPH_GRAPH_A: 
	{
	  boost::graph_property<Graph, boost::graph_graph_attribute_t>::type&
	    gga = boost::get_property(g, boost::graph_graph_attribute);
	  set_attribute(gga, attributes); 
	}
	break;
      case GRAPH_NODE_A: 
	{
	  boost::graph_property<Graph, boost::graph_vertex_attribute_t>::type&
	    gna = boost::get_property(g, boost::graph_vertex_attribute);
	  set_attribute(gna, attributes); 
	}
	break;
      case GRAPH_EDGE_A: 
	{
	  boost::graph_property<Graph, boost::graph_edge_attribute_t>::type&
	    gea = boost::get_property(g, boost::graph_edge_attribute);
	  set_attribute(gea, attributes); 
	}
	break;
      case NODE_A:
	{
	  boost::property_map<Graph, boost::vertex_attribute_t>::type
	    va = boost::get(boost::vertex_attribute, g);    //va[v]
	  set_attribute(va[current_vertex], attributes);
	}
	break;
      case EDGE_A: 
	{
	  boost::property_map<Graph, boost::edge_attribute_t>::type
	    ea = boost::get(boost::edge_attribute, g);      //ea[e]
	  set_attribute(ea[current_edge], attributes); 
	}
	break;
      }
      if ( clear_attribute )
	attributes.clear();
    }


    static void add_edges(const Vertex& u,
			  const Vertex& v, GRAPHVIZ_GRAPH& g) {
      graphviz::current_edge = boost::add_edge(u, v, g).first; 
      graphviz::set_attribute(g, EDGE_A, false);
    }
    
    static void add_edges(Subgraph* G1, Subgraph* G2,
			  GRAPHVIZ_GRAPH& g) {
      boost::graph_traits<Subgraph>::vertex_iterator i, j, m, n;
      for ( boost::tie(i, j) = boost::vertices(*G1); i != j; ++i) {
	for ( boost::tie(m, n) = boost::vertices(*G2); m != n; ++m) {
	  graphviz::add_edges(G1->local_to_global(*i),
			      G2->local_to_global(*m), g);
	}
      }
    }

    static void add_edges(Subgraph* G, const Vertex& v, GRAPHVIZ_GRAPH& g) {
      boost::graph_traits<Subgraph>::vertex_iterator i, j;
      for ( boost::tie(i, j) = boost::vertices(*G); i != j; ++i) {
	graphviz::add_edges(G->local_to_global(*i), v, g);
      }
    }

    static void add_edges(const Vertex& u, Subgraph* G, GRAPHVIZ_GRAPH& g) {
      boost::graph_traits<Subgraph>::vertex_iterator i, j;
      for ( boost::tie(i, j) = boost::vertices(*G); i != j; ++i) {
	graphviz::add_edges(u, G->local_to_global(*i), g);
      }
    }

    static std::string random_string() {
      static int i=0;
#if defined BOOST_NO_STRINGSTREAM
      //std::strstream out;
      char buf[256];
      sprintf(buf, "default%i\0", i);
      ++i;
      return  string(buf);
#else
      std::stringstream out;
      out << "default" << i;
      ++i;
      return out.str();
#endif
    }


    static void set_graph_name(const std::string& name) {
      boost::graph_property<Subgraph, boost::graph_name_t>::type&
	gea = boost::get_property(*current_graph, boost::graph_name);
      gea = name;
    }

  } //namespace detail {

#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		66
#define	YYFLAG		-32768
#define	YYNTBASE	18

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 263 ? yytranslate[x] : 45)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    17,    12,
       2,    15,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    14,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    10,     2,    11,     2,     2,     2,     2,
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
       6,     7,     8,     9
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     3,     7,    10,    12,    14,    16,    17,    20,
      22,    24,    25,    28,    31,    36,    38,    40,    42,    44,
      48,    52,    54,    56,    57,    59,    61,    63,    65,    67,
      70,    74,    75,    77,    79,    83,    87,    90,    92,    95,
      97,    99,   102,   103,   106,   109,   111
};
static const short yyrhs[] =
{
      20,    19,     0,    10,    23,    11,     0,    21,    22,     0,
       3,     0,     6,     0,     9,     0,     0,    23,    25,     0,
      25,     0,    12,     0,     0,    26,    24,     0,    31,    24,
       0,    27,    13,    28,    14,     0,     3,     0,     4,     0,
       5,     0,    29,     0,    28,    30,    29,     0,     9,    15,
       9,     0,    12,     0,    16,     0,     0,    33,     0,    37,
       0,    32,     0,    41,     0,    29,     0,    35,    34,     0,
      13,    28,    14,     0,     0,     9,     0,    36,     0,     9,
      17,     9,     0,    40,    39,    34,     0,     7,    40,     0,
      38,     0,    39,    38,     0,    35,     0,    41,     0,    43,
      44,     0,     0,    42,    19,     0,     8,     9,     0,    19,
       0,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   246,   249,   252,   262,   262,   265,   265,   268,   268,
     271,   271,   274,   274,   278,   285,   286,   287,   290,   290,
     293,   303,   303,   303,   306,   306,   306,   306,   309,   317,
     328,   328,   331,   346,   349,   368,   413,   417,   417,   420,
     429,   440,   447,   447,   462,   483,   483
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "GRAPH_T", "NODE_T", "EDGE_T", "DIGRAPH_T", 
  "EDGEOP_T", "SUBGRAPH_T", "ID_T", "'{'", "'}'", "';'", "'['", "']'", 
  "'='", "','", "':'", "graph", "graph_body", "graph_header", 
  "graph_type", "graph_name", "stmt_list", "semicolon", "stmt", 
  "attr_stmt", "attr_header", "attr_list", "attr", "attr_separator", 
  "compound_stmt", "graph_attr", "node_stmt", "opt_attr", "node_id", 
  "node_port", "edge_stmt", "edge_rhs_one", "edge_rhs", "edge_endpoint", 
  "subgraph", "@1", "subgraph_header", "opt_graph_body", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    18,    19,    20,    21,    21,    22,    22,    23,    23,
      24,    24,    25,    25,    26,    27,    27,    27,    28,    28,
      29,    30,    30,    30,    31,    31,    31,    31,    32,    33,
      34,    34,    35,    35,    36,    37,    38,    39,    39,    40,
      40,    41,    42,    41,    43,    44,    44
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     2,     3,     2,     1,     1,     1,     0,     2,     1,
       1,     0,     2,     2,     4,     1,     1,     1,     1,     3,
       3,     1,     1,     0,     1,     1,     1,     1,     1,     2,
       3,     0,     1,     1,     3,     3,     2,     1,     2,     1,
       1,     2,     0,     2,     2,     1,     0
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,     4,     5,     0,     7,    42,     1,     6,     3,    15,
      16,    17,     0,    32,    42,     9,    11,     0,    28,    11,
      26,    24,    31,    33,    25,     0,    27,     0,    46,    44,
       0,     0,     2,     8,    10,    12,     0,    13,     0,    29,
      42,    37,    31,    43,    45,    41,    20,    34,     0,    23,
      18,    23,    32,    39,    36,    40,    35,    38,    21,    14,
      22,     0,    30,    19,     0,     0,     0
};

static const short yydefgoto[] =
{
      64,     6,     3,     4,     8,    14,    35,    15,    16,    17,
      49,    18,    61,    19,    20,    21,    39,    22,    23,    24,
      41,    42,    25,    26,    27,    28,    45
};

static const short yypact[] =
{
      23,-32768,-32768,    -4,     6,     9,-32768,-32768,-32768,-32768,
  -32768,-32768,    18,    13,     0,-32768,    19,    21,-32768,    19,
  -32768,-32768,    -6,-32768,-32768,    28,    29,    -4,    -4,-32768,
      30,    31,-32768,-32768,-32768,-32768,    32,-32768,    32,-32768,
      24,-32768,     3,-32768,-32768,-32768,-32768,-32768,    27,     7,
  -32768,     8,    26,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    32,-32768,-32768,    44,    45,-32768
};

static const short yypgoto[] =
{
  -32768,    10,-32768,-32768,-32768,-32768,    33,    34,-32768,-32768,
      11,   -36,-32768,-32768,-32768,-32768,     4,    14,-32768,-32768,
       5,-32768,    15,    16,-32768,-32768,-32768
};


#define	YYLAST		56


static const short yytable[] =
{
      50,   -39,    50,     9,    10,    11,     5,    38,    12,    13,
      40,    32,     9,    10,    11,     7,    38,    12,    13,    58,
      58,    59,    62,    60,    60,    63,     1,    29,    30,     2,
      31,    34,    12,    52,    36,    40,   -40,    43,    44,    46,
      47,    48,    30,    31,    65,    66,    56,    57,    33,    51,
       0,     0,    37,     0,    53,    54,    55
};

static const short yycheck[] =
{
      36,     7,    38,     3,     4,     5,    10,    13,     8,     9,
       7,    11,     3,     4,     5,     9,    13,     8,     9,    12,
      12,    14,    14,    16,    16,    61,     3,     9,    15,     6,
      17,    12,     8,     9,    13,     7,     7,    27,    28,     9,
       9,     9,    15,    17,     0,     0,    42,    42,    14,    38,
      -1,    -1,    19,    -1,    40,    40,    40
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

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
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
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
#define yyclearin	(bgl_dir_char = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call bgl_dir_error.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (bgl_dir_char == YYEMPTY && yylen == 1)				\
    {								\
      bgl_dir_char = (Token);						\
      bgl_dir_lval = (Value);						\
      bgl_dir_char1 = YYTRANSLATE (bgl_dir_char);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      bgl_dir_error ("syntax error: cannot back up");			\
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


/* YYLEX -- calling `bgl_dir_lex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		bgl_dir_lex (&bgl_dir_lval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		bgl_dir_lex (&bgl_dir_lval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		bgl_dir_lex (&bgl_dir_lval, YYLEX_PARAM)
#  else
#   define YYLEX		bgl_dir_lex (&bgl_dir_lval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			bgl_dir_lex ()
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
  if (bgl_dir_debug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int bgl_dir_debug;
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
int bgl_dir_char;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE bgl_dir_lval;						\
							\
/* Number of parse errors so far.  */			\
int bgl_dir_nerrs;

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
  int bgl_dir_char1 = 0;

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
  bgl_dir_nerrs = 0;
  bgl_dir_char = YYEMPTY;		/* Cause a token to be read.  */

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

  /* bgl_dir_char is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (bgl_dir_char == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      bgl_dir_char = YYLEX;
    }

  /* Convert token to internal form (in bgl_dir_char1) for indexing tables with */

  if (bgl_dir_char <= 0)		/* This means end of input. */
    {
      bgl_dir_char1 = 0;
      bgl_dir_char = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      bgl_dir_char1 = YYTRANSLATE (bgl_dir_char);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (bgl_dir_debug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     bgl_dir_char, yytname[bgl_dir_char1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, bgl_dir_char, bgl_dir_lval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += bgl_dir_char1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != bgl_dir_char1)
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
	      bgl_dir_char, yytname[bgl_dir_char1]));

  /* Discard the token being shifted unless it is eof.  */
  if (bgl_dir_char != YYEOF)
    bgl_dir_char = YYEMPTY;

  *++yyvsp = bgl_dir_lval;
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
  if (bgl_dir_debug)
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
#line 249 "graphviz_parser.y"
{yyval.i=0;;
    break;}
case 3:
#line 253 "graphviz_parser.y"
{
    std::string* name = static_cast<std::string*>(yyvsp[0].ptr);
    graphviz::previous_graph = static_cast<graphviz::Subgraph*>(g);
    graphviz::current_graph = static_cast<graphviz::Subgraph*>(g);
    graphviz::set_graph_name(*name);
    delete name;
  ;
    break;}
case 6:
#line 265 "graphviz_parser.y"
{yyval.ptr = yyvsp[0].ptr; ;
    break;}
case 7:
#line 265 "graphviz_parser.y"
{yyval.ptr=(void*)(new std::string("G")); ;
    break;}
case 14:
#line 279 "graphviz_parser.y"
{ 
    graphviz::set_attribute(*graphviz::current_graph,
			  graphviz::attribute_state); 
  ;
    break;}
case 15:
#line 285 "graphviz_parser.y"
{ graphviz::attribute_state = GRAPH_GRAPH_A; ;
    break;}
case 16:
#line 286 "graphviz_parser.y"
{ graphviz::attribute_state = GRAPH_NODE_A; ;
    break;}
case 17:
#line 287 "graphviz_parser.y"
{ graphviz::attribute_state = GRAPH_EDGE_A; ;
    break;}
case 20:
#line 294 "graphviz_parser.y"
{ 
    std::string* name  = static_cast<std::string*>(yyvsp[-2].ptr);
    std::string* value = static_cast<std::string*>(yyvsp[0].ptr);
    graphviz::attributes[*name] = *value; 
    delete name;
    delete value;
  ;
    break;}
case 27:
#line 306 "graphviz_parser.y"
{ yyval.i = 0; ;
    break;}
case 28:
#line 310 "graphviz_parser.y"
{ 
    graphviz::set_attribute(
         *static_cast<graphviz::Subgraph*>(graphviz::current_graph),
			    GRAPH_GRAPH_A);
  ;
    break;}
case 29:
#line 318 "graphviz_parser.y"
{ 
    graphviz::Vertex* temp   = static_cast<graphviz::Vertex*>(yyvsp[-1].ptr); 
    graphviz::current_vertex = *temp;
    graphviz::set_attribute(*static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM),
			    NODE_A); 
    delete temp;
    yyval.i = 0;
  ;
    break;}
case 30:
#line 328 "graphviz_parser.y"
{ yyval.i=0; ;
    break;}
case 31:
#line 328 "graphviz_parser.y"
{ yyval.i=0; ;
    break;}
case 32:
#line 332 "graphviz_parser.y"
{
    std::string* name  = static_cast<std::string*>(yyvsp[0].ptr);
    std::pair<graphviz::Iter, bool> result = graphviz::lookup(*name); 
    if (result.second) {
      graphviz::current_vertex = result.first->second; 
      if (! graphviz::current_graph->is_root())
	boost::add_vertex(graphviz::current_vertex, *graphviz::current_graph);
    } else
      graphviz::current_vertex = graphviz::add_name(*name, *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM)) ; 
    graphviz::Vertex* temp = new graphviz::Vertex(graphviz::current_vertex);
    yyval.ptr = (void *)temp;
    graphviz::attribute_state = NODE_A;  
    delete name;
  ;
    break;}
case 33:
#line 346 "graphviz_parser.y"
{ yyval.ptr=yyvsp[0].ptr; ;
    break;}
case 34:
#line 350 "graphviz_parser.y"
{
    //consider port as a special properties ?? --need work here
    std::string* name = static_cast<std::string*>(yyvsp[-2].ptr);
    std::string* port = static_cast<std::string*>(yyvsp[0].ptr);

    std::pair<graphviz::Iter, bool> result = graphviz::lookup(*name); 
    if (result.second) 
      graphviz::current_vertex = result.first->second; 
    else
      graphviz::current_vertex = graphviz::add_name(*name, *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM)) ; 
    graphviz::Vertex* temp = new graphviz::Vertex(graphviz::current_vertex);
    yyval.ptr = (void *)temp;
    graphviz::attribute_state = NODE_A;  
    delete name;
    delete port;
  ;
    break;}
case 35:
#line 369 "graphviz_parser.y"
{

    typedef std::pair<void*, bool>* Ptr;
    Ptr source = static_cast<Ptr>(yyvsp[-2].ptr);

    for (std::vector<Ptr>::iterator it=graphviz::vlist.begin();
	 it !=graphviz::vlist.end(); ++it) { 
      if ( source->second ) {
	if ( (*it)->second )
	  graphviz::add_edges(static_cast<graphviz::Subgraph*>(source->first),
			    static_cast<graphviz::Subgraph*>((*it)->first),
			    *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
	else
	  graphviz::add_edges(static_cast<graphviz::Subgraph*>(source->first),
			    *static_cast<graphviz::Vertex*>((*it)->first),
			    *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
      } else {
	graphviz::Vertex* temp = static_cast<graphviz::Vertex*>(source->first);
	if ( (*it)->second )
	  graphviz::add_edges(*temp,
			    static_cast<graphviz::Subgraph*>((*it)->first),
			    *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
	else
	  graphviz::add_edges(*temp,
			    *static_cast<graphviz::Vertex*>((*it)->first),
			    *static_cast<GRAPHVIZ_GRAPH*>(YYPARSE_PARAM));
	delete temp;
      }

      delete source; 
      source = *it; 
    } 
    
    if ( ! source->second ) {
      graphviz::Vertex* temp = static_cast<graphviz::Vertex*>(source->first);
      delete temp;
    }
    delete source;

    graphviz::attributes.clear();
    graphviz::vlist.clear(); 
  ;
    break;}
case 36:
#line 414 "graphviz_parser.y"
{ graphviz::vlist.push_back(static_cast<std::pair<void*, bool>*>(yyvsp[0].ptr)); ;
    break;}
case 39:
#line 421 "graphviz_parser.y"
{ 
    std::pair<void*, bool>* temp = new std::pair<void*, bool>;
    temp->first = yyvsp[0].ptr;
    temp->second = false;
    yyval.ptr = (void*)temp;

    graphviz::attribute_state = EDGE_A; 
  ;
    break;}
case 40:
#line 430 "graphviz_parser.y"
{ 
    std::pair<void*, bool>* temp = new std::pair<void*, bool>;
    temp->first = yyvsp[0].ptr;
    temp->second = true;
    yyval.ptr = (void*)temp;

    graphviz::attribute_state = EDGE_A; 
  ;
    break;}
case 41:
#line 441 "graphviz_parser.y"
{
    if ( yyvsp[0].i )
      graphviz::current_graph = &graphviz::current_graph->parent();
    else
      graphviz::current_graph = graphviz::previous_graph;
  ;
    break;}
case 42:
#line 448 "graphviz_parser.y"
{
    graphviz::previous_graph = graphviz::current_graph;
    std::string name = graphviz::random_string();
    graphviz::Subgraph* temp = graphviz::create_subgraph(name);
    graphviz::current_graph = temp;
    graphviz::set_graph_name(name);

    yyval.ptr = (void *) graphviz::current_graph;
  ;
    break;}
case 43:
#line 457 "graphviz_parser.y"
{
    graphviz::current_graph = &graphviz::current_graph->parent();
  ;
    break;}
case 44:
#line 463 "graphviz_parser.y"
{
    //lookup ID_T if it is already in the subgraph,
    //if it is not, add a new subgraph
    std::string* name  = static_cast<std::string*>(yyvsp[0].ptr);

    std::pair<graphviz::It, bool> temp = graphviz::lookup_subgraph(*name);

    graphviz::previous_graph = graphviz::current_graph;
    if ( temp.second )  {//found 
      graphviz::current_graph = (temp.first)->second;
    } else {
      graphviz::current_graph = graphviz::create_subgraph(*name);
      graphviz::set_graph_name(*name);
    }

    yyval.ptr = (void *) graphviz::current_graph;
    delete name;
  ;
    break;}
case 45:
#line 483 "graphviz_parser.y"
{yyval.i = 1; ;
    break;}
case 46:
#line 483 "graphviz_parser.y"
{ yyval.i = 0; ;
    break;}
}

#line 727 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (bgl_dir_debug)
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
      ++bgl_dir_nerrs;

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
	  yysize += yystrlen (yytname[YYTRANSLATE (bgl_dir_char)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (bgl_dir_char)]);

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
	      bgl_dir_error (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    bgl_dir_error ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	bgl_dir_error ("parse error");
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
      if (bgl_dir_char == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  bgl_dir_char, yytname[bgl_dir_char1]));
      bgl_dir_char = YYEMPTY;
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
  if (bgl_dir_debug)
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

  *++yyvsp = bgl_dir_lval;
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
  bgl_dir_error ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 485 "graphviz_parser.y"


namespace boost {
  
  void read_graphviz(const std::string& filename, GRAPHVIZ_GRAPH& g) {
    FILE* file = fopen(filename.c_str(), "r");
    bgl_dir_restart(file);
    void* in = static_cast<void*>(file);
    yyparse(static_cast<void*>(&g));
  }

  void read_graphviz(FILE* file, GRAPHVIZ_GRAPH& g) {
    void* in = static_cast<void*>(file);
    bgl_dir_restart(file);
    yyparse(static_cast<void*>(&g));
  }
    
}

