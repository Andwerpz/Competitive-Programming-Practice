#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2020 - O

//group all the points into sets where the latitude measurements match up. Then, we can sort the longitude
//measurements and create a difference array, taking into account the wrap around. 

//if the measurements come from the same planet, then the differernce array between the matching set of 
//latitude measurements should just differ by a rotation. Use a string matching algorithm like kmp to find 
//all possible rotations. 

//then, take the intersection of all possible sets of rotations, and if the intersection is non-zero, then
//the measurements could be from the same planet. 

vector<int> pi(const vector<int> &s) {
    vector<int> p(s.size());

    for(int i = 1; i < s.size(); i++) {
        int g = p[i-1];
        while(g && s[i] != s[g]) {
            g = p[g - 1];
        }
        p[i] = g + (s[i] == s[g]);
    }
    return p;
}

vector<int> match(const vector<int>& s, const vector<int> &pat) {
    vector<int> temp;
    for(auto x : pat) temp.push_back(x);
    temp.push_back(-1);
    for(auto x : s) temp.push_back(x);

    vector<int> p = pi(temp), res;
    for(int i = p.size() - s.size(); i < p.size(); i++) {
        if(p[i] == pat.size()) {
            res.push_back(i - 2 * pat.size());
        }
    }
    return res;
}

set<int> get_diffs(vector<int> &a, vector<int> &b) {
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    vector<int> adiffs;
    vector<int> bdiffs;

    a.push_back(a.front() + 360 * 10000);
    b.push_back(b.front() + 360 * 10000);

    for(int i = 0; i < a.size() - 1; i++) {
        adiffs.push_back(a[i+1] - a[i]);
        bdiffs.push_back(b[i+1] - b[i]);
    }

    for(int i = 0; i < a.size() - 1; i++) {
        adiffs.push_back(a[i+1] - a[i]);
    }

    vector<int> diffs = match(adiffs, bdiffs);

    // cout << "a: ";

    // for(auto x : adiffs) cout << x << " ";

    // cout << "\nb: ";
    // for(auto x : bdiffs) cout << x << " ";

    // cout << "\nmatches: ";
    // for(auto x : diffs) cout << x << " ";

    // cout << '\n';
    // set<int> ans(diffs.begin(),diffs.end());

    set<int> ans;

    for(int i = 0; i < diffs.size(); i++) {
        int original = b[0];
        int next = a[diffs[i]];
        if(next < original) {
            next += 360 * 10000;
        }
        ans.insert(next - original);
    }
//  cout << "ans: ";
//  for(auto x : ans) cout << x << " ";
//  cout << '\n';
    return ans;
}

ld epsilon = 1e-10;

int parse_int(ld x) {
    return (int) (x * 10000.000001);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> a(n);
    vector<pair<int,int>> b(n);

    // for(auto &x: a) cin >> x.first >> x.second;
    // for(auto &x: b) cin >> x.first >> x.second;

    for(int i = 0; i < n; i++) {
        ld x; cin >> x;
        int num = parse_int(x);
        ld y; cin >> y;
        int numy = parse_int(y);
        a[i] = {num, numy};
        //cout << "adding coord: " << num << " " << numy << endl;
    }

    for(int i = 0; i < n; i++) {
        ld x; cin >> x;
        int num = parse_int(x);
        ld y; cin >> y;
        int numy = parse_int(y);
        b[i] = {num, numy};
        //cout << "adding coord: " << num << " " << numy << endl;
    }

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    vector<set<int>> diffs;
    int prevx = INT_MIN;
    vector<int> avals;
    vector<int> bvals;
    bool same = true;

    for(int i = 0; i < n; i++) {    
        if(a[i].first != b[i].first) {
            same = false;
            break;
        }
        if(a[i].first != prevx) {
            if(i != 0) {
                diffs.push_back(get_diffs(avals,bvals));
            }
            avals.clear();
            bvals.clear();
            prevx = a[i].first;
        }
        avals.push_back(a[i].second);
        bvals.push_back(b[i].second);
    }

    if(!same) {
        cout << "Different\n";
        return 0;       
    }
    if(avals.size() && bvals.size()) {
        diffs.push_back(get_diffs(avals,bvals));
    }
    if(diffs.size() == 0) {
        cout << "Different\n";
        return 0;
    }
    set<int> common = diffs[0];

    for(int i = 1; i < diffs.size(); i++) {
        set<int> inter;
        for(auto x : common) {
            if(diffs[i].find(x) != diffs[i].end()) {
                inter.insert(x);
            }
        }
        common = inter;
    }

    if(same && common.size()) {
        cout << "Same\n";
    } else {
        cout << "Different\n";
    }
    
    return 0;
}
