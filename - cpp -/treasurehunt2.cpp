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

//2025 NAQ - K

//just some casework. 

//first, figure out which 3x3 the treasure has to be contained in. 
//then, you can spend two queries to nail down the position of the treasure within the 3x3

int interact(int r, int c) {
    assert(r >= 0 && c >= 0 && r < 5 && c < 5);
    r ++; c ++;
    cout << "? " << r << " " << c << endl;
    int ans;
    cin >> ans;
    return ans;
}

void report_ans(int r, int c) {
    assert(r >= 0 && c >= 0 && r < 5 && c < 5);
    r ++;
    c ++;
    cout << "! " << r << " " << c << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int ro = -1, co = -1;
    if(interact(1, 1)) ro = 0, co = 0;
    else if(interact(1, 3)) ro = 0, co = 2;
    else if(interact(3, 1)) ro = 2, co = 0;
    else ro = 2, co = 2;

    if(interact(ro + 0, co + 1)) {
        if(interact(ro, co)) report_ans(ro, co);
        else report_ans(ro, co + 1);
    }   
    else {
        if(interact(ro + 1, co)) report_ans(ro + 1, co);
        else report_ans(ro + 1, co + 1);
    }
    
    return 0;
}