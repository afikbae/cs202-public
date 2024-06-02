/*
* Author : Mehmet Akif Sahin 
* ID: 22203673
* Section : 1
* Homework : 2
* Description : simulator class implementation file
*/

#include <cstring>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Heap.h"
#include "Simulator.h"

using namespace std;

void Simulator::solve( request* reqs, int n, stringstream& out, int target_waiting_time ) {
	int computer_count = 1;
	double waiting_time = 0;

	do {
		out = stringstream();
		out << "Minimum number of computers required: " << computer_count << endl;
		out << endl;
		out << "Simulation with " << computer_count << " computers:" << endl;
		out << endl;
		// processes[i] = time left for a computer process, if zero means the computer is avaliable
		int* processes = new int[ computer_count ];
		memset( processes, 0, computer_count * sizeof( int ) );
		
		Heap < request > pq (n);
		int time = 1;
		int processed_requests = 0;
		int req_index = 0;
		waiting_time = 0;
		while ( processed_requests < n ) {
			waiting_time += pq.size();
			for ( int computer = 0; computer < computer_count; computer++ ) {
				if ( processes[ computer ] == 1 ) processed_requests++;
				processes[ computer ] = max ( 0, processes[ computer ] - 1 );
			}

			while ( req_index < n && reqs [ req_index ].request_time == time ) {
				pq.push( reqs[ req_index++ ] );
			}
			for ( int computer = 0; computer < computer_count; computer++ ) {
				if ( processes[ computer ] == 0 ) {
					if ( !pq.empty() ) {
						request req = pq.top();
						pq.pop();
						processes[ computer ] = req.process_time + 1;
						out << "Computer " << computer << " takes request " << req.id << " at ms " << time << " (wait: " << time - req.request_time << " ms)" << endl;
					}
				}
			}
			time++;
		}
		waiting_time /= n;
		out << endl;
		out << fixed << setprecision(2);
		out << "Average waiting time: " << waiting_time << " ms" << endl;
		computer_count++;
		delete[] processes;
	} while ( waiting_time > target_waiting_time );
}

int main (int argc, char *argv[]) {
	if ( argc != 3 ) {
		throw runtime_error( "arguments are wrong" );
	}
	int target_waiting_time = stoi( argv[2] );

	ifstream in ( argv[1] );
	int n; in >> n;
	Simulator::request* reqs = new Simulator::request[n];
	for ( int i = 0; i < n; i++ ) {
		in >> reqs[i].id >> reqs[i].priority >> reqs[i].request_time >> reqs[i].process_time;
	}
	stringstream out;
	Simulator sim;
	sim.solve(reqs, n, out, target_waiting_time);
	cout << out.str();
	delete[] reqs;
	return 0;
}		
