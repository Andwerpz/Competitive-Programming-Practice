#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//University of Alberta Programming Contest 2023 H

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<string, int> m;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        m.insert({s, i});
    }
    vector<ll> a(0);
    string s;
    cin >> s;
    int l = 0;
    while(l != s.size()) {
        int dig = -1;
        int ptr = 1;
        while(m.find(s.substr(l, ptr)) == m.end()) {
            ptr ++;
        } 
        dig = m.find(s.substr(l, ptr)) -> second;
        a.push_back(dig);
        l += ptr;
    }
    ll ans = 0;
    ll pow = 1;
    for(int i = a.size() - 1; i >= 0; i--){
        ans += a[i] * pow;
        pow *= (ll) n;
    }
    cout << ans << "\n";
    
    return 0;
}
