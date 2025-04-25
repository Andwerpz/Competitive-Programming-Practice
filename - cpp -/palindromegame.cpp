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

//Codeforces - 1527 B1 B2

//bruh, can't do games like this D:
//just a bunch of casework, my brain can't hold all the cases at once

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int a = 0, b = 0;
        bool center = false;
        if(n % 2) center = s[n / 2] == '0';
        int zcnt = 0, ucnt = 0;
        for(int i = 0; i < n / 2; i++){
            if(s[i] != s[n - 1 - i]) ucnt ++;
            if(s[i] == '0' && s[n - 1 - i] == '0') zcnt ++;
        }
        if(!center) {
            if(zcnt != 0) {
                if(ucnt >= 1) {
                    b += ucnt - 1;
                    a += 1;
                    a += zcnt - 1, b += zcnt - 1;
                    b += 2;
                }
                else {
                    a += zcnt - 1, b += zcnt - 1;
                    a += 2;
                }
            }
            else {
                b += ucnt;
            }
        }
        else {
            if(zcnt != 0){
                b += ucnt;
                a += 1;
                a += zcnt - 1, b += zcnt - 1;
                b += 2;
            }
            else {
                b += ucnt;
                a += 1;
            }
        }
        // cout << "A B : " << a << " " << b << "\n";
        cout << (a == b? "DRAW" : (a < b? "ALICE" : "BOB")) << "\n";
    }
    
    return 0;
}