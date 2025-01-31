#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//UTPC Contest 1-29-25 Div.1 - I

//uhh, grundy numbers or smth. idk how to prove, maybe the editorial will inform me. 
//apparently, this is exactly staircase nim. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    int podd = -1;
    int cur = 0, dsum = 0;
    int g = 0;
    for(int i = 0; i < n; i++){
        int diff = a[i] - cur;
        cur = a[i];
        dsum += diff;
        if(diff != 0){
            if(dsum % 2){
                if(diff % 2) podd = i;
                else g ^= i - podd, podd = i;
            }
            else {
                if(diff % 2) g ^= i - podd, podd = -1;
                //else do nothing
            }
        }
    }
    if(podd != -1) g ^= n - podd;
    cout << (g? "Ai" : "Bo") << "\n";
    
    return 0;
}