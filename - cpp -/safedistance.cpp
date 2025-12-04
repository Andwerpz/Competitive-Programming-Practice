#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

typedef pair<int,int> pii;
typedef vector<int> vi;
#define rep(i, a ,b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define z(s) (int) (x).size()

//SWERC 2020 - C

//binary search on the minimum distance. 

//then, it's just solving whether or not you can walk from the bottom left to top right
//given that you can't go within a bunch of circles. This is just a BFS graph problem.

const ld epsilon = 1e-9;

struct vec2 {
    ld x, y;
};

ld dist_sq(vec2 a, vec2 b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

ld dist(vec2 a, vec2 b) {
    return sqrt(dist_sq(a, b));
}

bool is_valid(ld x, ld y, vector<vec2>& a, int n, ld val) {
    vector<vector<int>> c(n);
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(dist(a[i], a[j]) < val * 2) {
                c[i].push_back(j);
                c[j].push_back(i);
            }
        }
    }
    vector<bool> v(n, false);
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(x - a[i].x < val || a[i].y < val) {
            v[i] = true;
            q.push(i);
        }
    }
    while(q.size() != 0) {
        int cur = q.front();
        q.pop();
        for(int nx : c[cur]) {
            if(v[nx]) continue;
            v[nx] = true;
            q.push(nx);
        }
    }
    for(int i = 0; i < n; i++) {
        if(a[i].x < val || y - a[i].y < val) {
            if(v[i]) return false;
        }
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    ld x, y;
    cin >> x >> y;
    int n;
    cin >> n;
    vector<vec2> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
    ld low = 0, high = 1e9;
    while(high - low > epsilon) {
        ld mid = low + (high - low) / 2;
        if(is_valid(x, y, a, n, mid)) low = mid;
        else high = mid;
    }
    cout << fixed << setprecision(10) << low << "\n";

    return 0;
}
