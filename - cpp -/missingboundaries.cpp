#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

//3rd Universal Cup, Stage 7: Warsaw - B

//first, if there is a segment that is only missing a starting or ending point, make the 
//missing starting or ending point equal to the not missing boundary, and mark it as adjustable. 

//for segments that are missing both boundaries, these can be placed anywhere we want. 

//Then, just go through all the boundaries in ascending order, and see how many 'free' segments
//are required. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int t;
    cin >> t;
    while(t--){
        int n, l;
        cin >> n >> l;
        int ex = 0, ex_p = 0, ex_s = 0;
        vector<pair<int, pii>> ev; //{pos, {is begin? -1 : 1, is adjustable? 0 : 1}}
        for(int i = 0; i < n; i++){
            int a, b;
            cin >> a >> b;
            if(a == -1 && b == -1) {
                ex ++;
                continue;
            }
            int adj_a = (a == -1), adj_b = (b == -1);
            if(a == -1) {
                a = b;
            }
            else if(b == -1) {
                b = a;
            }
            ev.push_back({a, {-1, adj_a}});
            ev.push_back({b, {1, adj_b}});
        }
        ev.push_back({0, {1, 0}});
        ev.push_back({l + 1, {-1, 0}});
        sort(ev.begin(), ev.end());
        bool is_valid = true;
        for(int i = 0; i < ev.size() - 1; i++){
            pair<int, pii> cur = ev[i], nxt = ev[i + 1];
            // cout << "CUR NXT : " << cur.first << " " << cur.second.first << " " << nxt.first << " " << nxt.second.first << "\n";
            if(cur.second.first == nxt.second.first) {
                //either see two left or two right bounds
                is_valid = false;
                break;
            }
            if(cur.second.first == -1 && nxt.second.first == 1) {
                //this is a segment interior
                continue;
            }
            //this is between two segments
            if(cur.first + 1 != nxt.first) {
                //have a gap
                if(!cur.second.second && !nxt.second.second) {
                    //forced to have a gap here
                    // cout << "GAP : " << cur.second.second << " " << nxt.second.second << "\n";
                    ex_p ++;
                }
                ex_s += nxt.first - cur.first - 1;
            }
        }
        // cout << "ex_p ex_s : " << ex_p << " " << ex_s << "\n";
        if(ex_p > ex || ex_s < ex) is_valid = false;
        cout << (is_valid? "TAK" : "NIE") << "\n";
    }

    return 0;
}