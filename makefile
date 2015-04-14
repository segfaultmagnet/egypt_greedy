# Lab 4
CXX=g++
CXXFLAGS=-std=gnu++11 -g
SRC=greedy.cpp
INC_DATA_DIR=$(GIT_REPOS)/sherim_data
INC_LOGIC_DIR=$(GIT_REPOS)/sherim_logic
INC_DATA=$(INC_DATA_DIR)/dlist.h
INC_LOGIC=$(INC_LOGIC_DIR)/logic.h

all:	greedy

greedy:	$(SRC) $(INC_DATA) $(INC_LOGIC)
	$(CXX) $(CXXFLAGS) -o greedy $(SRC) -I$(INC_DATA_DIR) -I$(INC_LOGIC_DIR)

clean:
	rm *.exe
