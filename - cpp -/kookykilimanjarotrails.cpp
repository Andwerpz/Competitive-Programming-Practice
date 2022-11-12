#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//A&M Fall 2022 K

//this problem is like a parenthesis problem. Use a stack. 

//each different difficulty is a different type of parenthesis.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    stack<int> s;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        if(s.size() != 0 && s.top() == next){
            s.pop();
        }
        else {
            s.push(next);
        }
    }
    cout << (s.size() == 0? "YES\n" : "NO\n");
    
    return 0;
}
