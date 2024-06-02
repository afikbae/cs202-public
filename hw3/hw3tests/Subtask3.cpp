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

struct MyPair {
	int hash, oldIndex;
};

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
		hash %= mod;
		hash += charToVal( item[i] );
		hash %= mod;
	}

	int minHash = hash;

	int power = fp( p, item.length() - 1, mod );

	for ( int i = 0; i < item.length(); i++ ) {
		hash -= ( power * charToVal( item[i] ) ) % mod;
		hash %= mod;
		hash *= p;
		hash %= mod;
		hash -= ( power * charToVal( item[i] ) ) % mod;
		hash %= mod;
		if ( hash < minHash ) minHash = hash;
	}

	return minHash;
}

int find (MyPair * arr, int n, int hash ) {
	int lo = 0, hi = n - 1, ans = -1;
	while ( lo <= hi ) {
		int mid = ( hi + lo ) / 2;
		if ( hash > arr[mid].hash ) {
			lo = mid + 1;
		} else if ( hash == arr[mid].hash ) {
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
	MyPair* hashes1  = new MyPair[ n ];
	MyPair* hashes2  = new MyPair[ n ];

	for ( int i = 0; i < n; i++ ) {
		int hash = computeHash( strs[i], mod1 );
		hashes1[i] = {hash, i};
		hash = computeHash( strs[i], mod2 );
		hashes2[i] = {hash, i};
	}

	
	sort( hashes1, hashes1 + n, [](MyPair p1, MyPair p2) {
		return p1.hash < p2.hash;
	      });
	sort( hashes2, hashes2 + n, [](MyPair p1, MyPair p2) {
		return p1.hash < p2.hash;
	      });

	int* counts = new int[n];
	memset( counts, -1, n * sizeof(int) );

	for ( int i = 0; i < n; ) {
		int hash1 = hashes1[i].hash;
		int hash2 = hashes2[i].hash;
		int start = i;
		int end = ++i;
		while ( hash1 == hash2 && hash1 == hashes1[i].hash ) end = ++i;
		if ( counts[start] > 0 ) {
			numberOfReverse += counts[start] > end - start ? end - start : counts[start];
		} else {
			sizeOfMinimalSubset++;
			string reverseStr = reverseString(strs[hashes1[start].oldIndex]);
			int reverseHash1 = computeHash( reverseStr, mod1);
			int reverseHash2 = computeHash( reverseStr, mod2);
			int reverseStart1 = find( hashes1, n, reverseHash1 );
			int reverseStart2 = find( hashes2, n, reverseHash2 );
			if ( reverseStart1 != -1 && reverseStart2 != -1 && reverseStart1 == reverseStart2 )
				counts[reverseStart1] = end - start;
		}
	}
	delete[] hashes1;
	delete[] hashes2;
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
