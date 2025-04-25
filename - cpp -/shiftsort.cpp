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

//Spring 2025 Columbia University Local Contest - K

//observe that if a cyclic shift only has 2 elements to shift, then it essentially swaps them. 

//suppose that k = a is a 2 element shift. Then, i can use the shift where k = 1 to shift any two elements 
//that are distance a apart to the correct positions, then use the k = a shift to swap them. So for any 
//2 element cyclic shift length a, I can swap any two elements that are a apart. 

//note that n = 10 is actually the smallest n in which there are two different shift lengths such that they only 
//have 2 elements. So it's probably pretty important to use these to create swaps of other lengths. 

//I'll call level 0 swaps the ones that are given to us by a single cyclic shift. A level 1 swap is constructed 
//using multiple level 0 swaps. If A is the smallest level 0 swap and B is the largest level 0 swap, then 
//the length range of level 1 swaps are [1, B - A], as we can always use level 0 swaps to swap to some third 
//intermediate value reachable by both of the swap targets via level 0 swap

//A level 2 swap is any other length. If you construct the level 2 swaps correctly, then you'll see that there
//shoudn't be that many of them that exceed 30 operations to perform. 

//now that we can swap any element in the array with any other, we can trivially sort the array using 
//selection sort.

int n;
vector<pii> ans(0);
int off = 0;

int l0_min, l0_max;
int l1_min, l1_max;

//off = i means that the element at index i is currently at index 0
void shift_to_off(int noff) {
    while(noff < off) noff += n;
    if(noff == off) return;
    int diff = noff - off;
    ans.push_back({1, diff});
    off = noff;
    off %= n;
}

//swaps elements at indexes i and j
void do_swap(int i, int j) {
    while(i < 0) i += n;
    while(j < 0) j += n;
    i %= n, j %= n;
    if(i == j) return;
    while(j < i) j += n;
    if(n - (j - i) < j - i) {
        swap(i, j);
        i %= n, j %= n;
        while(j < i) j += n;
    }
    // cout << "I J : " << i << " " << j << endl;
    assert(i < j && j - i <= l0_max);
    int diff = j - i;
    if(diff >= l0_min) {
        //level 0 swap
        shift_to_off(i - diff + 1);
        // cout << "L0 SWAP : " << i << " " << j << " " << diff << " " << off << "\n";
        ans.push_back({diff, 1});
    }
    else if(diff <= l1_max) {
        //level 1 swap
        // cout << "L1 SWAP : " << i << " " << j << "\n";
        int tmp = i + l0_max;
        assert(tmp - j >= l0_min);
        do_swap(i, tmp);
        do_swap(j, tmp);
        do_swap(i, tmp);
    }
    else {
        //level 2 swap
        int tmpi = i + l0_max, tmpj = j + l0_min;
        assert(tmpi != tmpj);
        // cout << "L2 SWAP : " << i << " " << j << " " << tmpi << " " << tmpj << "\n";
        do_swap(i, tmpi);
        do_swap(j, tmpj);
        do_swap(tmpi, tmpj);
        do_swap(i, tmpi);
        do_swap(j, tmpj);
    }
}

void verify(vi p) {
    // for(int i = 0; i < n; i++) cout << p[i] + 1 << " ";
    // cout << endl;
    for(pii& x : ans) {
        int k = x.first, amt = x.second;
        vi inds;
        for(int i = k - 1; i < n; i += k) inds.push_back(i);
        vi ninds(inds.size());
        for(int i = 0; i < inds.size(); i++) ninds[i] = inds[(i + amt) % inds.size()];
        vi np = p;
        for(int i = 0; i < inds.size(); i++) np[inds[i]] = p[ninds[i]];
        p = np;
        // for(int i = 0; i < n; i++) cout << p[i] + 1 << " ";
        // cout << endl;
    }
    for(int i = 1; i < p.size(); i++) assert(p[i] == p[i - 1] + 1);
}

void solve(vi p) {
    ans.clear();
    for(int i = 0; i < n; i++){
        int ind = -1;
        for(int j = i; j < n; j++) if(p[j] == i) ind = j;
        // cout << "DO SWAP : " << i << " " << ind << "\n";
        do_swap(i, ind);
        swap(p[i], p[ind]);
    }
    shift_to_off(0);
    assert(ans.size() <= p.size() * 30);
}

void test(int n) {
    int cnt = 0;
    while(true) {
        cnt ++;
        vi p(n);
        for(int i = 0; i < n; i++) p[i] = i;
        random_shuffle(p.begin(), p.end());
        solve(p);
        verify(p);
        if(cnt % 1000 == 0) cout << "CNT : " << cnt << endl;
    }   
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    srand(time(0));
    cin >> n;
    l0_min = n / 3 + 1, l0_max = n / 2;
    l1_min = 1, l1_max = l0_max - l0_min;
    // for(int i = 1; i <= l0_max; i++){
    //     do_swap(0, i);
    //     cout << "I : " << i << " " << ans.size() << "\n";
    //     ans.clear();
    // }
    
    vi p(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
        p[i] --;
    }
    solve(p);
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++) cout << ans[i].first << " " << ans[i].second << "\n";
    
    return 0;
}