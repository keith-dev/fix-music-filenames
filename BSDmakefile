PROGS_CXX = fix-music-filenames test

PROG.fix-music-filenames = fix-music-filenames
SRCS.fix-music-filenames = src/main.cc src/filesystem.cc src/scheme.cc

PROG.test = test
SRCS.test = src/scheme.cc unittest/utilsTest.cc \
	unittest/PurchasedStudioSchemeTest.cc \
	unittest/SpacelessSchemeTest.cc \
	unittest/StudioSchemeTest.cc \
	unittest/AbcdeSchemeTest.cc \
	unittest/GenericRipSchemeTest.cc \
	unittest/MultiCdGenericRipSchemeTest.cc \
	unittest/DefaultSchemeTest.cc

PREFIX ?= ${HOME}
MK_MAN = no

CXXFLAGS = -g -std=c++20 -D_GLIBCXX_DEBUG -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Iinclude -I${PREFIX}/include -I/usr/local/include
LDFLAGS  = -L${PREFIX}/lib
LDADD.test = -L/usr/local/lib -lgtest_main -lgtest

.include <bsd.progs.mk>
