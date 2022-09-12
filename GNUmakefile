PROG.fix-music-filenames   = fix-music-filenames
REPORT.fix-music-filenames = fix-music-filenames.report
SRCS.fix-music-filenames   = src/main.cc src/filesystem.cc src/scheme.cc

PROG.test = test
REPORT.test = test.report
SRCS.test = src/scheme.cc unittest/utilsTest.cc \
	unittest/PurchasedStudioSchemeTest.cc \
	unittest/SpacelessSchemeTest.cc \
	unittest/StudioSchemeTest.cc \
	unittest/AbcdeSchemeTest.cc \
	unittest/DefaultSchemeTest.cc

PREFIX   ?= ${HOME}
CXXFLAGS += -g -std=c++20 -D_GLIBCXX_DEBUG -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Iinclude -I$(PREFIX)/include
LDFLAGS  += -L${PREFIX}/lib
LDADD.gtest = -lgtest_maind -lgtestd

INFO      ?= clang-tidy
INFOFLAGS ?= -checks='clang-analyzer-*,misc-*,modernize-*,-modernize-use-trailing-return-type,portability-*,performance-*,readability-*,-readability-identifier-length'

.PHONY: all report clean

all: $(PROG.fix-music-filenames) $(PROG.test)

report: $(REPORT.fix-music-filenames)

clean:
	- rm $(PROG.fix-music-filenames) $(SRCS.fix-music-filenames:.cc=.o) $(SRCS.fix-music-filenames:.cc=.d)
	- rm $(REPORT.fix-music-filenames) $(SRCS.fix-music-filenames:.cc=.info)
	- rm $(PROG.test) $(SRCS.test:.cc=.o) $(SRCS.test:.cc=.d)
	- rm $(REPORT.test) $(SRCS.test:.cc=.info)

#-- specific rules ---
$(PROG.fix-music-filenames): $(SRCS.fix-music-filenames:.cc=.o)
	$(LINK.cc) -o $@ $^ $(LDFLAGS)

$(PROG.test): $(SRCS.test:.cc=.o)
	$(LINK.cc) -o $@ $^ $(LDFLAGS) $(LDADD.gtest)

$(REPORT.fix-music-filenames): $(SRCS.fix-music-filenames:.cc=.info)

$(REPORT.test): $(SRCS.test:.cc=.info)

#-- generic rules ---
%.d: %.cc
	$(CXX) -MM $(CXXFLAGS) $< | sed 's,[^:]*:,$*.o $@ :,g' > $@

%.info: %.cc
	$(INFO) $(INFOFLAGS) $< -- $(CXXFLAGS) > $@

#-- generated inculde file ---
include $(SRCS.fix-music-filenames:.cc=.d) $(SRCS.test:.cc=.d)
