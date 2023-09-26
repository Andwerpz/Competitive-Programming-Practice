#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using pi = pair<int, int>;

//ICPC Finals 2014

const int N = 2e6+5;

int lifts[N][20];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;

    vector<pi> a(k);

    vector<int> events;
    map<int, vector<int>> starts, ends;

    for (int i = 0; i < k; ++i) {
        cin >> a[i].first >> a[i].second;
        events.push_back(a[i].first);
        events.push_back(a[i].second);

        events.push_back(a[i].first + n);
        events.push_back(a[i].second + n);

        starts[a[i].first].push_back(i);
        starts[a[i].first + n].push_back(i);

        ends[a[i].second].push_back(i);
        ends[a[i].second + n].push_back(i);
    }

    sort(events.begin(), events.end());

    events.erase(unique(events.begin(), events.end()), events.end());

    int mx = -1;
    int mx_nei = -1;

    vector<int> adj(k, -1), best_nei(k, 0);

    for (auto e : events) {
        // starts
        for (auto x : starts[e]) {
            int other;
            if (a[x].second < a[x].first || e > n) {
                other = a[x].second + n;
            } else {
                other = a[x].second;
            }
            if (other > mx) {
                mx = other;
                mx_nei = x;
            }
        }

        cerr << "e : " << e << " mx : " << mx << " mx_nei : " << mx_nei << endl;


        // ends
        for (auto x : ends[e]) {
            cerr << x << " ";
            int wrap = mx % n;
            if (wrap > best_nei[x]) {
                adj[x] = mx_nei;
            }
        }
        cerr << endl;
    }


    for (auto x : adj) cerr << x << " ";
    cerr << endl;


    
    return 0;
}
