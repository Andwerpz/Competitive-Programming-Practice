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

//Topcoder - 10938

//obviously, the hull needs to be connected, and not have holes. 
//what is less obvious is that the hull can't be 'convex' (duh). What that means is that there cannot be
//some cell that is not part of the hull which is covered on three sides by the hull. 

//then, refer to trapping rainwater (leetcode) if you're still confused about the solution. 

vector<string> split(string& s, char delim){
    vector<string> ans;
    for(int i = 0; i < s.size();){
        int r = i;
        while(r != s.size() && s[r] != delim) r ++;
        ans.push_back(s.substr(i, r - i));
        i = r + 1;
    }
    return ans;
}

class DiscreteConvexHull {
public:
    long long minArea(vector<string> cells) {
        //store for each x value, the min and max y value of points there
        map<ll, ll> mny, mxy;
        for(int i = 0; i < cells.size(); i++){
            vector<string> tok = split(cells[i], ' ');
            for(int j = 0; j < tok.size(); j++){
                vector<string> coord = split(tok[j], ',');
                ll x = stoi(coord[0]), y = stoi(coord[1]);
                if(!mny.count(x)) mny[x] = 1e9;
                if(!mxy.count(x)) mxy[x] = -1e9;
                mny[x] = min(mny[x], y);
                mxy[x] = max(mxy[x], y);
            }
        }
        //go two ways, storing min/max pfx/sfx
        map<ll, ll> pfxmny, pfxmxy, sfxmny, sfxmxy;
        ll px = -1;
        for(auto i = mny.begin(); i != mny.end(); i++) {
            ll x = i->first;
            pfxmny[x] = mny[x], pfxmxy[x] = mxy[x];
            if(px != -1) {
                pfxmny[x] = min(pfxmny[x], pfxmny[px]);
                pfxmxy[x] = max(pfxmxy[x], pfxmxy[px]);
            }
            px = x;
        }
        px = -1;
        for(auto i = mny.rbegin(); i != mny.rend(); i++){
            ll x = i->first;
            sfxmny[x] = mny[x], sfxmxy[x] = mxy[x];
            if(px != -1){
                sfxmny[x] = min(sfxmny[x], sfxmny[px]);
                sfxmxy[x] = max(sfxmxy[x], sfxmxy[px]);
            }
            px = x;
        }
        //calc ans
        ll ans = 0;
        px = -1;
        ll pmny, pmxy;
        for(auto i = mny.begin(); i != mny.end(); i++){
            ll x = i->first;
            ll cmny = max(pfxmny[x], sfxmny[x]), cmxy = min(pfxmxy[x], sfxmxy[x]);
            // cout << "X : " << x << " " << cmny << " " << cmxy << "\n";
            ans += cmxy - cmny + 1; //current column
            if(px != -1){   //all columns between
                ll amny = max(cmny, pmny), amxy = min(cmxy, pmxy);
                ll xdist = x - px - 1;
                ans += max(1ll, amxy - amny + 1) * xdist;
                if(amxy < amny) ans += amny - amxy;
            }
            px = i->first;
            pmny = cmny, pmxy = cmxy;
        }
        return ans;
    }
};

int main() {
    int n0; cin >> n0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> arg0(n0);
    for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
    auto c = DiscreteConvexHull();
    long long ret = c.minArea(arg0);
    cout << ret;
}