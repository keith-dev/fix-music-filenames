PROGS_CXX = fix-music-filenames
PROG.fix-music-filenames = fix-music-filenames
SRCS.fix-music-filenames = main.cc scheme.cc

PREFIX ?= ${HOME}
MK_MAN = no

CXXFLAGS = -g -std=c++20 -Wall -Wextra -Wno-unused-parameter -I${PREFIX}/include
LDFLAGS  = -L${PREFIX}/lib

.include <bsd.progs.mk>
