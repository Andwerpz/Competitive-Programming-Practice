#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2019 D

//idk how to solve this, daniel did this one. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<pair<int, int>> dna(n);
    // dna[i] = {val, s/e}

    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        int start;
        if (s[0] == 's') start = 1;
        else start = -1;
        // cerr << "s : " << s << endl;
        s.erase(s.begin());
        
        int x = stoi(s);
        dna[i] = {x, start};
    }    


    // check valids (si == ei)
    vector<int> valids(1123456, 1123456);
    for (int i = 0; i < n; ++i) {
        if (valids[dna[i].first] == 1123456) {
            // havent seen it
            valids[dna[i].first] = dna[i].second;
        } else valids[dna[i].first] += dna[i].second;
    }
    // int valid_cnt = 0;
    for (int i = 1; i <= 1000000; ++i) {
        if (valids[i] == 0) {
            valids[i] = 1;
            // valid_cnt++;
        } else valids[i] = 0;
    }

    // cerr << "valid_cnt : " << valid_cnt << endl;

    // check mins
    vector<int> mins(1123456), balance(1123456);

    for (int i = 0; i < n; ++i) {
        balance[dna[i].first] += dna[i].second;
        mins[dna[i].first] = min(mins[dna[i].first], balance[dna[i].first]);
    }

    for (int i = 1; i <= 1000000; ++i) {
        if (!valids[i]) {
            mins[i] = 1123456;
        }
    }

    // for (int i = 1; i <= 5; ++i) cerr << valids[i] << " ";
    // cerr << endl;

    // for (int i = 1; i <= 5; ++i) cerr << mins[i] << " ";
    // cerr << endl;


    // how many are at mins at each position (careful with start)
    balance.assign(1123456, 0);
    vector<bool> turned_on(1123456);
    // start
    int cnt = 0, ans = -1, best = 0;
    for (int i = 1; i <= 1000000; ++i) {
        // if (mins[i] == 0) {
        //     cerr << "i : " << i << endl;
        // }
        cnt += mins[i] == 0;
        if (mins[i] == 0) turned_on[i] = true;
    }

    best = cnt;

    // cerr << "cnt : " << cnt << endl;

    for (int i = 0; i < n; ++i) {
        if (!valids[dna[i].first]) continue;
        balance[dna[i].first] += dna[i].second;
        if (balance[dna[i].first] == mins[dna[i].first]) {
            // cerr << "hey. i : " << i << endl;
            cnt++;
            turned_on[dna[i].first] = true;
        } else if (turned_on[dna[i].first]) {
            // cerr << "hey. i : " << i << endl;
            cnt--;
            turned_on[dna[i].first] = false;
        }

        // cerr << "i : " << i << " cnt : " << cnt << endl;
        // cerr << "i : " << i << " balance : " << balance[dna[i].first] << endl;

        if (cnt > best) {
            best = cnt;
            ans = i;
        }
    }


    cout << ans + 2 << " " << best << endl;
    
    return 0;
}
