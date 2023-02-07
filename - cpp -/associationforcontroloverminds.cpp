#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 03 A

//i think the intended soltion is with dsu, but this is fine too. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<int, int> m;
    map<int, int> size;
    int ans = 0;
    for(int i = 0; i < n; i++){
        bool isValid = true;
        int amt;
        cin >> amt;
        vector<int> a(amt, 0);
        map<int, int> cnt;
        for(int j = 0; j < amt; j++){
            cin >> a[j];
            if(m.find(a[j]) != m.end()) {
                int prev = m.find(a[j]) -> second;
                if(cnt.find(prev) == cnt.end()) {
                    cnt.insert({prev, 0});
                }
                cnt.find(prev) -> second ++;
            }
        }
        for(auto j = cnt.begin(); j != cnt.end(); j++) {
            if(j -> second != size.find(j -> first) -> second) {
                isValid = false;
            }
        }
        if(isValid) {
            ans ++;
            for(int j = 0; j < amt; j++) {
                if(m.find(a[j]) != m.end()) {
                    m.erase(a[j]);
                }
                m.insert({a[j], i});
            }
            size.insert({i, amt});
        }
    }
    cout << ans << "\n";
    
    return 0;
}
