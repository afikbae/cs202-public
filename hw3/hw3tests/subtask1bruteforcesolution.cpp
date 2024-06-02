/*
 * Author : Yusuf Ziya Ozgul
 * Description: Test code for subtask 2
 */

#include <bits/stdc++.h>


using namespace std;

int numberOfPairs;
string str[100005];
int n, i, j, k, a, b, c;


int main(int argc, char *argv[] ){
	freopen( argv[1], "r", stdin );
	if( argc > 2 ){
		freopen( argv[2], "w", stdout );
	}
	scanf( "%d", &n);
	for( int i = 0; i < n; i++ ){
		cin >> str[i];
	}
	for( int i = 0; i < n; i++ ){
		for( int j = 0; j < n; j++ ){
			if( i == j ) {
				continue;
			}
		    if ( str[i].size() >= str[j].size() ) {
				continue;
			}
		    int k = 0;
		    int lengthi = str[i].size();
		    int lengthj = str[j].size();
		    while( k < lengthi && str[i].at(k) == str[j].at(k) ){ // prefix
				k++;
			}
			if( k == lengthi ){
				numberOfPairs++;
			}
			k = 0;
			lengthi--;
			lengthj--;
			while( lengthi >= 0 && str[i].at(lengthi) == str[j].at( lengthj - k ) ){ //suffix
				lengthi--;
				k++;
			}
			if ( lengthi == - 1 ){
				numberOfPairs++;
			}
		}
	}
	printf("%d\n", numberOfPairs );
	
}
