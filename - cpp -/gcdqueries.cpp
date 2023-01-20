#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1762D

//notice that if you're using gcd to find multiples, 0 is always a multiple of any number. 

//the problem this solution suffers from is finding the initial not-1 position. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        map<int, int> m;
        for(int i = 0; i < n; i++){
            m.insert({i, 0});
        }
        vector<bool> v(n, true);
        for(int i = n - 1; i >= 0; i--){
            if(!v[i]) {
                continue;
            }
            int maxGcd = 0;
            for(auto j = m.begin(); j != m.end(); j++){
                int next = j -> first;
                if(next == i){
                    continue;
                }
                int gcd = 0;
                cout << "? " << (i + 1) << " " << (next + 1) << endl;
                cin >> gcd;
                j -> second = gcd;
                maxGcd = max(maxGcd, gcd);
            }
            vector<int> remove(0);
            for(auto j = m.begin(); j != m.end(); j++){
                if(j -> first == i){
                    continue;
                }
                if(j -> second == maxGcd){
                    continue;
                }
                remove.push_back(j -> first);
            }
            for(int j : remove) {
                m.erase(j);
                v[j] = false;
            }
            if(m.size() == 2) {
                cout << "! " << (m.begin() -> first + 1) << " " << (m.rbegin() -> first + 1) << endl;
                int ret = 0;
                cin >> ret;
                break;
            }
            v[i] = false;
            m.erase(i);
            if(m.size() == 2) {
                cout << "! " << (m.begin() -> first + 1) << " " << (m.rbegin() -> first + 1) << endl;
                int ret = 0;
                cin >> ret;
                break;
            }
        }
    }
    
    return 0;
}
