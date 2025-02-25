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

ll randstate = 1;
ll rand(ll up) {
    ll ans = (randstate % up);
    randstate = (16807ll * randstate) % 2147483647ll;
    return ans;
}

vi dr = {-1, -1, -1, 0, 0, 1, 1, 1};
vi dc = {-1, 0, 1, -1, 1, -1, 0, 1};
void incq(int r, int c, int n, vvi& a, int inc) {
    for(int i = 1; i < n; i++){
        for(int j = 0; j < 8; j++){
            int nr = r + dr[j] * i;
            int nc = c + dc[j] * i;
            if(nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
            a[nr][nc] += inc;
        }
    }
}

class QueenInterference {
public:
    int numSteps(int n) {
        vi qpos(n);
        vvi a(n, vi(n, 0));
        for(int i = 0; i < qpos.size(); i++){
            qpos[i] = rand(n);
            incq(qpos[i], i, n, a, 1);
        }
        int ans = 0;
        while(true){
            //check if position is good
            bool good = true;
            vi r(0);
            for(int i = 0; i < qpos.size(); i++){
                if(a[qpos[i]][i]) good = false, r.push_back(i);
            }
            if(good) break;
            //do alteration
            ans ++;
            int qc = r[rand(r.size())];
            int qr = qpos[qc];
            incq(qr, qc, n, a, -1);
            int minr = 1e9;
            vi minpos(0);
            for(int i = 0; i < n; i++){
                if(a[i][qc] < minr) minr = a[i][qc], minpos.clear();
                if(a[i][qc] == minr) minpos.push_back(i);
            }
            int nr = minpos[0];
            if(minpos.size() > 1) {
                nr = minpos[rand(minpos.size())];
            }
            qpos[qc] = nr;
            incq(nr, qc, n, a, 1);
        }
        return ans;
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = QueenInterference();
    int ret = c.numSteps(arg0);
    cout << ret;
}