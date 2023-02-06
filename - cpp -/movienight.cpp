#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ICPC North America Qualifier 2022 G

ll mod = 1e9 + 7;

ll solve(set<int>& inCycle, vector<bool>& v, vector<vector<int>>& c, int i) {
    ll ans = 1;
    v[i] = true;
    for(int j = 0; j < c[i].size(); j++){
        int next = c[i][j];
        if(inCycle.find(next) != inCycle.end()) {
            //cout << next << " IN CYCLE" << endl;
            continue;
        }
        ans *= solve(inCycle, v, c, next) + 1;
        ans %= mod;
    }
    //cout << "ANS : " << ans << " " << i << endl;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        c[a[i]].push_back(i);
    }
    ll ans = 1;
    vector<bool> isCycle(n, false);
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++){
        if(v[i]) {
            continue;
        }
        //cout << "I : " << i << endl;
        v[i] = true;
        int cur = i;
        stack<int> path;
        path.push(cur);
        while(!v[a[cur]]) {
            cur = a[cur];
            v[cur] = true;
            path.push(cur);
            //cout << "V : " << cur << endl;
        }
        set<int> inCycle;
        inCycle.insert(a[cur]);
        ll cnt = 1;
        //cout << "CYCLE :" << endl;
        while(inCycle.find(path.top()) == inCycle.end()) {
            int nextInCycle = path.top();
            inCycle.insert(nextInCycle);
            path.pop();
        }
        for(auto j = inCycle.begin(); j != inCycle.end(); j++) {
            int nextInCycle = *j;
            //cout << "SOLVE NEXT : " << nextInCycle << endl;
            ll nextAns = solve(inCycle, v, c, nextInCycle);
            //cout << "NANS : " << nextAns << endl;
            cnt *= nextAns;
            cnt %= mod;
        }
        //cout << "CNT : " << cnt << endl;
        ans *= (cnt + 1);
        ans %= mod;
    }
    ans --;
    if(ans < 0){
        ans += mod;
    }
    cout << ans << "\n";
    
    return 0;
}
