#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

//3rd Universal Cup, Stage 13 Sendai - O

//can reinterpret into a maximum independent set on bipartite graph. 

//observe that if two constraints intersect (not completely contain, intersect), then they can both be selected
//iff the parities of their starting points match. If they are not intersecting, then they are independent. 

//So imagine each constraint is an node, and two nodes are connected by an edge iff they are intersecting and 
//their parities don't match. What we have here is a bipatite graph and we want to pick the most nodes such that 
//no two selected nodes are connected by an edge. This is exactly MIS on a bipartite graph. 

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
	if (btoa[j] == -1) return 1;
	vis[j] = 1; int di = btoa[j];
	for (int e : g[di])
		if (!vis[e] && find(e, g, btoa, vis)) {
			btoa[e] = di;
			return 1;
		}
	return 0;
}
int dfsMatching(vector<vi>& g, vi& btoa) {
	vi vis;
	rep(i,0,sz(g)) {
		vis.assign(sz(btoa), 0);
		for (int j : g[i])
			if (find(j, g, btoa, vis)) {
				btoa[j] = i;
				break;
			}
	}
	return sz(btoa) - (int)count(all(btoa), -1);
}

vi cover(vector<vi>& g, int n, int m) {
	vi match(m, -1);
	int res = dfsMatching(g, match);
    // cout << "RES : " << res << "\n";
	vector<bool> lfound(n, true), seen(m);
	for (int it : match) if (it != -1) lfound[it] = false;
	vi q, cover;
	rep(i,0,n) if (lfound[i]) q.push_back(i);
	while (!q.empty()) {
		int i = q.back(); q.pop_back();
		lfound[i] = 1;
		for (int e : g[i]) if (!seen[e] && match[e] != -1) {
			seen[e] = true;
			q.push_back(match[e]);
		}
	}
	rep(i,0,n) if (!lfound[i]) cover.push_back(i);
	rep(i,0,m) if (seen[i]) cover.push_back(n+i);
	assert(sz(cover) == res);
	return cover;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int n, m; cin >> n >> m;
    vector<pi> a(m);
    for (auto& x : a)
        cin >> x.first >> x.second;

    for (auto& x : a) {
        x.first--, x.second--;
    }
    
    // cerr << "a\n";
    // for (auto x : a) 
    //     cerr << x.first << " " << x.second << endl;

    
    // cerr << "hey" << endl;
    vector<int> v2idx(m);
    int ev_cnt = 0, odd_cnt = 0;
    rep(i, 0, m) {
        if ((a[i].first % 2) == 1) {
            v2idx[i] = odd_cnt++;
        } else {
            v2idx[i] = ev_cnt++;
        }
    }

    // cerr << "v2\n";
    // rep(i, 0, m) {
    //     cerr << v2idx[i] << " ";
    // }
    // cerr << endl;
    
    vector<vi> g(ev_cnt);
    
    vector<bool> v(m, false);
    int ans = 0;
    rep(i, 0, m) {
        rep(j, 0, m) {
            if (i == j)
                continue;
            
            if ((a[i].first % 2) == (a[j].first % 2))
                continue;

            if (a[i].first % 2 == 1)
                continue;

            int ifi = a[i].first, ise = a[i].second, jfi = a[j].first, jse = a[j].second;
        
            if ((ifi > jfi))
                swap(ifi, jfi), swap(ise, jse);
            
            if ((jfi <= ise) && (jse > ise)) {
                // cerr << "ij : " << i << " " << j << endl;
                // cerr << "i. " << a[i].first << " " << a[i].second << endl;
                // cerr << "j. " << a[j].first << " " << a[j].second << endl;
                v[i] = true, v[j] = true;
                g[v2idx[i]].push_back(v2idx[j]);
            }
        }
    } 
    for(int i = 0; i < m; i++) ans += !v[i];

    // cerr << "g\n";
    // rep(i, 0, ev_cnt) {
    //     cerr << "v2i : " << v2idx[i] << endl;
    //     for (auto x : g[i])
    //         cerr << x << " ";
    //     cerr << endl;
    // }


    ans += cover(g, ev_cnt, odd_cnt).size();
    ans = m - cover(g, ev_cnt, odd_cnt).size();
    // cout << "COVER : ";
    // for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
    // cout << "\n";
    // ans += v.size();

    // cout << v.size() << endl;
    cout << ans << "\n";
    
    return 0;
}