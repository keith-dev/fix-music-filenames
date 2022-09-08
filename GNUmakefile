PROG.fix-music-filenames   = fix-music-filenames
DEPENDS.fix-music-filenames= fix-music-filenames.depends
REPORT.fix-music-filenames = fix-music-filenames.report
SRCS.fix-music-filenames   = src/main.cc src/filesystem.cc src/scheme.cc

PROG.test = test
DEPENDSS.test = test.depends
REPORT.test = test.report
SRCS.test = src/scheme.cc unittest/utils_test.cc \
	unittest/DefaultSchemeTest.cc \
	unittest/PurchasedStudioSchemeTest.cc

PROGS_CXX = $(PROG.fix-music-filenames) $(PROG.test)
DEPENDS = $(DEPENDS.fix-music-filenames) $(DEPENDS.test)

PREFIX   ?= ${HOME}
CXXFLAGS += -g -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Iinclude -I$(PREFIX)/include
LDFLAGS  += -L${PREFIX}/lib
LDADD.gtest = -lgtest_maind -lgtestd

INFO      ?= clang-tidy
INFOFLAGS ?= -checks='clang-analyzer-*,misc-*,modernize-*,-modernize-use-trailing-return-type,portability-*,readability-*,-readability-identifier-length'

all: $(DEPENDS) $(PROGS_CXX)

report: $(REPORT.fix-music-filenames)

clean:
	- rm $(DEPENDS.fix-music-filenames) $(SRCS.fix-music-filenames:.cc=.depend)
	- rm $(PROG.fix-music-filenames)    $(SRCS.fix-music-filenames:.cc=.o)
	- rm $(REPORT.fix-music-filenames)  $(SRCS.fix-music-filenames:.cc=.info)
	- rm $(PROG.test) $(SRCS.test:.cc=.o)

#-- specific rules ---
$(PROG.fix-music-filenames): $(SRCS.fix-music-filenames:.cc=.o)
	$(LINK.cc) -o $@ $^ $(LDFLAGS)

$(PROG.test): $(SRCS.test:.cc=.o)
	$(LINK.cc) -o $@ $^ $(LDFLAGS) $(LDADD.gtest)

$(DEPENDS.fix-music-filenames): $(SRCS.fix-music-filenames:.cc=.depend)
	cat $^ > $@

$(REPORT.fix-music-filenames): $(SRCS.fix-music-filenames:.cc=.info)

#-- generic rules ---
%.depend: %.cc
	$(COMPILE.cc) -MM $< -o $@

%.info: %.cc
	$(INFO) $(INFOFLAGS) $< -- $(CXXFLAGS) > $@

#-- generated inculde file ---
-include $(DEPENDS.fix-music-filenames)
