/*
* Author : Mehmet Akif Sahin
* ID: 22203673
* Section : 3
* Homework : 4
* Description : Pathfinder solution implementation
*/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#include "Queue.cpp"

using namespace std;

struct Edge {
	int to, from;
};

void bft (int** adjList, int n, int* sizes, int destRouter, int sourceRouter, string & path, int & diameter, int*& distances, int*& ways ) {
	bool* visited = new bool[n];
	memset(visited, 0, n * sizeof(bool));

	Queue<int> queue;
	queue.push(sourceRouter);
	visited[sourceRouter] = 1;

	delete[] distances;
	distances = new int[n];
	memset(distances, 0, n * sizeof(int));

	delete[] ways;
	ways = new int[n];
	memset(ways, -1, n * sizeof(int));

	while ( queue.size() > 0 ) {
		int v = queue.peek();
		queue.pop();
		for ( int i = 0; i < sizes[v]; i++ ) {
			int neighbor = adjList[v][i];
			if ( visited[neighbor] ) continue;
			visited[neighbor] = 1;
			distances[neighbor] = distances[v] + 1;
			diameter = distances[neighbor] > diameter ? distances[neighbor] : diameter;
			ways[neighbor] = v;
			queue.push( neighbor );
		}
	}
	delete[] visited;
}

void construct_path ( int destRouter, int sourceRouter, string& path, int& pathLength, int* ways, int n ) {
	pathLength = 2;
	path = to_string(destRouter) + "\n";
	for ( int v = ways[destRouter]; v != sourceRouter; v = ways[v]) {
		if ( v == -1 ) {
			cout << "Cannot find" << endl;
      			return;
		}
		path = to_string(v) + "\n" + path;
		pathLength++;
	}
	path = to_string(sourceRouter) + "\n" + path;
}

void solve (int** adjList, int n, int* sizes, int destRouter, int sourceRouter, string & path, int& pathLength, int & diameter) {
	int* distances = nullptr;
	int* ways = nullptr;
	for ( int i = 0; i < n; i++ ) {
		bft (adjList, n, sizes, destRouter, i, path, diameter, distances, ways );
		if ( i == sourceRouter ) {
			construct_path(destRouter, sourceRouter, path, pathLength, ways, n);
		}
	}
	delete[] distances;
	delete[] ways;
}

int main ( int argc, char *argv[] ) {
	freopen(argv[1], "r", stdin);
	int sourceRouter = stoi( argv[2] );
	int destRouter = stoi( argv[3] );

	int n;
	cin >> n;
	int** adjList = new int*[n];
	int* sizes = new int[n];
	for ( int i = 0; i < n; i++ ) {
		int id;
		cin >> id >> sizes[i];
		adjList[id] = new int[sizes[i]];
		for ( int j = 0; j < sizes[i]; j++ ) {
			cin >> adjList[id][j];
		}
	}

	string path;
	int pathLength;
	int diameter = 0;
	solve( adjList, n, sizes, destRouter, sourceRouter, path, pathLength, diameter);

	cout << "Path consists of " << pathLength << " routers:" << "\n" << path;
	cout << "Diameter of the graph is " << diameter << endl;


	for ( int i = 0; i < n; i++ ) {
		delete[] adjList[i];
	}
	delete[] adjList;
	delete[] sizes;
	fcloseall();
	return 0;
}
