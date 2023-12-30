#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1894B

//if there are two values which occur more than once, then it is always possible. 

//in the case where it is possible, choose two of the values that occur more than once, and assign them 2 and 3
//in the b array. All other elements, assign 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        map<int, int> m;
        for(int i = 0; i < n; i++){
            if(m.find(a[i]) == m.end()){
                m.insert({a[i], 0});
            }
            m[a[i]] ++;
        }
        int nr = 0;
        int a_val = -1;
        int b_val = -1;
        for(auto i = m.begin(); i != m.end(); i++){
            if(i -> second >= 2) {
                nr ++;
                if(a_val == -1){
                    a_val = i -> first;
                }
                else if(b_val == -1){
                    b_val = i -> first;
                }
            }
        }
        if(nr < 2) {
            cout << "-1\n";
            continue;
        }
        for(int i = 0; i < n; i++){
            if(a[i] == a_val) {
                cout << "2 ";
                a_val = -1;
            }
            else if(a[i] == b_val) {
                cout << "3 ";
                b_val = -1;
            }
            else {
                cout << "1 ";
            }
        }
        cout << "\n";
    }
    
    return 0;
}
