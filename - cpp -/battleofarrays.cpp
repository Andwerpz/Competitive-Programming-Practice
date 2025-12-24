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

//ICPC NERC 2025-2026 - B

//didn't prove, but assumed that if you naively simulate this, it'll come out to around O(n + m) time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        priority_queue<int> a, b;
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a.push(x);
        }
        for(int i = 0; i < m; i++) {
            int x;
            cin >> x;
            b.push(x);
        }
        int turn = 0;
        bool alice_win;
        while(true) {
            assert(a.size() != 0 && b.size() != 0);
            if(turn == 0) {
                //alice 
                int x = a.top(); a.pop();
                int y = b.top(); b.pop();
                y -= x;
                a.push(x);
                if(y > 0) b.push(y);
            }
            else {
                //bob 
                int x = b.top(); b.pop();
                int y = a.top(); a.pop();
                y -= x;
                b.push(x);
                if(y > 0) a.push(y);
            }
            if(a.size() == 0) {
                alice_win = false;
                break;
            }
            if(b.size() == 0) {
                alice_win = true;
                break;
            }
            turn ^= 1;
        }
        cout << (alice_win ? "Alice" : "Bob") << "\n";
    }
    
    return 0;
}