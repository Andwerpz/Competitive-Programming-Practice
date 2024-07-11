#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 600E

//we can take a dsu approach. 

//for each component, we keep track of the number of occurrences of each color, and for each number of occurrences, 
//the sum of colors that have that amount of occurrences. 

//if we build the components from the leaves to the root, then we can record the answer for each subtree
//when there is a component that covers that subtree. 

//combining all components will take around n * log(n)^2 time. Since n = 10^5, this should run in time. 

struct DSU {
    int N;
    vector<int> dsu;
    vector<map<int, int>> occ;  //for each color, what is the amount of occurrences?
    vector<map<int, ll>> sum;   //for each amount of occurrences, what is the sum of colors

    DSU(int n, vector<int> color) {
        this->N = n;
        this->dsu = vector<int>(n, 0);
        occ = vector<map<int, int>>(n);
        sum = vector<map<int, ll>>(n);
        for(int i = 0; i < n; i++){ //initialize roots
            dsu[i] = i;
            occ[i][color[i]] = 1;
            sum[i][1] = color[i];
        }
    }

    int find(int a) {
        if(dsu[a] == a) {
            return a;
        }
        return dsu[a] = find(dsu[a]);
    }

    bool unify(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        //cost of merging is equal to size of occ for thing to be merged.
        //always do lower cost
        if(occ[rb].size() < occ[ra].size()) {
            swap(ra, rb);
        }
        //merge ra into rb
        for(auto i = occ[ra].begin(); i != occ[ra].end(); i++){
            int c_color = i->first;
            int n_occ = i->second;
            sum[rb][occ[rb][c_color]] -= c_color;
            occ[rb][c_color] += n_occ;
            sum[rb][occ[rb][c_color]] += c_color;
        }
        dsu[ra] = rb;
        return true;
    }
};

void find_p(int cur, int _p, vector<int>& p, vector<vector<int>>& c) {
    p[cur] = _p;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == _p) {
            continue;
        }
        find_p(next, cur, p, c);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> color(n);
    for(int i = 0; i < n; i++){
        cin >> color[i];
    }
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 0; i < n - 1; i++){
        int x, y;
        cin >> x >> y;
        x --;
        y --;
        c[x].push_back(y);
        c[y].push_back(x);
    }
    vector<int> p(n, -1);
    find_p(0, -1, p, c);
    vector<int> indeg(n, 0);
    for(int i = 0; i < n; i++){
        indeg[p[i]] ++;
    }
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(indeg[i] == 0){
            q.push(i);
        }
    }
    DSU dsu(n, color);
    vector<ll> ans(n, -1);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        ans[cur] = dsu.sum[dsu.find(cur)].rbegin() -> second;
        if(p[cur] != -1){
            dsu.unify(cur, p[cur]);
        }
        indeg[p[cur]] --;
        if(indeg[p[cur]] == 0){
            q.push(p[cur]);
        }
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}
