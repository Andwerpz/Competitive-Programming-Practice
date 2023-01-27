#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 C

//use a stack. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    stack<char> s1;
    stack<char> s2;
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        if(c == '<') {
            s1.pop();
        }
        else {
            s1.push(c);
        }
    }
    while(s1.size() != 0){
        s2.push(s1.top());
        s1.pop();
    }
    while(s2.size() != 0){
        cout << s2.top();
        s2.pop();
    }
    cout << "\n";
    
    return 0;
}
