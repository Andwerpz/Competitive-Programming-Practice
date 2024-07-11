#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1986 G1, G2

//for some p[i], we can see that p[i] / gcd(p[i], i) is kinda the 'extra material' that we have 
//leftover after dividing as much as we can by i, and i / gcd(p[i], i) is the material that
//some p[j] has to account for. 

//denote a[i] = p[i] / gcd(p[i], i) and b[i] = i / gcd(p[i], i). If b[i] | a[j] and b[j] | a[i],
//then the stuff that needs to be accounted for (b[i] and b[j]) is covered by a[i] and a[j], 
//and thus p[i] * p[j] is divisible by i * j. This means that it is equivalent to count
//the number of pairs i, j where b[i] | a[j] and b[j] | a[i]. 

//ok, well now how do we count that?

//first, note that it's pretty simple to count the number of pairs where b[i] | a[j]. Just keep 
//some frequency map, f[i] = number of j where a[j] = i, and then for each b[i], check all
//of it's multiples and take the sum. 

//the difficulty arises when we also want to account for b[j] | a[i]. To do so, we can also save
//some extra information in our frequency map, namely f[i] stores the list of b[j] such that a[j] = i. 
//Then, when we iterate over f, we just look into the lists of b[j] that we get, and test each one of
//against a[i] to see if it is divisible. 

//I believe that this solution runs in O(n * log(n)), perhaps O(n^(4/3)) in the worst case. 

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

void find_divisors_helper(vector<int>& p, vector<int>& c, int ind, int val, vector<int>& ans) {
    if(ind == p.size()) {
        ans.push_back(val);
        return;
    }
    for(int i = 0; i <= c[ind]; i++){
        find_divisors_helper(p, c, ind + 1, val, ans);
        val *= p[ind];
    }
}

vector<int> find_divisors(int val) {
    vector<int> factors = find_prime_factors(val);
    map<int, int> m;
    vector<int> p(0);
    vector<int> c(0);
    for(int i = 0; i < factors.size(); i++){
        int next = factors[i];
        if(m.find(next) == m.end()) {
            p.push_back(next);
            c.push_back(0);
            m.insert({next, m.size()});
        }
        int ind = m[next];
        c[ind] ++;
    }
    vector<int> div(0);
    find_divisors_helper(p, c, 0, 1, div);
    return div;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    prime_sieve(5e5 + 1);
    //precalculate divisors
    vector<vector<int>> div(5e5 + 1, vector<int>());
    for(int i = 1; i < div.size(); i++){
        div[i] = find_divisors(i);
    }
    //abmp: for a given value of a, what are the associated values of b?
    //bamp is defined similarly
    vector<vector<int>> abmp(5e5 + 1, vector<int>(0)), bamp(5e5 + 1, vector<int>(0));
    vector<int> f(5e5 + 1, 0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> p(n);
        for(int i = 0; i < n; i++){
            cin >> p[i];
        }
        vector<int> a(n), b(n);
        for(int i = 0; i < n; i++){
            a[i] = p[i] / gcd(i + 1, p[i]);
            b[i] = (i + 1) / gcd(i + 1, p[i]);
        }
        //populate ab and ba mp
        for(int i = 0; i < n; i++){
            abmp[a[i]].push_back(b[i]);
            bamp[b[i]].push_back(a[i]);
        }
        ll ans = 0;
        for(int i = 0; i < n; i++){
            if(a[i] % b[i] == 0){
                ans --;
            }
        }
        sort(b.begin(), b.end());
        for(int i = 0; i < n; i++){
            if(i != 0 && b[i - 1] == b[i]){
                continue;
            }
            int cb = b[i];
            //populate f
            for(int j = 0; j < bamp[cb].size(); j++){
                for(int k = 0; k < div[bamp[cb][j]].size(); k++){
                    f[div[bamp[cb][j]][k]] ++;
                }
            }
            //calc ans for current b. Look for all the a that divides cb
            for(int j = cb; j <= n; j += cb) {
                for(int k = 0; k < abmp[j].size(); k++){
                    int ca = abmp[j][k];
                    ans += f[ca];
                }
            }
            //clear f
            for(int j = 0; j < bamp[cb].size(); j++){
                for(int k = 0; k < div[bamp[cb][j]].size(); k++){
                    f[div[bamp[cb][j]][k]] --;
                }
            }
        }
        //account for doublecounting
        ans /= 2;
        cout << ans << "\n";
        //clear ab and ba mp
        for(int i = 0; i < n; i++){
            if(abmp[a[i]].size() != 0){
                abmp[a[i]].clear();
            }
            if(bamp[b[i]].size() != 0){
                bamp[b[i]].clear();
            }
        }
    }
    
    return 0;
}