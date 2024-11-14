#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//NCPC 2024 - J

//bruh, their validator not working???

//if there is a missing even number from 2 to 2n on either side, then we can just fill that side with the
//missing number / 2, and no pair will be able to exactly match any challenge card. 

//otherwise, both P_i and S_i will look like a permutation of the even numbers from 2 to 2n. Can look for the occurrence of
//2n in S_i, and just create n - 1 players of form (P_i, 1), (P_i, 2), ..., (P_i, n - 1). Then, we just have one more player
//that can easily be created. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pii> a(n);
    set<int> l, r;
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
        if(a[i].first % 2 == 0){
            l.insert(a[i].first);
        }
        if(a[i].second % 2 == 0){
            r.insert(a[i].second);
        }
    }
    if(n == 1){
        if(a[0].first == 2 && a[0].second == 2){
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
            cout << "1 1\n";
        }
        return 0;
    }
    vector<pii> ans(0);
    if(l.size() != n){
        int x = -1;
        for(int i = 1; i <= n; i++){
            if(!l.count(i * 2)) {
                x = i;
                break;
            }
        }
        assert(x != -1);
        for(int i = 1; i <= n; i++){
            ans.push_back({x, i});
        }
    }
    else if(r.size() != n){
        assert(false);
        int x = -1;
        for(int i = 1; i <= n; i++){
            if(!r.count(i * 2)) {
                x = i;
                break;
            }
        }
        assert(x != -1);
        for(int i = 1; i <= n; i++){
            ans.push_back({i, x});
        }
    }
    else {
        assert(r.size() == n);
        assert(l.size() == n);
        int maxl = -1;
        for(int i = 0; i < n; i++){
            if(a[i].second == n * 2) {
                maxl = a[i].first / 2;
                break;
            }
        }
        assert(maxl != -1);
        for(int i = 1; i < n; i++){
            ans.push_back({maxl, i});
        }
        for(int i = 0; i < n; i++){
            if(maxl == a[i].first / 2) {
                continue;
            }
            if(abs(maxl - (a[i].first / 2)) % 2 == 1){
                if(a[i].second == 2) {
                    ans.push_back({a[i].first / 2, 2});
                }
                else {
                    ans.push_back({a[i].first / 2, 1});
                }
                break;
            }
        }
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}