AUTOMAKE_OPTIONS=foreign

# Instruct aclocal to check the cfg directory for
# extra macros
ACLOCAL_AMFLAGS=-I config

EXTRA_DIST = include
AM_CXXFLAGS= -I$(top_srcdir)/include/ -std="c++17" -g
bin_PROGRAMS = nova

nova_CXXFLAGS = $(AM_CXXFLAGS)
nova_SOURCES = src/Error.cpp src/Expression.cpp src/Interpreter.cpp src/Lexer.cpp src/ParseHelper.cpp src/Parser.cpp src/Position.cpp src/shell.cpp src/Statement.cpp src/SymbolTable.cpp src/Token.cpp src/types.cpp src/stdfuncs.cpp
