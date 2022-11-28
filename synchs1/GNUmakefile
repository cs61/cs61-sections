PROGRAMS = sample01 sample02 sample03 counting

all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)
CONFIGMK ?= config.mk

O ?= 3
PTHREAD ?= 1
include ../common/rules.mk
-include $(CONFIGMK)

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): \
%: %.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS)


clean:
	rm -f $(ALLPROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all always clean
