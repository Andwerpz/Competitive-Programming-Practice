#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 E

//if two cards of same characters are swapped, then it is impossible to know what has been done. 
//this means that if there exists two cards of the same character, then it is impossible to know what has been done, 
//because you don't know if a swap happened in the case nothing was swapped. 

//if there are no duplicates, then it is always possible to figure out what happened. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    set<char> st;
    bool isValid = true;
    for(int i = 0; i < s.size(); i++){
        if(st.find(s[i]) != st.end()) {
            isValid = false;
            break;
        }
        st.insert(s[i]);
    }
    cout << (isValid? 1 : 0) << "\n";
    
    return 0;
}
