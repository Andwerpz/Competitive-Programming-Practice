#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2016 B

vector<int> dijkstra(vector<vector<pair<int, int>>>& c, int start) {
    int n = c.size();
    vector<int> dist(n, -1);
    vector<int> prev(n, -1);
    vector<bool> v(n, false);
    priority_queue<pair<ll, int>> q;
    q.push({0, start});
    dist[start] = 0;
    v[start] = true;
    while(q.size() != 0){
        int cur = q.top().second;
        int curDist = -q.top().first;
        q.pop();
        if(dist[cur] < curDist) {
            continue;
        }
        dist[cur] = curDist;
        for(int i = 0; i < c[cur].size(); i++){
            int next = c[cur][i].first;
            int nextDist = curDist + c[cur][i].second;
            if(!v[next] || dist[next] > nextDist) {
                v[next] = true;
                dist[next] = nextDist;
                prev[next] = cur;
                q.push({-nextDist, next});
            }
        }
    }
    return dist;
}

void insert(map<ll, ll>& m, ll val) {
    if(m.find(val) == m.end()) {
        m.insert({val, 0});
    }
    m[val] ++;
}

void erase(map<ll, ll>& m, ll val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(val);
    }
}

void insert(pair<ll, pair<ll, map<ll, ll>>>& g, ll val) {
    g.first ++;
    g.second.first += val;
    insert(g.second.second, val);
}

void erase(pair<ll, pair<ll, map<ll, ll>>>& g, ll val) {
    g.first --;
    g.second.first -= val;
    erase(g.second.second, val);
}

ll calc_ans(pair<ll, pair<ll, map<ll, ll>>>& g) {
    return 2ll * g.second.first * (g.first - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, b, s, r;
    cin >> n >> b >> s >> r;
    vector<vector<pair<int, int>>> c(n, vector<pair<int, int>>(0));
    for(int i = 0; i < r; i++){
        int u, v, l;
        cin >> u >> v >> l;
        u --;
        v --;
        c[u].push_back({v, l});
    }
    vector<int> dist = dijkstra(c, b);
    vector<ll> branches(b);
    for(int i = 0; i < b; i++){
        branches[i] = dist[i];
        cout << "DIST : " << branches[i] << "\n";
    }
    sort(branches.begin(), branches.end());
    vector<pair<ll, pair<ll, map<ll, ll>>>> buckets(s); //{nr members, {dist sum, multiset}}
    int ptr = 0;
    for(int i = 0; i < s; i++){
        buckets[i] = {0, {0, map<ll, ll>()}};
        if(i != s - 1){
            insert(buckets[i], branches[ptr++]);
        }
        else {
            while(ptr != branches.size()) {
                insert(buckets[i], branches[ptr++]);
            }
        }
    }
    
    while(true) {
        bool change = false;
        for(int i = s - 2; i >= 0; i--){
            if(buckets[i + 1].second.second.size() == 0){
                continue;
            }
            ll bef_ans = calc_ans(buckets[i + 1]) + calc_ans(buckets[i]);
            ll to_remove = buckets[i + 1].second.second.begin() -> first;
            erase(buckets[i + 1], to_remove);
            insert(buckets[i], to_remove);
            ll aft_ans = calc_ans(buckets[i + 1]) + calc_ans(buckets[i]);
            if(aft_ans < bef_ans) {
                change = true;
                continue;
            }
            erase(buckets[i], to_remove);
            insert(buckets[i + 1], to_remove);
        }
        if(!change) {
            break;
        }
    }
    ll ans = 0;
    for(int i = 0; i < buckets.size(); i++){
        cout << "BUCKET " << i << " : " << "\n";
        for(auto j = buckets[i].second.second.begin(); j != buckets[i].second.second.end(); j++){
            cout << j -> first << " " << j -> second << "\n";
        }
        ans += calc_ans(buckets[i]);
    }
    cout << ans << "\n";
    

    return 0;
}
