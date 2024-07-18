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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1994D

//first, notice that we can consider the operations in any order, we just need to make sure that we don't add the same
//edge twice. 

//Lets consider the operations in descending order from n - 1 to 1. Notice that at operation n - 1, there are n 
//components that we still need to connect, which are the n nodes. Note that the difference between two values a[i], 
//a[j] is divisible by x if a[i] % x == a[j] % x. Since there can only be n - 1 unique a[i] % (n - 1), there 
//must exist 2 nodes where the remainders match. This can be shown to be true for all operations. 

//to find the edge to create in each operation, we can use DSU, and keep track of the last node we saw with a given
//remainder. 

struct DSU {
    int N;
    vector<int> dsu, sz;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        this->sz = vector<int>(n, 1);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    int get_sz(int a){
        return sz[find(a)];
    }

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        sz[ra] += sz[rb];
        return true;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vi a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        stack<pii> ans;
        DSU dsu(n);
        for(int i = n - 1; i >= 1; i--){
            vi mod(n);
            for(int j = 0; j < n; j++){
                mod[j] = a[j] % i;
            }
            vi pm(i, -1);
            for(int j = 0; j < n; j++){
                if(pm[mod[j]] != -1 && dsu.unify(j, pm[mod[j]])){
                    ans.push({j, pm[mod[j]]});
                    break;
                }
                pm[mod[j]] = j;
            }
        }
        if(ans.size() != n - 1){
            cout << "NO" << "\n";
            continue;
        }
        cout << "YES\n";
        while(ans.size() != 0){
            cout << ans.top().first + 1 << " " << ans.top().second + 1 << "\n";
            ans.pop();
        }
    }
    
    return 0;
}