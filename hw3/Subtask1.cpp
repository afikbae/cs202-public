/**
* Title: Hash Table
* Author : Mehmet Akif Şahin
* ID: 22203673 
* Section : 3
* Homework : 3
* Description : Subtask1 solution
*/

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

#include "HashTable.h"

#define int long long

using namespace std;

int fp(int a, int b, int modulo) {
    if (b == 0) return 1;
    if (b % 2 == 1) return (a * fp(a, b - 1, modulo)) % modulo;
    int half = fp(a, b/2, modulo);
    return (half * half) % modulo;
}

int solve ( string*& strs, int n ) {
	int result = 0;
	int mod1 = 12582917;
	int mod2 = 12582919;
	HashTable ht1 ( mod1 );
	HashTable ht2 ( mod2 );
	for ( int i = 0; i < n; i++ ) {
		ht1.insert( strs[i] );
		ht2.insert( strs[i] );
	}

	for ( int i = 0; i < n; i++ ) {
		int l = strs[i].length();
		string& str = strs[i];
		int hash1 = 0;
		int hash2 = 0;
		int p = 31;
		int power1 = 1;
		int power2 = 1;
		for ( int pos = 0; pos < str.length(); pos++ ) {
			hash1 += (power1 * ( ( str[pos] | 32 ) - 'a' + 1 ));
			hash1 %= mod1;
			hash2 += (power2 * ( ( str[pos] | 32 ) - 'a' + 1 ));
			hash2 %= mod2;
			power1 *= p;
			power1 %= mod1;
			power2 *= p;
			power2 %= mod2;
			if ( ht1.contains( hash1 ) && ht2.contains( hash2 ) ) {
				result++;
			}
		}
		int inv1 = fp ( p, mod1 - 2, mod1 );
		int inv2 = fp ( p, mod2 - 2, mod2 );
		for ( int pos = 0; pos < str.length() ; pos++ ) {
			hash1 -= ( str[pos] | 32 ) - 'a' + 1;
			hash1 *= inv1;
			hash1 %= mod1;
			hash2 -= ( str[pos] | 32 ) - 'a' + 1;
			hash2 *= inv2;
			hash2 %= mod2;
			if ( ht1.contains( hash1 ) && ht2.contains( hash2 ) ) {
				result++;
			}
		}
	}
	return result - n;
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

	cout << solve( strs, n ) << endl;

	delete[] strs;
	return 0;
}		
