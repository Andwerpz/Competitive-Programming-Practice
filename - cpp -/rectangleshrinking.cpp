#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

void solve_seg(vvi& a, priority_queue<pii>& q){
    int active = -1;
    int a_r = -1;
    while(q.size() != 0){
        int cur = q.top().second;
        int l = -q.top().first;
        int r = a[cur][3];
        q.pop();
        if(active == -1){
            active = cur;
            a_r = r;
            continue;
        }
        if(r <= a_r) {
            a[cur].assign(4, 0);
            continue;
        }
        a[active][3] = min(a[active][3], l - 1);
        active = cur;
        a_r = r;
    }
    for(int i = 0; i < a.size(); i++){
        if(a[i][1] > a[i][3]) {
            a[i].assign(4, 0);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vvi a(n, vi(4));    //{u, l, d, r}
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 4; j++){
                cin >> a[i][j];
            }
        }
        //make all tall rectangles non-intersecting
        {
            priority_queue<pii> q;
            for(int i = 0; i < n; i++){
                if(a[i][0] != a[i][2]) {
                    q.push({-a[i][1], i});
                }
            }
            solve_seg(a, q);
        }
        //if a short segment 'completely contains' a tall segment, shorten that tall segment to the other side
        //otherwise, shorten the short segment 
        set<pii> ends;
        for(int i = 0; i < n; i++){
            if(a[i][0] != a[i][2] && a[i][1] != 0) {
                ends.insert({a[i][1], -(i + 1)});
                ends.insert({a[i][3], i + 1});
            }
        }
        {
            queue<int> q;
            for(int i = 0; i < n; i++){
                if(a[i][0] == a[i][2] && a[i][0] != 0) {
                    q.push(i);
                }
            }
            while(q.size() != 0 && ends.size() != 0){
                int cur = q.front();
                q.pop();
                int l = a[cur][1];
                int r = a[cur][3];
                auto lptr = ends.lower_bound({l, 0});
                if(lptr != ends.end() && lptr->second >= 1){
                    l = lptr->first + 1;
                }
                auto rptr = ends.lower_bound({r, 1e9});
                if(rptr != ends.begin()){
                    rptr --;
                    if(rptr->second <= -1){
                        r = rptr->first - 1;
                    }
                }
                if(r < l){
                    a[cur].assign(4, 0);
                    continue;
                }
                a[cur][1] = l;
                a[cur][3] = r;
                while(ends.lower_bound({l, -1e9}) != ends.end() && ends.lower_bound({l, -1e9})->first <= r) {
                    auto ptr = ends.lower_bound({l, -1e9});
                    int ind = ptr->second - 1;
                    ends.erase(ptr);
                    if(ind < 0){
                        continue;
                    }
                    int side = a[cur][0] == 1? 2 : 1;
                    a[ind][0] = side;
                    a[ind][2] = side;
                    q.push(ind);
                }
            }
        }
        //now, all tall and short segments should be unintersecting, so run the normal algorithm. 
        //now, solve segments on layer 1 and 2 seperately
        {
            for(int l = 1; l <= 2; l++){
                priority_queue<pii> q;
                for(int i = 0; i < n; i++){
                    if(a[i][0] == a[i][2] && a[i][0] == l) {
                        q.push({-a[i][1], i});
                    }
                }
                solve_seg(a, q);
            }
        }
        //print answer
        int area = 0;
        for(int i = 0; i < n; i++){
            if(a[i][0] == 0){
                continue;
            }
            area += (a[i][2] - a[i][0] + 1) * (a[i][3] - a[i][1] + 1);
        }
        cout << area << "\n";
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 4; j++){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}