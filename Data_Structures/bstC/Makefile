PROGRAM = bstCTest
FILES.c = test/bstCTest.c src/bstC.c ../lib/unity.c
FILES.h = bstC.h ../lib/unity.h ../lib/unity_internals.h
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

#Uncomment -DDEBUG to show some extra debug information
CFLAGS  = ${SFLAGS} ${GFLAGS} ${OFLAGS} ${WFLAGS} ${UFLAGS} ${DFLAGS} #-DDEBUG
LDFLAGS = -lm
LDLIBS  =

all:    ${PROGRAM}

${PROGRAM}: ${FILES.o}
	${CC} -o $@ ${CFLAGS} ${FILES.o} ${LDFLAGS} ${LDLIBS}

bstCTest.o: ${FILES.h}
bstC.o: ${FILES.h}
unity.o: ${FILES.h}
unity_internals.o: ${FILES.h}

# If it exists, prog1.dSYM is a directory on macOS
DEBRIS = a.out core *~ *.dSYM
RM_FR  = rm -fr

clean:
	${RM_FR} ${FILES.o} ${PROGRAM} ${DEBRIS} test/bstCTest.o test/unity.o

