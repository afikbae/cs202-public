SHELL := /bin/bash
CXX = g++

cl:
	

gen1:
	$(CXX) gen1.cpp -o gen1

brute1:
	$(CXX) subtask1bruteforcesolution.cpp -o brute1

mysolution1:
	$(CXX) Subtask1.cpp HashTable.cpp -o solution1

test1:	gen1 brute1 mysolution1 
	./test1.sh
	make rmtest1

rmtest1:
	$(RM) gen1 brute1 solution1 int out1 out2

gen2:
	$(CXX) gen2.cpp -o gen2

brute2:
	$(CXX) subtask2bruteforcesolution.cpp -o brute2

mysolution2:
	$(CXX) Subtask2.cpp -o solution2

test2:	gen2 brute2 mysolution2 
	./test2.sh
	make rmtest2

rmtest2:
	$(RM) gen2 brute2 solution2 int out1 out2
gen3:
	$(CXX) gen3.cpp -o gen3

brute3:
	$(CXX) subtask3bruteforcesolution.cpp -o brute3

mysolution3:
	$(CXX) Subtask3.cpp -o solution3

test3:	gen3 brute3 mysolution3 
	./test3.sh
	make rmtest3

rmtest3:
	$(RM) gen3 brute3 solution3 int out1 out2

