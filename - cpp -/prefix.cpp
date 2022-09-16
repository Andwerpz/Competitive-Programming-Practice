#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC 2022 Week 1 B

//trivial solution

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s, t;
    cin >> s >> t;
    if(s.size() > t.size()){
        cout << "No\n";
        return 0;
    }
    bool isValid = true;
    for(int i = 0; i < s.size(); i++){
        if(s[i] != t[i]){
            isValid = false;
            break;
        }
    }
    cout << (isValid? "Yes\n" : "No\n");
    
    return 0;
}
