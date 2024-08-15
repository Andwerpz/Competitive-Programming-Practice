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

//Codeforces - 2004D

//if the two cities share a color, then the minimum cost is to just go directly from x to y. 

//otherwise, they don't share a color, and we must travel through another city to get from x to y. 
//we can just try all 4 combinations of cities that we might travel through, for example if city x is
//'BG' and city y is 'RY' then we'd try 'BR', 'BY', 'GR', 'GY'. We can use a set to identify the closest 
//of each type of city to x, and then move directly to y. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string t_str = "BGRY";
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vector<string> type(n);
        map<string, set<int>> occ;
        for(int i = 0; i < n; i++){
            cin >> type[i];
            occ[type[i]].insert(i);
        }
        for(int i = 0; i < q; i++){
            int x, y;
            cin >> x >> y;
            x --;
            y --;
            if(x > y){
                swap(x, y);
            }
            bool share = false;
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 2; k++){
                    if(type[x][j] == type[y][k]) {
                        share = true;
                    }
                }
            }
            if(share){
                cout << abs(x - y) << "\n";
                continue;
            }
            int minc = 1e9;
            for(int j = 0; j < 2; j++){
                for(int k = 0; k < 2; k++){
                    string n_type = string(1, type[x][j]) + string(1, type[y][k]);
                    sort(n_type.begin(), n_type.end());
                    auto ptr = occ[n_type].lower_bound(x);
                    if(ptr != occ[n_type].end()) {
                        int z = *ptr;
                        minc = min(minc, abs(x - z) + abs(z - y));
                    }
                    if(ptr != occ[n_type].begin()) {
                        ptr --;
                        int z = *ptr;
                        minc = min(minc, abs(x - z) + abs(z - y));
                    }
                }
            }
            cout << (minc == 1e9? -1 : minc) << "\n";
        }
    }
    
    return 0;
}