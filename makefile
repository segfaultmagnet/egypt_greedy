# Lab 4
CXX=g++
CXXFLAGS=-std=gnu++11
SRC=greedy.cpp
BIGINT_DIR=$(GIT_REPOS)/bigint
DATA_DIR=$(GIT_REPOS)/sherim_data
LOGIC_DIR=$(GIT_REPOS)/sherim_logic
# BIGINT=$(BIGINT_DIR)/BigIntegerLibrary.o
BIGINT_O= \
	BigUnsigned.o \
	BigInteger.o \
	BigIntegerAlgorithms.o \
	BigUnsignedInABase.o \
	BigIntegerUtils.o \
BIGINT_H= \
	NumberlikeArray.hh \
	BigUnsigned.hh \
	BigInteger.hh \
	BigIntegerAlgorithms.hh \
	BigUnsignedInABase.hh \
	BigIntegerLibrary.hh \
DATA=$(DATA_DIR)/dlist.h
LOGIC=$(LOGIC_DIR)/logic.h

all:

greedy:	$(SRC) $(BIGINT_DIR)/$(BIGINT_LIB) $(DATA) $(LOGIC)
	$(CXX) $(CXXFLAGS) -o greedy $(SRC) -I$(BIGINT_DIR) -I$(DATA_DIR) -I$(LOGIC_DIR)

BIGINT_LIB:     $(BIGINT_O)
BIGINT_O:       $(BIGINT_H)

# $(BIGINT):
# 	make $(BIGINT_DIR)/Makefile

clean:
	rm *.exe
