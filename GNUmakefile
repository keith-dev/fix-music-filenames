PROG.fix-music-filenames   = fix-music-filenames
DEPENDS.fix-music-filenames= fix-music-filenames.depends
REPORT.fix-music-filenames = fix-music-filenames.report
SRCS.fix-music-filenames   = main.cc scheme.cc
PROGS_CXX                  = $(PROG.fix-music-filenames)

PREFIX   ?= ${HOME}
CXXFLAGS += -g -std=c++20 -Wall -Wextra -Wno-unused-parameter -I$(PREFIX)/include
LDFLAGS  += -L${PREFIX}/lib

INFO      ?= clang-tidy
INFOFLAGS ?= -checks='clang-analyzer-*,misc-*,modernize-*,-modernize-use-trailing-return-type,portability-*,readability-*,-readability-identifier-length'

all: $(DEPENDS.fix-music-filenames) $(PROGS_CXX)

report: $(REPORT.fix-music-filenames)

clean:
	- rm $(DEPENDS.fix-music-filenames) $(SRCS.fix-music-filenames:.cc=.depend)
	- rm $(PROG.fix-music-filenames)    $(SRCS.fix-music-filenames:.cc=.o)
	- rm $(REPORT.fix-music-filenames)  $(SRCS.fix-music-filenames:.cc=.info)

#-- specific rules ---
$(PROG.fix-music-filenames): $(SRCS.fix-music-filenames:.cc=.o)
	$(LINK.cc) -o $@ $^ $(LDFLAGS)

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
