# Egypt Greedy
cxx		= g++
cxxflags	= -std=gnu++11 -w

bigint_dir	= $(GIT_REPOS)/bigint
data_dir	= $(GIT_REPOS)/sherim_data
logic_dir	= $(GIT_REPOS)/sherim_logic

bigint_cc	= \
		$(bigint_dir)/BigUnsigned.cc \
		$(bigint_dir)/BigInteger.cc \
		$(bigint_dir)/BigIntegerAlgorithms.cc \
		$(bigint_dir)/BigUnsignedInABase.cc \
		$(bigint_dir)/BigIntegerUtils.cc \

bigint_hh	= \
		$(bigint_dir)/NumberlikeArray.hh \
		$(bigint_dir)/BigUnsigned.hh \
		$(bigint_dir)/BigInteger.hh \
		$(bigint_dir)/BigIntegerAlgorithms.hh \
		$(bigint_dir)/BigUnsignedInABase.hh \
		$(bigint_dir)/BigIntegerLibrary.hh \

data_cpp	= $(data_dir)/dlist.cpp
data_h		= $(data_dir)/dlist.h
logic_cpp	= $(logic_dir)/logic.cpp
logic_h		= $(logic_dir)/logic.h

deps		= \
		$(bigint_cc) \
		$(bigint_hh) \
		$(data_cpp) \
		$(data_h) \
		$(logic_cpp) \
		$(logic_h) \

src		= greedy.cpp

all:	greedy

greedy: $(src) $(deps)
	$(cxx) $(cxxflags) -o $@ $(src) $(deps) -I$(bigint_dir) -I$(data_dir) -I$(logic_dir)

clean:
	rm -f greedy.exe
