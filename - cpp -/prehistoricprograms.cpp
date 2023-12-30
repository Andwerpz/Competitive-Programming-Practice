#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2021 - H

//for each string, compute the number of open parentheses required before it, and the net number of open parentheses 
//it will contribute. 

//then, we split the strings into two groups; ones where the net open is non-negative, and ones where it is negative.

//we then greedily put all of the net positive ones at the front, and then put all the net negative ones at the end.
//If it is possible to create a string, then this method should create one. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    int n; cin >> n;
    vector<string> a(n);
    for (auto& s : a) cin >> s;

    vector<vector<int>> parens(n, vector<int>(3));

    for (int i = 0; i < n; ++i) {
        // cerr << "i : " << i << endl;
        int cnt = 0;
        parens[i][2] = i;
        for (int j = 0; j < a[i].size(); ++j) {
            if (a[i][j] == '(') {
                cnt++;
            } else cnt--;
            parens[i][0] = min(cnt, parens[i][0]);
        }
        parens[i][1] = cnt;
    }

    // parens => {min value, net contr, index}

    sort(parens.begin(), parens.end(), [](vector<int>& a, vector<int>& b) -> bool {
       if (a[1] == b[1]) {
            return a[0] > b[0];
       } 
       return a[1] > b[1];
    });

    // for (auto v : parens) {
    //     for (auto x : v) cerr << x << " ";
    //     cerr << endl;
    // }

    vector<vector<int>> positives, negs;
    for (int i = 0; i < n; ++i) {
        if (parens[i][1] >= 0) {
            positives.push_back(parens[i]);
        } else {
            negs.push_back(parens[i]);
        }
    }

    sort(positives.begin(), positives.end(), [](vector<int>& a, vector<int>& b) -> bool {
        return a[0] > b[0];
    });


    
    vector<int> ans;
    int cnt = 0;
    bool works = true;
    for (int i = 0; i < positives.size(); ++i) {
        ans.push_back(positives[i][2]);
        for (auto c : a[positives[i][2]]) {
            if (c == '(') cnt ++;
            else cnt --;
            if (cnt < 0) works = false;
        }
    }

    // have to do it again
    for (int i = 0; i < negs.size(); ++i) {
        // cerr << "i : " << i << endl;
        int ind = negs[i][2];
        int other_cnt = 0;
        for (int j = a[ind].size()-1; j > -1; --j) {
            // cerr << "j : " << j << endl;
            if (a[ind][j] == '(') {
                other_cnt++;
            } else other_cnt--;
            negs[i][0] = max(other_cnt, negs[i][0]);
        }
    }

    
    sort(negs.begin(), negs.end(), [](vector<int>& a, vector<int>& b) -> bool {
        return a[0] > b[0];
    });

    // vector<int> negs = solve(a, negs);

    for (int i = 0; i < negs.size(); ++i) {
        ans.push_back(negs[i][2]);
        for (auto c : a[negs[i][2]]) {
            if (c == '(') cnt ++;
            else cnt --;
            if (cnt < 0) works = false;
        }
    }

    if (!works || cnt != 0) {
        cout << "impossible" << endl;
    } else {
        for (auto x : ans) {
        cout << x+1 << endl;
        }
    }

    

    
    return 0;
}
