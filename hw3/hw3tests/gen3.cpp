#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {
    return a + rand() % (b - a + 1);
}

string RandomString(int len)
{
   string str = "ab"; // not using all of the characters to increase the chance of collision
   string newstr;
   int pos;
   while(newstr.size() != len) {
    pos = ((rand() % (str.size() - 1)));
    newstr += str.substr(pos,1);
   }
   return newstr;
}

int main (int argc, char *argv[]) {
    srand(atoi(argv[1]));
    int l = rand(1,100);
    printf("%d\n", l);
    set<string> sset;
    for (int i = 0; i < l; i++) {
	string str = RandomString(rand(1, 100));
        while (sset.find(str) != sset.end()) str = RandomString(rand(1, 100));
        sset.insert(str);

        printf("%s\n", str.c_str());
    }
    return 0;
}
