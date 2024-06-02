/**
* Title: Hash Table
* Author : Mehmet Akif Şahin
* ID: 22203673 
* Section : 3
* Homework : 3
* Description : Subtask2 solution
*/

#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <climits>

#include "HashTable.h"

using namespace std;

#define int long long

struct MyPair {
	int hash, oldIndex;
};

int fp(int a, int b, int modulo) {
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * fp(a, b - 1, modulo)) % modulo;
    int half = fp(a, b/2, modulo);
    return (half * half) % modulo;
}

int find (MyPair * arr, int n, int hash ) {
	int lo = 0, hi = n - 1, ans = -1;
	while ( lo <= hi ) {
		int mid = ( hi + lo ) / 2;
		if ( hash > arr[mid].hash ) {
			lo = mid + 1;
		} else if ( hash == arr[mid].hash ) {
			ans = mid;
			return ans;
		} else {
			hi = mid - 1;
		}
	}
	return ans;
}

int _hash ( string& text, int mod ) {
	int result = 0;
	int p = 31;
	for ( int i = text.length() - 1; i >= 0; i-- ) {
		result *= p;
		result %= mod;
		result += (text[i] | 32) - 'a' + 1;
		result %= mod;
	}
	return result;
}

int* solve ( string& text, string*& patterns, int n ) {
	int* occurences = new int[n];
	memset( occurences, 0, n * sizeof(int) );

	int mod1 = 1e9 + 7;
	int mod2 = 1e9 + 9;

	MyPair* hashes1 = new MyPair[n];
	MyPair* hashes2 = new MyPair[n];

	int shortest = INT_MAX, longest = 0;
	for ( int i = 0; i < n; i++ ) {
		hashes1[i] = {_hash( patterns[i], mod1 ), i};
		hashes2[i] = {_hash( patterns[i], mod2 ), i};
		if ( patterns[i].length() < shortest ) shortest = patterns[i].length();
		if ( patterns[i].length() > longest ) longest = patterns[i].length();
	}

	sort( hashes1, hashes1 + n, [](MyPair p1, MyPair p2) {
		return p1.hash < p2.hash;
	      });
	sort( hashes2, hashes2 + n, [](MyPair p1, MyPair p2) {
		return p1.hash < p2.hash;
	      });

	for ( int substrLength = shortest; substrLength <= longest; substrLength++ ) {
		int hash1 = 0;
		int hash2 = 0;
		int p = 31;

		for ( int i = substrLength - 1; i >= 0; i-- ) {
			hash1 *= p;
			hash1 %= mod1;
			hash1 += ( text[i] | 32 ) - 'a' + 1;
			hash1 %= mod1;

			hash2 *= p;
			hash2 %= mod2;
			hash2 += ( text[i] | 32 ) - 'a' + 1;
			hash2 %= mod2;
		}

		int index1 = find( hashes1, n, hash1 );
		int index2 = find( hashes2, n, hash2 );

		if ( index1 != -1 && index2 != -1 && hashes1[index1].oldIndex == hashes2[index2].oldIndex ) {
			occurences[hashes1[index1].oldIndex]++;
		}

		int power1 = fp( p, mod1 - 2, mod1 );
		int power2 = fp( p, mod2 - 2, mod2 );
		for ( int i = substrLength; i < text.length(); i++ ) {
			hash1 -= ( text[i - substrLength] | 32 ) - 'a' + 1;
			hash1 %= mod1;
			hash1 *= power1;
			hash1 %= mod1;
			hash1 += ( ( text[i] | 32 ) - 'a' + 1 ) * fp( p, substrLength - 1, mod1 );
			hash1 %= mod1;

			hash2 -= ( text[i - substrLength] | 32 ) - 'a' + 1;
			hash2 %= mod2;
			hash2 *= power2;
			hash2 %= mod2;
			hash2 += ( ( text[i] | 32 ) - 'a' + 1 ) * fp( p, substrLength - 1, mod2 );
			hash2 %= mod2;

			int index1 = find( hashes1, n, hash1 );
			int index2 = find( hashes2, n, hash2 );

			if ( index1 != -1 && index2 != -1 && hashes1[index1].oldIndex == hashes2[index2].oldIndex ) {
				occurences[hashes1[index1].oldIndex]++;
			}
		}
	}
	delete[] hashes1;
	delete[] hashes2;
	return occurences;
}

int32_t main ( int32_t argc, char *argv[] ) {
	if( argc > 2 ){
	    freopen(argv[2], "w", stdout );
	}

	ifstream in ( argv[1] );
	string text; in >> text;
	int n; in >> n;
	string* patterns = new string[n];
	for ( int i = 0; i < n; i++ ) {
		in >> patterns[i];
	}

	int* occurences = solve( text, patterns, n );

	for ( int i = 0; i < n; i++ ) {
		cout << occurences[i] << endl;
	}

	delete[] occurences;
	delete[] patterns;
	return 0;
}		
