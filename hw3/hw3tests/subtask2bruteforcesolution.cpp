#include <bits/stdc++.h>

using namespace std;
string text;
string patterns[100005];
int n,i,j,k,a,b,c, fre[100005];

int main(int argc, char *argv[]){
	freopen( argv[1], "r", stdin );
	if( argc > 2 ){
		freopen( argv[2], "w", stdout );
	}
	cin >> text;
	scanf( "%d", &n);
	for( int i = 0; i < n; i++ ){
		cin >> patterns[i];
	}
	for( int i = 0; i < n; i++ ){
		 int lengthPattern = patterns[i].size();
		 int lengthText = text.size();
		 for( int j = 0; j <= lengthText - lengthPattern; j++ ){
			 int k = j, l = 0;
			 while( l < lengthPattern && text.at(k) == patterns[i].at(l) ){
				 l++;
				 k++;
			 }
			 if( l == lengthPattern ) {
				 fre[i]++;
			 }
		 }
		 printf( "%d\n", fre[i] );
	}
}
