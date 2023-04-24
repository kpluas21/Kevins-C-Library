PROGRAM = DynamiCTest
FILES.c = test/DynamiCTest.c src/DynamiC.c ../lib/unity.c
FILES.h = DynamiC.h ../lib/unity.h ../lib/unity_internals.h
FILES.o = ${FILES.c:.c=.o}

CC = gcc
SFLAGS = -std=c99
GFLAGS = -g
OFLAGS = -O0
DFLAGS = -I/src
WFLAG1  = -Wall
WFLAG2  = -Wextra
WFLAG3  = -Werror
WFLAG4  = -Wstrict-prototypes
WFLAG5  = -Wmissing-prototypes
WFLAGS  = ${WFLAG1} ${WFLAG2} ${WFLAG3} ${WFLAG4} ${WFLAG5} 
UFLAGS  = # Set on command line only

CFLAGS  = ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS} ${UFLAGS} ${DFLAGS}
LDFLAGS = -lm
LDLIBS  =

all:    ${PROGRAM}

${PROGRAM}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

DynamiCTest.o: ${FILES.h}
DynamiC.o: ${FILES.h}
unity.o: ${FILES.h}
unity_internals.o: ${FILES.h}

# If it exists, prog1.dSYM is a directory on macOS
DEBRIS = a.out core *~ *.dSYM
RM_FR  = rm -fr

clean:
	${RM_FR} ${FILES.o} ${PROGRAM} ${DEBRIS} test/DynamiCTest.o test/unity.o

TEST = ./DynamiCTest

test:
	${TEST}
