#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ACPC 2023 Fall Contest H

//note that every platform must have exactly one platform pointing towards it, and there are always
//two ways to get to this platform, either from the top or from the left. 

//this also implies that the platforms that are able to point towards it must be facing the same direction,
//because if they were facing different directions, they would either be both pointing towards the 
//platform, or both pointing away. 

//then, we just find how many components of platform are 'locked' into pointing the same direction, and
//the answer is just 2 to the power of the count. 

//basic union find implementation with path compression
struct DSU {
    int N;
    int nr_components;
    vector<int> dsu;

    DSU(int n) {
        this->N = n;
        this->nr_components = n;
        this->dsu = vector<int>(n, 0);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    void dsu_init() {
        for(int i = 0; i < N; i++){
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        nr_components --;
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    vector<vector<int>> id(n, vector<int>(n, -1));
    int id_ptr = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 'P') {
                id[i][j] = id_ptr ++;
            }
        }
    }
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout << id[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    DSU dsu(id_ptr);
    vector<vector<int>> c(id_ptr, vector<int>(0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(id[i][j] == -1){
                continue;
            }
            int right = -1;
            int left = -1;
            //right
            for(int k = 1; k <= n; k++){
                int n_ind = (j - k + n) % n;
                if(id[i][n_ind] != -1){
                    right = id[i][n_ind];
                    break;
                }
            }
            //down
            for(int k = 1; k <= n; k++){
                int n_ind = (i - k + n) % n;
                if(id[n_ind][j] != -1){
                    left = id[n_ind][j];
                    break;
                }
            }
            //cout << id[i][j] << " " << right << " " << left << "\n";
            dsu.unify(right, left);
        }
    }
    // cout << "NR COMPONENTS: " << dsu.nr_components << "\n";
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         if(id[i][j] == -1){
    //             cout << ".";
    //         }
    //         else {
    //             cout << dsu.find(id[i][j]);
    //         }
    //     }
    //     cout << "\n";
    // }
    ll ans = 1;
    for(int i = 0; i < dsu.nr_components; i++){
        ans <<= 1;
    }
    cout << ans << "\n";
    
    return 0;
}
