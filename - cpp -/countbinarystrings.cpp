#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1767C

//first, using the 1 constraints, we can compress the string, since any character under the same 1 constraint needs to
//be the same. We can compress the string using DSU. 

//next, to find out how many ways there are to satisfy the 2 constraints, we can use dp. 
//dp[i][j] = nr ways to make the prefix given
//i = nr elements placed so far excluding first element
//j = nr 2 constraints satisfied. 

//since there could be around n^2 2 constraints, this dp seems like it's going to be n^5, as for each dp state we need
//to do around n^2 processing time, but we can cut this down to n^3 by observing that if a 2 constraint completely
//contains another 2 constraint, then the outer constraint is completely redundant. 

//so to guarantee that we can get at most n constraints, we just pick the shortest 2 constraint that starts at each 
//index. 

struct DSU {
    int N;
    vector<int> dsu;

    DSU(int n) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
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

    //ret true if updated something
    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        dsu[rb] = ra;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i; j++){
            cin >> a[i][j];
        }
    }
    //use dsu to compress the array
    DSU dsu(n);
    for(int i = 0; i < n; i++){
        int r = -1;
        for(int j = 0; j < n - i; j++) {
            if(a[i][j] == 1) {
                r = i + j + 1;
            }
        }
        for(int j = i + 1; j < r; j++){
            dsu.unify(j - 1, j);
        }
    }
    map<int, int> m;
    for(int i = 0; i < n; i++){
        if(!m.count(dsu.find(i))) {
            m.insert({dsu.find(i), m.size()});
        }
    }
    //list out '2' constraints, and compress them
    vector<pair<int, int>> c(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i; j++){
            if(a[i][j] == 2){
                int l = m[dsu.find(i)];
                int r = m[dsu.find(i + j)];
                c.push_back({l, r});
                break;
            }
        }
    }
    //run dp
    n = m.size();
    ll mod = 998244353;
    //dp[i][j] = nr ways given
    //i = nr elements we've placed (excluding first)
    //j = nr constraints we've satisfied
    vector<vector<ll>> dp(n, vector<ll>(c.size() + 1, 0));
    dp[0][0] = 2;   //either '0' or '1'
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j <= c.size(); j++){
            //place same
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;
            //place different
            int nj = j;
            while(nj != c.size()) {
                if(i >= c[nj].first && i < c[nj].second) {
                    nj ++;
                }
                else {
                    break;
                }
            }
            dp[i + 1][nj] = (dp[i + 1][nj] + dp[i][j]) % mod;
        }
    }
    cout << dp[n - 1][c.size()] << "\n";
    
    return 0;
}
