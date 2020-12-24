# This sample Makefile allows you to make any SRGP application
#   whose source is exactly one .c file.
#
# To use this Makefile, you must type:
#
#        make PROG=xxxx
#                  ----
# where
#       xxxx.cpp is the name of the file you wish to compile.
#       ----

CC = g++

GCCFLAGS = -fpcc-struct-return
CFLAGS = -g
INCLUDE = -I/usr/include
LDFLAGS = -L/usr/lib/
LDLIBS =  -lGLU -lGL -lglut -lm


$(PROG):
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) $(PROG).cpp game.cpp $(LDFLAGS) $(LDLIBS) -lSOIL -o $(PROG)


clean:
		rm -f *.o $(PROG)
