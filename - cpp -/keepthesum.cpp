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

//Codeforces - 2103E

// if you can do an operation, then you can always sort the array?
// you can swap any two elements that add up to k
// you can sort all the elements that are symmetrical around k
// if two elements are symmetrical around k, you can change their 'band' to any other band
// the difference between the number of high and low elements in each band is fixed
// this implies that if there is an imbalance in some band, then those numbers in that band are stuck

// maybe can convert every convertable number into the same band, then use that band as an intermediate to fix everything else

// pick two convertable numbers, and a third arbitrary one. You can swap the arbitrary number with any of the convertable numbers
// k = 4
// 3 0 4
// 3 1 3
// 1 3 3
// 0 4 3

// how to swap two arbitrary numbers?
// k = 5
// 1 2 0 5
// 1 2 2 3
// 1 1 2 4
// 2 1 2 3
// 2 1 0 5
// can do in 3 operations at most (last operation was just for clarity)

//from here, just sort the array using selection sort. If it's not already sorted and there are no convertable numbers, 
//then it's impossible.

vi a;
int k, p1, p2;
vector<vi> ans;

//swap p1 with ind
void convert_swap(int ind) {
    assert(a[p1] + a[p2] == k);
    if(p1 == ind) return;
    if(ind == p2) {
        swap(p1, p2);
        return;
    }
    // cout << "CONVERT SWAP : " << p1 << " " << p2 << " " << ind << endl;
    int x = a[p1] - a[ind];
    if(x != 0) {
        a[p1] -= x, a[p2] += x;
        ans.push_back({p1, p2, x});
    }
    p1 = ind;
}

//swap ind1, ind2
void nonconvert_swap(int ind1, int ind2) {
    if(ind1 == ind2) return;
    // cout << "SWAP : " << ind1 << " " << ind2 << "\n";
    // for(int x : a) cout << x << " ";
    // cout << endl;
    int op1 = p1;
    convert_swap(ind1);
    convert_swap(ind2);
    convert_swap(op1);
    // for(int x : a) cout << x << " ";
    // cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n >> k;
        a = vi(n);
        ans = vvi(0);
        for(int i = 0; i < n; i++) cin >> a[i];
        //see if already sorted
        {
            bool sorted = true;
            for(int i = 1; i < n; i++) if(a[i] < a[i - 1]) sorted = false;
            if(sorted) {
                cout << "0\n";
                continue;
            }
        }
        //find convertable pair
        p1 = -1, p2 = -1;
        {
            map<int, int> m;
            for(int i = 0; i < n; i++) {
                if(m.count(k - a[i])) p1 = i, p2 = m[k - a[i]];
                m[a[i]] = i;
            }
        }
        if(p1 == -1) {
            cout << "-1\n";
            continue;
        }
        //sort array, first make convertable pair into first and last element of array
        convert_swap(0);
        convert_swap(p2);
        convert_swap(n - 1);
        convert_swap(p2);
        //sort array, selection sort
        set<pii> s; //{val, ind}
        for(int i = 1; i < n - 1; i++) s.insert({a[i], i});
        for(int i = 1; i < n - 1; i++){
            pii next = *s.begin();
            s.erase(next);
            // cout << "NEXT : " << next.first << " " << next.second << "\n";
            if(next.second == i) continue;
            pii cur = {a[i], i};
            s.erase(cur);
            nonconvert_swap(next.second, cur.second);
            s.insert({a[next.second], next.second});
        }
        //make a[p1] = 0, a[p2] = k
        // cout << "P1 P2 : " << p1 << " " << p2 << endl;
        assert(p1 == 0 && p2 == n - 1);
        if(a[0] != 0) {
            ans.push_back({p1, p2, a[0]});
            a[n - 1] += a[0], a[0] -= a[0];
        }
        // for(int x : a) cout << x << " ";
        // cout << "\n";
        cout << ans.size() << "\n";
        for(vi x : ans) cout << x[0] + 1 << " " << x[1] + 1 << " " << x[2] << "\n";
    }
    
    return 0;
}