# build all programs with names like `[sbl][0-9] [sbl][0-9][0-9]`
XPROGRAMS = $(patsubst %.cc,%,$(wildcard [sbl][0-9].cc [sbl][0-9][0-9].cc ll[0-9].cc ll[0-9][0-9].cc))
PROGRAMS = $(XPROGRAMS) hulk
all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS) inv testinsert0 greet1

include ../common/rules.mk

LIBS = -lm


# Rules for making object files (i.e., parts of executables)
# from source files

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<


# Rules for making executables (runnable programs) from object files

$(XPROGRAMS): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)

hulk: \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)


clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)
	rm -rf $(wildcard [sbl][0-9] [sbl][0-9][0-9] ll[0-9] ll[0-9][0-9])

.PHONY: all clean
