PROGRAMS = counting \
	$(patsubst %.cc,%,$(wildcard sample[0-9][0-9].cc philosophy[0-9][0-9].cc))

all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)
CONFIGMK ?= config.mk

O ?= 3
PTHREAD ?= 1
WANT_TSAN = 1
X86 = 0
include ../common/rules.mk
-include $(CONFIGMK)

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): \
%: %.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS)


clean:
	rm -f $(ALLPROGRAMS) *.o
	rm -f $(wildcard sample[0-9][0-9] philosophy[0-9][0-9])
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all always clean
