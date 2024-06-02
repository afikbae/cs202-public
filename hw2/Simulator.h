#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <sstream>

class Simulator {
public:
	struct request {
		int id, priority, request_time, process_time;
		bool operator>( const request& right ) const {
			return priority > right.priority ||
			(priority == right.priority && request_time < right.request_time) ||
			(priority == right.priority && request_time == right.request_time && id < right.id);
		}
		bool operator<( const request& right ) const {
			return priority < right.priority ||
			(priority == right.priority && request_time > right.request_time) ||
			(priority == right.priority && request_time == right.request_time && id > right.id);
		}
	};
	void solve( request* reqs, int n, std::stringstream& out, int target_waiting_time );
};

#endif
