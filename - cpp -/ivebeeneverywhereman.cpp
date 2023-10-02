#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - everywhere

//just count the number of unique elements using a set. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        set<string> s;
        for(int i = 0; i < n; i++){
            string st;
            cin >> st;
            s.insert(st);
        }
        cout << s.size() << "\n";
    }
    
    return 0;
}
