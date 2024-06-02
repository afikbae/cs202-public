#include <bits/stdc++.h>


using namespace std;
int reverseCount, minimalSubsetSize, i,j,k,a,b,c,n, countLeft, countRight;
string str[100005];
bool visited[100005];

int findString( string temp ){
	for( int i = 1; i<=n; i++ ){
		if( str[i].size() != temp.size() ){
            continue;
		}
		int j = 0;
		int length = str[i].size();
		while( j < str[i].size() && str[i].at(j) == temp.at(j) ){
			j++;
		} 
		if( j == str[i].size() ){
			return i;
		}
	}
	return -1;
}


int main(int argc, char *argv[]){
    freopen(argv[1], "r", stdin);
    if( argc > 2 ){
        freopen(argv[2], "w", stdout);
    }
    scanf("%d",&n);
    for( int i = 1; i <= n; i++){
         cin >> str[i];
    }
    for( int i = 1; i<=n; i++ ){
         if( !visited[i] ){
             minimalSubsetSize++;
             visited[i] = true;
             int length = str[i].size();
             string temp = str[i];
             countLeft = countRight = 0;
             countLeft++;
             for( int j= 0; j < length - 1; j++ ){
                  string right = temp.substr( 1, length - 1);
                  right.append( temp.substr(0,1));
                  temp = right;
                  int id = findString( temp );
                  if ( id != -1 ){
					  visited[id] = true;
					  countLeft++;
				  }  
		     }
		     temp = str[i];
		     reverse( temp.begin(), temp.end());
		      for( int j= 0; j < length; j++ ){
                  int id = findString( temp );
                  if ( id != -1  && !visited[id]){
					  visited[id] = true;
					  countRight++;
				  }
				  string right = temp.substr( 1, length - 1);
                  right.append( temp.substr(0,1));
                  temp = right;
		     }
		     reverseCount+= min ( countLeft, countRight );
		 }
		 
    
    
    }
    printf("%d\n", reverseCount);
    printf("%d\n", minimalSubsetSize);
}
