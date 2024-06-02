/**
* Title: Binary Search Trees
* Author : Mehmet Akif Şahin
* ID: 22203673
* Section : 3
* Homework : 1
* Description : Implementation file for analysis method
*/

#include "analysis.h"
#include "BST.h"
#include <climits>
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>

#define N 10000
#define K 1000

void timeAnalysis() {
	int randomNumbers[N+1];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, N);

	for (int i = 0; i <= N; i++) {
		randomNumbers[i] = 0;
	}

	int last = 0;
	for (int i = 0; i < N; i++) {
		int ran;
		do {
			ran = distrib(gen);
			//std::cerr << "rand " << ran << std::endl;
		} while (randomNumbers[ran] > 0 || ran == last);
		randomNumbers[last] = ran;
		last = ran;
		//std::cerr << i << "-" << last << std::endl;
	}

	clock_t start, stop;
	double times[N/K];
	int heights[N/K];

	BST bst;

	start = clock();

	for (int i = 1; i <= N; i++) {
		if (i % K == 0) {
			stop = clock();
			times[i/K - 1] = (stop - start) / (double) CLOCKS_PER_SEC;
			heights[i/K - 1] = bst.getHeight();
			start = clock();
		}
		bst.insertKey(randomNumbers[i-1], false);
	}

	for (int i = 0; i * 1000 < N; i++) {
		std::cout << (i+1)*K << " " << times[i] << " " << heights[i] << std::endl;
	}

	std::cout << std::endl;
}

//int main() {
//	timeAnalysis();

//	return 0;
//}
