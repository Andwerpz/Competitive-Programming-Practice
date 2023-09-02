#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using pi = pair<int, int>;

//ICPC World Finals 2018 K

//need at least 10 priority queues for this problem :P

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<int> a(n);

    for (int i = 0; i < m; ++i) {
        int x, b; cin >> x >> b;
        a[x]++;
        a[b]++;
    }

    priority_queue<pi> in_tree, out_tree;
    vector<int> ones;

    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) {
            ones.push_back(i);
        } else {
            out_tree.push({-a[i], i});
        }
    }

    // cerr << "hey" << endl;

    int satisfied = 0;
    vector<pi> edges;

    while (ones.size() && out_tree.size()) {
        int vone = ones.back();
        ones.pop_back();

        assert(out_tree.size());

        auto p = out_tree.top();
        int v = p.second, deg = -p.first;

        out_tree.pop();

        edges.push_back({vone, v});
        satisfied++;

        deg--;
        if (deg == 1) {
            ones.push_back(v);
        } else {
            out_tree.push({-deg, v});
        }
    }

    

    // cerr << "EDGES" << endl;
    // for (auto x : edges) {
    //     cerr << x.first << " " << x.second << endl;
    // }
    // cerr << endl;
    // cerr << endl;

    if (out_tree.size()) {
        auto p = out_tree.top();
        int v = p.second, deg = -p.first;
        out_tree.pop();
        in_tree.push({-deg, v});
    } else if (ones.size() == 2) {
        satisfied += 2;
        edges.push_back({ones[0], ones[1]});
    } else {
        cout << "DOESNT WORK" << endl;
        cerr << "onessi : " << ones.size() << endl;
        throw runtime_error("BOZO");
        return 0;
    }

    while (out_tree.size()) {
        int vlow, deglow;
        if (!in_tree.size()) {
            // bring one from the out tree
            auto p = out_tree.top();
            vlow = p.second, deglow = -p.first;
            out_tree.pop();
        } else {
            // take lowest from in tree
            vlow = in_tree.top().second, deglow = -in_tree.top().first;
            in_tree.pop();
        }

        int vhi, deghi;
        if (out_tree.size()) {
            vhi = out_tree.top().second, deghi = -out_tree.top().first;
            out_tree.pop();
        } else throw runtime_error("BOZO2");

        // connect edge
        edges.push_back({vlow, vhi});
        deglow--;
        deghi--;

        // bring from out tree to in tree

        in_tree.push({-deghi, vhi});

        if (!deglow) {
            satisfied++;
        } else {
            in_tree.push({-deglow, vlow});
        }
    }

    // cerr << endl;
    // cerr << endl;
    cout << n - satisfied << endl;
    cout << n << " " << n-1 << endl;
    for (auto x : edges) {
        cout << x.first << " " << x.second << endl;
    }

    return 0;
}
