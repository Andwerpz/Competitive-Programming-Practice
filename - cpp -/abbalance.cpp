
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1606A

//notice that AB(s) == BA(s) when s[0] == s[s.size() - 1]. 

//to prove this to yourself, first notice that consecutive 'a's and 'b's are redundant, we can remove the extras. 
//now we have a string of alternating 'a's and 'b's, and it's pretty obvious that it must start and end on the same letter in order
//for AB(s) == BA(s).

//so to solve, just check if the start and end are the same, if they aren't, then just set the last character equal to the first one.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        if(s[0] != s[s.size() - 1]){
            s[s.size() - 1] = s[0];
        }
        cout << s << endl;
    }

    return 0;
}
