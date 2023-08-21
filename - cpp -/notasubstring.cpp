#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1860A

//the only case in which it is impossible to generate a string is when s = "()". 
//since every proper bracket sequence needs a "()" substring, it is impossible. 

//otherwise, it is always possible. Just check if there are two consecutive '(' or ')' characters. 
//if there is, then we can generate a string of form "()()()". If there isn't then we generate one of form
//"((()))".

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        if(s == "()") {
            cout << "NO\n";
            continue;
        }
        bool consecutive = false;
        for(int i = 1; i < s.size(); i++){
            if(s[i] == s[i - 1]){
                consecutive = true;
            }
        }
        cout << "YES\n";
        if(consecutive) {
            for(int i = 0; i < s.size(); i++){
                cout << "()";
            }
            cout << "\n";
        }
        else {
            for(int i = 0; i < s.size(); i++){
                cout << "(";
            }
            for(int i = 0; i < s.size(); i++){
                cout << ")";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
