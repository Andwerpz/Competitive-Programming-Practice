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

//Codeforces - 1991F

//if our triangle side lengths are a, b, c, where a >= b >= c, then the only requirement for it to be
//valid is a - b < c. 

//what is the largest subarray such that there is no way to create a triangle? If we set c = 1, b = 1, then
//the minimum a must be is 2. Then, if c = 1, b = 2, a must be 3. And so on. You can see that this forms the
//fibonacci sequence, and it will reach 10^9 in around 50 terms. So any subarray larger than 50 terms will
//be guaranteed to form at least 1 triangle. 

//for 2 triangles, we can see that it only requires at least 53 terms. This is because after removing the 
//first triangle, we have 50 terms, which is enough to guarantee the second triangle. 

//for queries that are less than 50 terms, we have to manually figure out if it's possible. 
//first, we can sort the array. There are two possibilities:
//1. the two triangles are disjoint segments of 3 consecutive elements each
//2. the two triangles are merged together in 6 consecutive elements. 

//checking 1. is pretty easy, 2. is more annoying. 

bool checktri(int a, int b, int c){
    if(b > a){
        swap(a, b);
    }
    if(c > a){
        swap(a, c);
    }
    if(c > b){
        swap(b, c);
    }
    return a - b < c;
}

bool check1(vi& a){
    int cnt = 0;
    for(int i = 0; i < a.size() - 2; i++){
        if(a[i + 2] - a[i + 1] < a[i]) {
            i += 2;
            cnt ++;
        }
    }
    return cnt >= 2;
}

bool check2(vi& _a){
    for(int i = 0; i < _a.size() - 5; i++){
        int a = _a[i + 0];
        int b = _a[i + 1];
        int c = _a[i + 2];
        int d = _a[i + 3];
        int e = _a[i + 4];
        int f = _a[i + 5];
        bool valid = false;
        valid = valid | (checktri(a, b, c) && checktri(d, e, f));
        valid = valid | (checktri(a, b, d) && checktri(c, e, f));
        valid = valid | (checktri(a, b, e) && checktri(c, d, f));
        valid = valid | (checktri(a, b, f) && checktri(c, d, e));
        valid = valid | (checktri(a, c, d) && checktri(b, e, f));
        valid = valid | (checktri(a, c, e) && checktri(b, d, f));
        valid = valid | (checktri(a, c, f) && checktri(b, d, e));
        valid = valid | (checktri(a, d, e) && checktri(b, c, f));
        valid = valid | (checktri(a, d, f) && checktri(b, c, e));
        valid = valid | (checktri(a, e, f) && checktri(b, c, d));
        if(valid){
            return true;
        }
    }
    return false;
}

bool is_valid(vi& a) {
    sort(a.begin(), a.end());
    return check1(a) || check2(a);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l --;
        if(r - l >= 50){
            cout << "YES\n";
            continue;
        }
        vi sub(r - l);
        for(int j = 0; j < sub.size(); j++){
            sub[j] = a[l + j];
        }
        cout << (is_valid(sub)? "YES" : "NO") << "\n";
    }
    
    return 0;
}