
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1613A

//my implementation sucks

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int x1, p1, x2, p2;
        cin >> x1 >> p1 >> x2 >> p2;
        string s1 = to_string(x1);
        string s2 = to_string(x2);
        bool isEqual = true;
        if(p1 + s1.size() > p2 + s2.size()){
            cout << ">\n";
            continue;
        }
        else if(p1 + s1.size() < p2 + s2.size()){
            cout << "<\n";
            continue;
        }
        //cout << s1 << " " << s2 << endl;
        int c1 = 0;
        int c2 = 0;
        while(c1 < s1.size() || c2 < s2.size()){
            int char1 = c1 >= s1.size()? '0' : s1[c1];
            int char2 = c2 >= s2.size()? '0' : s2[c2];
            //cout << char1 << " " << char2 << endl;
            if(char1 > char2){
                cout << ">\n";
                goto outer;
            }
            else if(char1 < char2){
                cout << "<\n";
                goto outer;
            }
            c1++;
            c2++;
        }
        cout << "=\n";
        outer: continue;
    }
    
    return 0;
}
