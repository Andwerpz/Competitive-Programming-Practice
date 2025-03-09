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

//Codeforces - 2045A

//bruuh, implementation diff

//just do some greedy

int calc1(int vcnt, int ccnt, int ncnt, int gcnt, int ycnt) {
    int dcnt = min(ncnt, gcnt);
    ccnt += (ncnt - dcnt) + (gcnt - dcnt);
    int ans = 0, udcnt = 0;
    while(vcnt + ycnt != 0){
        if(vcnt != 0) vcnt --;
        else if(ycnt != 0) ycnt --; 
        bool udcnt_sub = false;
        {
            if(dcnt != 0) dcnt --, udcnt ++;
            else if(ccnt != 0) ccnt --;
            else if(ycnt != 0) ycnt --;
            else if(udcnt != 0) udcnt --, udcnt_sub = true;
            else break;
        }
        {
            if(dcnt != 0) dcnt --, udcnt ++;
            else if(ccnt != 0) ccnt --;
            else if(ycnt != 0) ycnt --;
            else if(udcnt != 0) udcnt --;
            else {udcnt += udcnt_sub; break;}
        }
        ans += 3;
    }
    ans += udcnt;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s;
    cin >> s;
    int vcnt = 0, ccnt = 0, ncnt = 0, gcnt = 0, ycnt = 0;
    for(char c : s) {
        if(c == 'G') gcnt ++;
        else if(c == 'N') ncnt ++;
        else if(c == 'Y') ycnt ++;
        else if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') vcnt ++;
        else ccnt ++;
    }
    int ans = calc1(vcnt, ccnt, ncnt, gcnt, ycnt);
    cout << ans << "\n";
    
    return 0;
}