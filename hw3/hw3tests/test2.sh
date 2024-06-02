#!/bin/bash
for((i=1; i <= 100; ++i)); do
	echo $i
	./gen2 $i > int
	TIME_TAKEN=$( { time ./solution2 int > out1; } 2>&1 | grep real | awk '{print $2}' )
	./brute2 int > out2
	if ! diff -w out1 out2; then
		cat int
		break
	else 
		echo "No differences for iteration $i. Time taken: $TIME_TAKEN"
	fi
done
