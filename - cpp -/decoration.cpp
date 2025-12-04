#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;

//SWERC 2020 - G

//observe that if we fix the first element of the sequence, we actually fix all 
//the elements, as a[i + 1] must be equal to (a[i] + d[a[i]]) % N, where d[i] is
//the number of divisors of i. 

//so we can reinterpret this as a graph problem: we have nodes 0, 1, ..., N - 1, 
//node i has an outgoing edge to node (i + d[i]) % N. We want to find a path of 
//length K such that it doesn't use a node twice and the sum of node indexes on the
//path is minimized. 

//to solve this new problem, we can observe that the graph is a functional graph, 
//and just use binary lifting. From here, it's just some annoying implementation
//to find cycles to see which nodes are actually eligible to start the path. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    ll n, k;
    cin >> n >> k;
    vl div(n, 0);
    for(int i = 1; i < n; i++) {
        for(int j = i; j < n; j += i) {
            div[j] ++;
        }
    }
    const int B = 22;
    vvi b(n, vi(B, -1));
    vi c(n);
    vvi rc(n);
    for(int i = 0; i < n; i++) {
        b[i][0] = (i + div[i]) % n;
        c[i] = (i + div[i]) % n;
        rc[(i + div[i]) % n].push_back(i);
    }
    for(int i = 1; i < B; i++) {
        for(int j = 0; j < n; j++) {
            b[j][i] = b[b[j][i - 1]][i - 1];
        }
    }
    // cout << "HERE" << endl;
    vvl bc(n, vl(B, 0));
    for(int i = 0; i < n; i++) {
        bc[i][0] = i;
    }
    for(int i = 1; i < B; i++) {
        for(int j = 0; j < n; j++) {
            bc[j][i] = bc[j][i - 1] + bc[b[j][i - 1]][i - 1];
        }
    }
    // cout << "DONE COMPUTE BLIFT" << endl;
    //find all cycle nodes
    vector<bool> isc(n, false);
    vector<bool> v(n, false);
    for(int i = 0; i < n; i++) {
        if(v[i]) continue;
        vi path;
        int ptr = i;
        bool foundc = false;
        while(!v[ptr]) {
            v[ptr] = true;
            path.push_back(ptr);
            ptr = c[ptr];
        }
        assert(path.size() >= 1);
        for(int i = path.size() - 1; i >= 0; i--) {
            // cout << "PATH : " << path[i] << " " << ptr << endl;
            if(path[i] == ptr) {
                for(int j = i; j < path.size(); j++) {
                    isc[path[j]] = true;
                }
                break;
            }
        }
    }
    // cout << "DONE FIND CYCLE NODES" << endl;
    //find mxl
    vi mxl(n, -1);
    v = vector<bool>(n, false);
    for(int i = 0; i < n; i++) {
        if(!isc[i]) continue;
        if(v[i]) continue;
        vi path;
        int ptr = i;
        while(!v[ptr]) {
            v[ptr] = true;
            path.push_back(ptr);
            ptr = c[ptr];
        }
        assert(path.size() >= 1);
        for(int x : path) {
            mxl[x] = path.size();
            queue<int> q;
            q.push(x);
            while(q.size() != 0) {
                int cur = q.front();
                q.pop();
                for(int nx : rc[cur]) {
                    if(isc[nx]) continue;
                    assert(!v[nx]);
                    v[nx] = true;
                    mxl[nx] = mxl[cur] + 1;
                    q.push(nx);
                }
            }
        }
    }
    // cout << "DONE FIND MXL" << endl;
    // for(int i = 0; i < n; i++) {
    //     cout << mxl[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n; i++) {
    //     cout << c[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n; i++) {
    //     cout << isc[i] << " ";
    // }
    // cout << "\n";
    //compute min 
    ll ans = 1e18;
    int anss = -1;
    for(int i = 0; i < n; i++) {
        if(mxl[i] < k) continue;
        int ptr = i;
        int tmp = k;
        ll cans = 0;
        for(int j = B - 1; j >= 0; j--) {
            if(tmp >= (1 << j)) {
                cans += bc[ptr][j];
                ptr = b[ptr][j];
                tmp -= (1 << j);
            }
        }
        assert(tmp == 0);
        if(cans < ans) {
            anss = i;
            ans = cans;
        }
    }
    if(anss == -1) {
        cout << "-1\n";
        return 0;
    }
    for(int i = 0; i < k; i++) {
        cout << anss << " ";
        anss = c[anss];
    }
    cout << "\n";

    return 0;
}
