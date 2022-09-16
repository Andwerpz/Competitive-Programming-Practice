#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC 2022 Week 1 A

//trivial solution. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    set<int> s;
    for(int i = 0; i < 5; i++){
        int a;
        cin >> a;
        s.insert(a);
    }
    cout << s.size() << "\n";
    
    return 0;
}
