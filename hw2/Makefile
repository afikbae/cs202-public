# Author : Mehmet Akif Sahin 
# ID: 22203673
# Section : 1
# Homework : 2
# Description : makefile

outputs := output1.txt output2.txt output3.txt output4.txt

build: Simulator.cpp Heap.h Heap.cpp
	g++ -o simulator Simulator.cpp
run: build
	./simulator log1.txt 5 > output1.txt
	./simulator log2.txt 15 > output2.txt
	./simulator log3.txt 46 > output3.txt
	./simulator log3.txt 17 > output4.txt
clean:
	$(RM) simulator $(outputs)
