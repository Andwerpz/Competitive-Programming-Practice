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

//Topcoder - 14715

//constructive. 

//First, we should always place the '1' nodes adjacent to eachother. Next, the '2' nodes should always
//be placed so that they're adjacent to the same node. 

//Actually, we can disregard the '2' nodes for now. At the end we'll just place them so they're hanging 
//off of the same parent node. 

//For the rest of the nodes '3' and above, we can hang them in a predictable pattern. Denote l and r two 
//different child nodes. We don't really care where they are, we just want them to be different. Also, we 
//want l and r to initially have 0 and 1 children respectively. 

//Every time we add a node, we add one to l and one to r. Then, if l or r are full of children (have 2 
//children), we then reassign l or r to the node we just added to them. 

class SkolemBinaryTree {
public:
    void validate(vector<pii>& e, int k) {
        int n = k * 2;
        vvi c(n);
        for(int i = 0; i < e.size(); i++){
            int u = e[i].first, v = e[i].second;
            c[u].push_back(v);
            c[v].push_back(u);
        }
        for(int i = 0; i < n; i++) assert(1 <= c[i].size() && c[i].size() <= 3);
        for(int i = 0; i < k; i++){
            int a = i * 2 + 0, b = i * 2 + 1;
            queue<int> q;
            vb v(n, false);
            vi d(n, 1e9);
            d[a] = 0;
            v[a] = true;
            q.push(a);
            while(q.size() != 0){
                int cur = q.front();
                q.pop();
                for(int x : c[cur]) if(!v[x]) v[x] = true, d[x] = d[cur] + 1, q.push(x);
            }
            assert(d[b] == i + 1);
        }
    }

    vector<int> construct(int k) {
        vector<pii> e;
        int idptr = 0;
        int l = idptr ++;
        int r = idptr ++;
        e.push_back({l, r});
        int l2 = idptr ++, r2 = idptr ++;
        int last = l;
        for(int i = 2; i < k; i++){
            int lc = idptr ++;
            int rc = idptr ++;
            e.push_back({l, lc});
            e.push_back({r, rc});
            if(i % 2){
                l = lc;
                last = lc;
            }
            else {
                r = rc;
                last = rc;
            }
        }
        if(k > 1) {
            e.push_back({last, l2});
            e.push_back({last, r2});
        }
        validate(e, k);
        vi ans(e.size() * 2);
        for(int i = 0; i < e.size(); i++){
            ans[i * 2 + 0] = e[i].first;
            ans[i * 2 + 1] = e[i].second;
        }
        return ans;
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = SkolemBinaryTree();
    vector<int> ret = c.construct(arg0);
    for (auto& item : ret) { cout << item << "\n"; }
}