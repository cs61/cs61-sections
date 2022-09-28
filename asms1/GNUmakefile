PROGRAMS = $(sort $(patsubst fun%.cc,fun%,$(wildcard fun[0-9][0-9].cc)) $(patsubst fun%.s,fun%,$(wildcard fun[0-9][0-9].s)))
ALLPROGRAMS = $(PROGRAMS)
FULLSOURCES = $(patsubst fun%.cc,fun%.s,$(sort $(wildcard fun[0-9][0-9].cc)))

all: $(PROGRAMS) $(FULLSOURCES)

O = s
include ../common/rules.mk
LDFLAGS := $(if $(ISLINUX),-no-pie,)

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(filter-out -g,$(CXXFLAGS)) $(O) $(DEPCFLAGS) -o $@ -c $<

%.s: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(filter-out -g,$(CXXFLAGS)) $(O) $(DEPCFLAGS) -o $@ -S $<
	$(call cleanasm,$@)

fundriver.o: fundriver.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

%.o: %.s $(BUILDSTAMP)
	$(call run,$(CXX) -o $@ -c,ASSEMBLE,$<)

fun%: fun%.o fundriver.o
	$(CXX) $(CXXFLAGS) $(O) -o $@ $^ $(LDFLAGS)


clean:
	rm -rf $(DEPSDIR)
	rm -f $(ALLPROGRAMS) *.o $(FULLSOURCES)

.PHONY: all clean
