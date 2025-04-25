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

//USACO 2025 US Open - Gold P2

//define f[i] as the number of votes that the ith person has. Say that person z has the most amount of votes. 
//We can choose cows x, y, as the two leaders if f[x] + f[y] >= f[z]. If this is not true, then we can't 
//gerrymander f[z] voters between x and y. 

//so after every query, we just need to find (x, y) such that f[x] + f[y] >= f[z] and |x - y| is maximized. 
//Observe that if you computed the prefix and suffix maximum of f, you can solve this in O(n) time using 
//two pointers. How can we speed this up?

//observe that there are at most around sqrt(n) unique values in f, and actually most of the values in the
//prefix and suffix sum of f are duplicates. If we just keep track of these sqrt(n) unique values and their 
//leftmost and rightmost positions, we can get the same information as the prefix and suffix arrays but in
//just O(sqrt(n)) space and time. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    //keep track of all unique elements. 
    //for each unique element, keep track of the first and last occurrence
    //a[i] = what does the ith person vote for
    //f[i] = how many votes does the ith person have
    //occ[i] = for some amount of votes i, the set of cows that have that amount
    //u = set of unique elements in f
    vi f(n + 1, 0), a(n);
    set<int> u;
    vector<set<int>> occ(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
        f[a[i]] ++;
    }
    for(int i = 0; i < n; i++){
        occ[f[i]].insert(i);
        u.insert(f[i]);
    }
    while(q--){
        //handle query
        int ind, x;
        cin >> ind >> x;
        ind --, x --;
        occ[f[a[ind]]].erase(a[ind]);
        if(occ[f[a[ind]]].size() == 0) u.erase(f[a[ind]]);
        f[a[ind]] --;
        occ[f[a[ind]]].insert(a[ind]);
        if(occ[f[a[ind]]].size() == 1) u.insert(f[a[ind]]);
        a[ind] = x;
        occ[f[a[ind]]].erase(a[ind]);
        if(occ[f[a[ind]]].size() == 0) u.erase(f[a[ind]]);
        f[a[ind]] ++;
        occ[f[a[ind]]].insert(a[ind]);
        if(occ[f[a[ind]]].size() == 1) u.insert(f[a[ind]]);
        // cout << "DONE HANDLE QUERY : " << u.size() << endl;
        //build pfx, sfx arrays
        //pfx : val ind monotonically increasing
        //sfx : val ind monotonically decreasing
        vector<pii> pfx, sfx;   //{val, ind}
        for(auto i = u.rbegin(); i != u.rend(); i++){
            int val = *i;
            if(val == 0) continue;
            int focc = *occ[val].begin(), locc = *occ[val].rbegin();
            // cout << "FOCC LOCC : " << focc << " " << locc << " " << val << endl;
            if(pfx.size() == 0 || pfx[pfx.size() - 1].second > focc) {
                pfx.push_back({val, focc});
            }
            if(sfx.size() == 0 || sfx[sfx.size() - 1].second < locc) {
                sfx.push_back({val, locc});
            }
        }
        reverse(pfx.begin(), pfx.end());
        // cout << "PFX : " << "\n";
        // for(int i = 0; i < pfx.size(); i++) cout << pfx[i].first << " " << pfx[i].second << "\n";
        // cout << "SFX : \n";
        // for(int i = 0; i < sfx.size(); i++) cout << sfx[i].first << " " << sfx[i].second << "\n";
        //calc ans
        int tgt = *u.rbegin();
        int sptr = 0, ans = 0;
        for(int i = 0; i < pfx.size(); i++){
            while(sptr + 1 != sfx.size() && sfx[sptr + 1].first + pfx[i].first >= tgt) sptr ++;
            if(sfx[sptr].first + pfx[i].first >= tgt) ans = max(ans, sfx[sptr].second - pfx[i].second);
        }
        cout << ans << "\n";
    }
    
    return 0;
}