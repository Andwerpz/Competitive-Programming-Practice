#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1862E

//note that if we choose some subsequence of movies to watch, the total penalty will always equal the index
//of the last movie, i, times d; i * d. 

//with that in mind, if we set the location of the last movie we watch, lets say 'l', we can just take the m 
//largest entertainment values in the segment [0, l], and update the answer with the sum. 

//we can keep track of the m largest movies using a multiset. 

void insert(map<int, int>& m, int val){
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m.find(val) -> second ++;
}

void erase(map<int, int>& m, int val) {
    m.find(val) -> second --;
    if(m.find(val) -> second == 0){
        m.erase(val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        ll d;
        cin >> n >> m >> d;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        map<int, int> mp;
        ll ans = 0;
        ll penalty = 0;
        ll gsum = 0;
        int mcnt = 0;
        for(int i = 0; i < n; i++){
            penalty += d;
            if(a[i] >= 0) {
                insert(mp, a[i]);
                gsum += a[i];
                mcnt ++;
            }
            if(mcnt > m){
                mcnt --;
                gsum -= mp.begin() -> first;
                erase(mp, mp.begin() -> first);
            }
            ans = max(ans, gsum - penalty);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
