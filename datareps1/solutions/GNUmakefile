FMPROGRAMS = $(patsubst %.cc,%,$(wildcard flapmaps[0-9].cc flapmaps[0-9][0-9].cc))
PROGRAMS = $(FMPROGRAMS)
all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

include ../../common/rules.mk

LIBS = -lm


# Rules for making object files (i.e., parts of executables)
# from source files

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

hexdump.o: \
%.o: ../%.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<


# Rules for making executables (runnable programs) from object files

$(FMPROGRAMS): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^ $(LIBS)


clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)

.PHONY: all clean
