#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1978F

//first, observe that we can turn this from a grid problem into an array problem. Notice that any value in the grid
//will always connect to it's same value neighbors diagonally (since k >= 2). As for the different neighbors, it will
//connect to them if they are within a distance of k in the original array. 

//so now we have an array where a[i] can connect to a[j] if |i - j| <= k, and gcd(a[i], a[j]) > 1. Note that gcd(a[i], a[j])
//is greater than 1 iff a[i] and a[j] share a prime factor. Since a[i] is limited to around 10^6, it can only have around
//20 unique prime factors, so we can just keep a map M where M[p] is the last index where we saw a number with prime factor p.
//If |M[p] - i| <= k, then we can connect a[M[p]] and a[i]. 

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

vector<int> lp; //lowest prime factor 
vector<int> pr; //prime list

void prime_sieve(int n) {
    lp = vector<int>(n + 1);
    pr = vector<int>(0);
    for(int i = 2; i <= n; i++) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= n; j++) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
}

vector<int> find_prime_factors(int val) {
    vector<int> factors(0);
    while(val != 1) {
        factors.push_back(lp[val]);
        val /= lp[val];
    }
    return factors;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(1e6 + 100);
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        ll o_seg = 0;
        {
            vector<int> tmp(0);
            for(int i = 1; i < n; i++){
                tmp.push_back(a[i]);
                if(a[i] == 1) {
                    o_seg += i - 1;
                }
            }
            for(int i = 0; i < n; i++){
                tmp.push_back(a[i]);
                if(a[i] == 1){
                    o_seg += n - i - 1;
                }
            }
            n = tmp.size();
            a = tmp;
        }
        DSU dsu(n);
        map<int, int> m;
        for(int i = 0; i < n; i++){
            vector<int> pf = find_prime_factors(a[i]);
            for(int j = 0; j < pf.size(); j++){
                int val = pf[j];
                if(m.count(val) && i - m[val] <= k) {
                    dsu.unify(i, m[val]);
                }
                m[val] = i;
            }
        }
        set<int> s;
        for(int i = 0; i < n; i++) {
            s.insert(dsu.find(i));
        }
        cout << s.size() + o_seg << "\n";
    }
    
    return 0;
}