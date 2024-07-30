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

//Codeforces - 1743D

//for the first substring, might as well just take the entire string. 

//for the second one, our goal is to patch holes in the first string. Note that the most important hole to patch is
//the most significant 0. How can we patch this hole? Well, we can't use any less significant 1s, since 1s can 
//only move to the left. No, we need to use a more significant 1. 

//so for every more significant 1, we can try patching the most significant 0, and we can try each in O(n) time. 
//this is where the random testcases helps us. Because the testcases are random, there are not going to be 
//that many more significant 1s, the probability that there are >= x more significant 1s is around 1 / 2^(x - 1). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string s;
    cin >> s;
    vb a(n);
    for(int i = 0; i < n; i++){
        a[i] = s[i] - '0';
    }
    int f = -1;
    for(int i = 0; i < n; i++){
        if(a[i]){
            f = i;
            break;
        }
    }
    if(f == -1){
        cout << "0\n";
        return 0;
    }
    int fz = -1;
    for(int i = f; i < n; i++){
        if(!a[i]){
            fz = i;
            break;
        }
    }
    if(fz == -1){
        for(int i = f; i < n; i++){
            cout << a[i];
        }
        cout << "\n";
        return 0;
    }
    vb ans(n, 0);
    for(int i = f; i < n && a[i]; i++){
        vb cans(n, 0);
        for(int j = 0; j < n; j++){
            cans[j] = a[j];
            if(j >= i - f + 1) {
                cans[j] = cans[j] || a[j - (i - f + 1)];
            }
        }
        bool greater = false;
        for(int j = 0; j < n; j++){
            if(cans[j] && !ans[j]) {
                greater = true;
                break;
            }
            if(ans[j] && !cans[j]) {
                break;
            }
        }
        if(greater) {
            ans = cans;
        }
    }
    for(int i = f; i < n; i++){
        cout << ans[i];
    }
    cout << "\n";
    
    return 0;
}