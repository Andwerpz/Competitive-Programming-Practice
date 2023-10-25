#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - Yandex Algorithm 2011 Round 2 D

//standard mo's algorithm sqrt decomposition problem. 

//we order the queries in such a way that in order to process them, we can make use of information 
//from the previous query

//total running time is around O(n * sqrt(n)). 

void insert(vector<ll>& m, ll& sum, ll val) {
    sum -= m[val] * m[val] * val;
    m[val] ++;
    sum += m[val] * m[val] * val;
}

void erase(vector<ll>& m, ll& sum, ll val) {
    sum -= m[val] * m[val] * val;
    m[val] --;
    sum += m[val] * m[val] * val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, t;
    cin >> n >> t;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int p = sqrt(n);
    vector<pair<int, pair<int, int>>> q(t);
    for(int i = 0; i < t; i++){
        q[i].first = i;
        cin >> q[i].second.first >> q[i].second.second;
        q[i].second.first --;
    }
    sort(q.begin(), q.end(), [&p](pair<int, pair<int, int>>& a, pair<int, pair<int, int>>& b) -> bool {
        int a_sec = a.second.first / p;
        int b_sec = b.second.first / p; 
        if(a_sec != b_sec) {
            return a_sec < b_sec;
        }
        if(a_sec % 2 == 0){
            return a.second.second < b.second.second;
        }
        return a.second.second > b.second.second;
    });
    //sum will always represent the answer on the subarray [l, r).
    int l = 0;
    int r = 0;
    ll sum = 0;
    vector<ll> m(1e6 + 100, 0);
    vector<ll> ans(t);
    for(int i = 0; i < t; i++){
        int nl = q[i].second.first;
        int nr = q[i].second.second;
        while(nl < l) {
            l --;
            insert(m, sum, a[l]);
        }
        while(nr > r) {
            insert(m, sum, a[r]);
            r ++;
        }
        while(nl > l) {
            erase(m, sum, a[l]);
            l ++;
        }
        while(nr < r) {
            r --;
            erase(m, sum, a[r]);
        }
        ans[q[i].first] = sum;
    }
    for(int i = 0; i < t; i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}
