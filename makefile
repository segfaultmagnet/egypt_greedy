# Egypt Greedy
bigint_dir	= $(GIT_REPOS)/bigint
data_dir	= $(GIT_REPOS)/sherim_data
logic_dir	= $(GIT_REPOS)/sherim_logic

bigint_obj	= \
		$(bigint_dir)/BigUnsigned.o \
		$(bigint_dir)/BigInteger.o \
		$(bigint_dir)/BigIntegerAlgorithms.o \
		$(bigint_dir)/BigUnsignedInABase.o \
		$(bigint_dir)/BigIntegerUtils.o \

bigint_head	= \
		$(bigint_dir)/NumberlikeArray.hh \
		$(bigint_dir)/BigUnsigned.hh \
		$(bigint_dir)/BigInteger.hh \
		$(bigint_dir)/BigIntegerAlgorithms.hh \
		$(bigint_dir)/BigUnsignedInABase.hh \
		$(bigint_dir)/BigIntegerLibrary.hh \

data=$(data_dir)/dlist.h
logic=$(logic_dir)/logic.h

all:	greedy

%o:	%.cc
	g++ -std=gnu++11 -c $<

 $(bigint_obj):	$(bigint_head)
bigint_lib:	$(bigint_obj)

greedy.o:	greedy.cpp bigint_lib $(data) $(logic)
	g++ -std=gnu++11 -c greedy.cpp -I$(bigint_dir) -I$(data_dir) -I$(logic_dir)

greedy: greedy.o $(bigint_head) $(data) $(logic)
	g++ -std=gnu++11 -o $@ greedy.o $(bigint_obj) $(bigint_lib) -I$(bigint_dir) -I$(data_dir) -I$(logic_dir)

clean:
	rm -f *.exe
