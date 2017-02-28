## Process this file with automake to produce Makefile.in

## Created by Anjuta



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(BREAKOUT_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = breakout

breakout_SOURCES = \
	main.cc \
	main-window.cc \
	main-window.h \
	graphics.cc \
	graphics.h \
	game-data.cc \
	game-data.h \
	math-vector2-d.cc \
	math-vector2-d.h \
	dir-reader.cc \
	dir-reader.h \
	ball-data.cc \
	ball-data.h \
	paddle-data.cc \
	paddle-data.h \
	brick-data.cc \
	brick-data.h \
	level-data.cc \
	level-data.h \
	collision-model-data.cc \
	collision-model-data.h \
	env-vectorize.h \
	env-vectorize.cc

breakout_LDFLAGS = 

breakout_LDADD = $(BREAKOUT_LIBS)




