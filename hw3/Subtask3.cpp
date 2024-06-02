/**
* Title: Hash Table
* Author : Mehmet Akif Şahin
* ID: 22203673 
* Section : 3
* Homework : 3
* Description : Subtask3 solution
*/

#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

#define int long long

struct triplet {
	int hash1, hash2, oldIndex;
};

bool operator <(const triplet& x, const triplet& y) {
    return x.hash1 < y.hash1 || (x.hash1 == y.hash1 && x.hash2 < y.hash2);
}

bool operator ==(const triplet& x, const triplet& y) {
    return x.hash1 == y.hash1 && x.hash2 == y.hash2;
}

int charToVal( char c ) {
	return ( c | 32 ) - 'a' + 1;
}

int fp(int a, int b, int modulo) {
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * fp(a, b - 1, modulo)) % modulo;
    int half = fp(a, b/2, modulo);
    return (half * half) % modulo;
}

int computeHash ( string& item, int mod ) {
	int hash = 0;
	int p = 31;
	for ( int i = 0; i < item.length(); i++ ) {
		hash *= p;
		hash = ( hash + mod ) % mod;
		hash += charToVal( item[i] );
		hash = ( hash + mod ) % mod;
	}

	int minHash = hash;

	int power = fp( p, item.length() - 1, mod );

	for ( int i = 0; i < item.length(); i++ ) {
		hash -= ( power * charToVal( item[i] ) ) % mod;
		hash = ( hash + mod ) % mod;
		hash *= p;
		hash = ( hash + mod ) % mod;
		hash += charToVal( item[i] );
		hash = ( hash + mod ) % mod;
		if ( hash < minHash ) {
			minHash = hash;
		}
	}

	return minHash;
}

int find (triplet * arr, int n, triplet item ) {
	int lo = 0, hi = n - 1, ans = -1;
	while ( lo <= hi ) {
		int mid = ( hi + lo ) / 2;
		if ( arr[mid] < item ) {
			lo = mid + 1;
		} else if ( item == arr[mid] ) {
			ans = mid;
			hi = mid - 1;
		} else {
			hi = mid - 1;
		}
	}
	return ans;
}

string reverseString ( const string& str ) {
	string reverse;
	reverse.resize( str.length() );
	for ( int i = 0; i < str.length(); i++ ) {
		reverse[ reverse.length() - i - 1] = str[i];
	}
	return reverse;
}

void solve ( string*& strs, int n, int& numberOfReverse, int& sizeOfMinimalSubset ) {
	int mod1 = 1000000007;
	int mod2 = 1000000009;
	triplet* hashes  = new triplet[ n ];

	for ( int i = 0; i < n; i++ ) {
		int hash1 = computeHash( strs[i], mod1 );
		int hash2 = computeHash( strs[i], mod2 );
		hashes[i] = {hash1, hash2, i};
	}

	sort( hashes, hashes + n );

	int* counts = new int[n];
	memset( counts, -1, n * sizeof(int) );

	for ( int i = 0; i < n; ) {
		int hash1 = hashes[i].hash1;
		int hash2 = hashes[i].hash2;
		int start = i;
		int end = i + 1;
		while ( end < n && hash1 == hashes[end].hash1 && hash2 == hashes[end].hash2 ) end++;
		if ( counts[start] > 0 ) {
			numberOfReverse += counts[start] > end - start ? end - start : counts[start];
		} else {
			sizeOfMinimalSubset++;
			string reverseStr = reverseString(strs[hashes[start].oldIndex]);
			int reverseHash1 = computeHash( reverseStr, mod1);
			int reverseHash2 = computeHash( reverseStr, mod2);
			int reverseStart = find( hashes, n, {reverseHash1, reverseHash2, 0} );
			if ( reverseStart != -1 )
				counts[reverseStart] = end - start;
		}
		i = end;
	}
	delete[] hashes;
	delete[] counts;
}

int32_t main ( int32_t argc, char *argv[] ) {
	if ( argc > 2 ){
	    freopen(argv[2], "w", stdout );
	}

	ifstream in ( argv[1] );
	int n; in >> n;
	string* strs = new string[n];
	for ( int i = 0; i < n; i++ ) {
		in >> strs[i];
	}

	int numberOfReverse = 0, sizeOfMinimalSubset = 0;

	solve( strs, n, numberOfReverse, sizeOfMinimalSubset );
	cout << numberOfReverse << endl << sizeOfMinimalSubset << endl;

	delete[] strs;
	return 0;
}		
