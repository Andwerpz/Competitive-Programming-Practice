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

//Codeforces - 2001C

//observe that querying a, b simply returns the node that is on the path a -> b, and is halfway between them. 

//Let's say that we have two nodes a, b, and we don't know any information about the nodes on the path
//from a to b. We can get all the edges on the path a -> b in dist(a, b) * log(dist(a, b)) queries by repeatedly
//querying the path halves until we get to single edges. 

//After getting the edges of one path, how do we consistently get more information? Maintain a set of nodes
//that we have no information of. Always query paths from nodes that we do have information to nodes that we 
//don't. Whenever we are about to send a query about two nodes that we have information of, just don't do it. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        set<int> not_v, v;
        v.insert(0);
        for(int i = 1; i < n; i++){
            not_v.insert(i);
        }
        vector<pii> e;
        while(not_v.size() != 0){
            queue<pii> q;
            q.push({*v.begin(), *not_v.begin()});
            set<int> cv;
            while(q.size() != 0){
                int a = q.front().first;
                int b = q.front().second;
                q.pop();
                if(v.count(a) && v.count(b)) {
                    continue;
                }
                int mid;
                cout << "? " << a + 1 << " " << b + 1 << endl;
                cin >> mid;
                mid --;
                if(mid == a || mid == b){
                    // cout << "FOUND EDGE : " << a << " " << b << endl;
                    e.push_back({a, b});
                    cv.insert(a);
                    cv.insert(b);
                }
                else {
                    q.push({a, mid});
                    q.push({mid, b});
                }
            }
            for(auto i = cv.begin(); i != cv.end(); i++){
                v.insert(*i);
                not_v.erase(*i);
            }
        }
        cout << "! ";
        for(int i = 0; i < n - 1; i++){
            cout << e[i].first + 1 << " " << e[i].second + 1 << " ";
        }
        cout << endl;
    }
    
    return 0;
}