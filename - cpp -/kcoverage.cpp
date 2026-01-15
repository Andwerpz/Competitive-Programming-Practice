/*
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
*/
#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
#define f first
#define s second
#define int long long
 
using namespace std;

//2025 ICPC Asia Chengdu Regional Contest - K

array<int, 3> operator+(array<int, 3> a, array<int, 3> b) {
    array<int, 3> c {0, 0, 0};
    for (int i = 0; i < 3; i++) c[i] = a[i] + b[i];
    return c;
}

array<int, 3> operator-(array<int, 3> a, array<int, 3> b) {
    array<int, 3> c {0, 0, 0};
    for (int i = 0; i < 3; i++) c[i] = a[i] - b[i];
    return c;
}

struct SegmentTree {
    struct Node {
        int max = -1e9;
    }; 

    vector<Node> st;
    int n;
    SegmentTree(int n): n(n) {
        st.resize(4 * n + 1);
    }

    void merge(Node& a, Node& b, Node& c) {
        a.max = max(b.max, c.max);
    }

    void build(vector<int>& a, int id, int l, int r) {
        if (l == r) {
            st[id].max = a[l];            
            return;
        }
        int mid = (l + r) / 2;
        build(a, id * 2, l, mid);
        build(a, id * 2 + 1, mid + 1, r);
        merge(st[id], st[id * 2], st[id * 2 + 1]);
    }

    void update(int id, int l, int r, int u, int val) {
        if (l == r) {
            st[id].max = val; // or st[id].sum += val
            return;
        }
        int mid = (l + r) / 2;
        if (u <= mid) update(id * 2, l, mid, u, val);
        else update(id * 2 + 1, mid + 1, r, u, val); 
        merge(st[id], st[id * 2], st[id * 2 + 1]);
    }

    Node query(int id, int l, int r, int u, int v) {
        if (v < l || r < u) return Node();
        if (u <= l && r <= v) {
            return st[id];
        }
        int mid = (l + r) / 2;
        auto a = query(id * 2, l, mid, u, v);
        auto b = query(id * 2 + 1, mid + 1, r, u, v);
        Node res;
        merge(res, a, b);
        return res;
    }
};

bool debug = false;

void solve() {
    int n, L, k; cin >> n >> L >> k;
    int MAX = n * 4 + L * 2 + 5;
    array<int, 3> empty{0, 0, 0};
    vector<int> covers(MAX + 1);
    vector<pii> ranges(n);
    for (int i = 0; i < n; i++) {
        cin >> ranges[i].first;
        ranges[i].second = ranges[i].first + L - 1;
        ranges[i].first++;
        ranges[i].second++;
    }
    for (auto [l, r]: ranges) {
        covers[l]++;
        covers[r + 1]--;
    }

    for (int i = 1; i <= MAX; i++) covers[i] += covers[i - 1];

    vector<array<int, 3>> scores(MAX + 1, empty), pre(MAX + 1, empty);
    vector<array<int, 3>> rangeScores(MAX + 1, empty); // score of range start at this index
    for (int i = 1; i <= MAX; i++) {
        if (covers[i] == k - 1) scores[i][0] = 1;
        else if (covers[i] == k) scores[i][1] = 1;
        else if (covers[i] == k + 1) scores[i][2] = 1;
        pre[i] = pre[i - 1] + scores[i];
    }

    for (int i = 1; i + L - 1 <= MAX; i++) {
        rangeScores[i] = pre[i + L - 1] - pre[i - 1];
    }   

    // max (k - 1) - k
    vector<array<int, 3>> maxPre(MAX + 1, empty), maxSuf(MAX + 2, empty);

    for (int i = 1; i <= MAX; i++) {
        maxPre[i] = maxPre[i - 1];
        if (maxPre[i][0] - maxPre[i][1] < rangeScores[i][0] - rangeScores[i][1]) {
            maxPre[i] = rangeScores[i];
        }
    }

    for (int i = MAX; i >= 1; i--) {
        maxSuf[i] = maxSuf[i + 1];
        if (maxSuf[i][0] - maxSuf[i][1] < rangeScores[i][0] - rangeScores[i][1]) {
            maxSuf[i] = rangeScores[i];
        }
    }

    if (debug) {
        cout << "rangeScores\n";
        for (int j = 0; j < 3; j++) {
            for (int i = 1; i <= MAX; i++) cout << rangeScores[i][j] << " \n"[i == MAX];
        }
        cout << "maxPre ";
        for (int i = 1; i <= MAX; i++) cout << maxPre[i][0] - maxPre[i][1] << " \n"[i == MAX];
        cout << "maxSuf ";
        for (int i = 1; i <= MAX; i++) cout << maxSuf[i][0] - maxSuf[i][1] << " \n"[i == MAX];
    }

    ll currentScore = pre[MAX][1]; // sum scores of k

    if (debug) {
        for (int i = 1; i <= MAX; i++) cout << scores[i][1] << " ";
        cout << '\n';
    }

    ll maxAdd = 0; // max we can add to currentScore

    vector<int> specOverLapLeft(MAX + 1, -1e9);
    vector<int> specOverLapRight(MAX + 1, -1e9);

    for (int i = 0; i + L <= MAX; i++) {
        specOverLapLeft[i] = -pre[i][0] + pre[i][1] - pre[i + L][2] + pre[i + L][1];
        specOverLapRight[i] = pre[i + L][0] - pre[i + L][1] + pre[i][2] - pre[i][1];

    }

    SegmentTree stLeft(MAX + 1), stRight(MAX + 1);

    stLeft.build(specOverLapLeft, 1, 0, MAX);
    stRight.build(specOverLapRight, 1, 0, MAX);



    for (auto [l, r]: ranges) {
        // change to range on the right non-overlap
        maxAdd = max(maxAdd, (ll)maxSuf[r + 1][0] - maxSuf[r + 1][1] + rangeScores[l][2] - rangeScores[l][1]);

        if (debug) {
            cout << l << " " << r << " right non overlap ";
            cout << maxSuf[r + 1][0] - maxSuf[r + 1][1] << " " << rangeScores[l][2] - rangeScores[l][1] << '\n';
        }

        // change to range on the left non-overlap
        if (l > L) maxAdd = max(maxAdd, (ll)maxPre[l - L][0] - maxPre[l - L][1] + rangeScores[l][2] - rangeScores[l][1]);

        if (debug) {
            cout << l << " " << r << " left non overlap ";
            cout << maxPre[l - L][0] - maxPre[l - L][1] << " " << rangeScores[l][2] - rangeScores[l][1] << '\n';
        }

        // overlap left end
        ll cur = pre[l - 1][0] - pre[l - 1][1] + pre[r][2] - pre[r][1];
        ll tmp = stLeft.query(1, 0, MAX, max(0ll, l - L), l - 1).max;
        maxAdd = max(maxAdd, cur + tmp);

        if (debug) {
            cout << l << " " << r << "left overlap ";
            cout << cur << " " << tmp << '\n';
        }

        // overlap right end
        cur = pre[l - 1][1] - pre[l - 1][2] + pre[r][1] - pre[r][0];
        tmp = stRight.query(1, 0, MAX, l, r - 1).max;
        maxAdd = max(maxAdd, cur + tmp);

        if (debug) {
            cout << l << " " << r << "right overlap ";
            cout << cur << " " << tmp << '\n';
        }

    }

    cout << currentScore + maxAdd << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int casi = 1;
    cin >> casi;
    while(casi --) {
      solve();
    }
    return 0;
}